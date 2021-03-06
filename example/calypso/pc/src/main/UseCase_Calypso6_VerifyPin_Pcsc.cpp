/**************************************************************************************************
 * Copyright (c) 2020 Calypso Networks Association                                                *
 * https://www.calypsonet-asso.org/                                                               *
 *                                                                                                *
 * See the NOTICE file(s) distributed with this work for additional information regarding         *
 * copyright ownership.                                                                           *
 *                                                                                                *
 * This program and the accompanying materials are made available under the terms of the Eclipse  *
 * Public License 2.0 which is available at http://www.eclipse.org/legal/epl-2.0                  *
 *                                                                                                *
 * SPDX-License-Identifier: EPL-2.0                                                               *
 **************************************************************************************************/

/* Core */
#include "ByteArrayUtil.h"
#include "PoSelectionRequest.h"
#include "SeProxyService.h"
#include "SeReader.h"

/* Example */
#include "CalypsoClassicInfo.h"
#include "CalypsoClassicTransactionEngine.h"
#include "CalypsoUtilities.h"

/* Plugin */
#include "PcscPluginFactory.h"
#include "PcscReadersSettings.h"

/* Common */
#include "LoggerFactory.h"

/* Core */
#include "PoSelectionRequest.h"
#include "SeCommonProtocols.h"
#include "SeResource.h"

/* Calypso */
#include "CalypsoPo.h"
#include "CalypsoPoPinException.h"
#include "CalypsoSam.h"
#include "ElementaryFile.h"
#include "PoSecuritySettings.h"
#include "PoSelectionRequest.h"

using namespace keyple::calypso::command::po::exception;
using namespace keyple::calypso::transaction;
using namespace keyple::common;
using namespace keyple::core::seproxy;
using namespace keyple::core::seproxy::event;
using namespace keyple::core::seproxy::exception;
using namespace keyple::core::seproxy::protocol;
using namespace keyple::core::util;
using namespace keyple::example::calypso::common::postructure;
using namespace keyple::example::calypso::common::transaction;
using namespace keyple::plugin::pcsc;

using AccessLevel = PoTransaction::SessionSetting::AccessLevel;
using AidSelector = SeSelector::AidSelector;
using InvalidatedPo = PoSelector::InvalidatedPo;
using ModificationMode = PoTransaction::SessionSetting::ModificationMode;
using PoSecuritySettingsBuilder = PoSecuritySettings::PoSecuritySettingsBuilder;

class UseCase_Calypso6_VerifyPin_Pcsc {
};

const std::shared_ptr<Logger> logger =
    LoggerFactory::getLogger(typeid(UseCase_Calypso6_VerifyPin_Pcsc));

static std::shared_ptr<SeReader> poReader;
static std::shared_ptr<CalypsoPo> calypsoPo;

static bool selectPo()
{
    /* Check if a PO is present in the reader */
    if (poReader->isSePresent()) {
        logger->info("= ##### 1st PO exchange: AID based selection with reading of Environment " \
                     "file\n");

        /* Prepare a Calypso PO selection */
        SeSelection seSelection;

        /*
         * Setting of an AID based selection of a Calypso REV3 PO
         *
         * Select the first application matching the selection AID whatever the SE communication
         * protocol keep the logical channel open after the selection
         */

        /*
         * Calypso selection: configures a PoSelectionRequest with all the desired attributes to
         * make the selection and read additional information afterwards
         */
        auto aidSelector = AidSelector::builder()->aidToSelect(CalypsoClassicInfo::AID).build();
        auto seSelector = PoSelector::builder()->seProtocol(SeCommonProtocols::PROTOCOL_ISO14443_4)
                                                .aidSelector(aidSelector)
                                                .invalidatedPo(InvalidatedPo::REJECT)
                                                .build();
        auto poSelector = std::dynamic_pointer_cast<PoSelector>(seSelector);
        auto poSelectionRequest = std::make_shared<PoSelectionRequest>(poSelector);

        /* Prepare the reading of the Environment and Holder file */
        poSelectionRequest->prepareReadRecordFile(CalypsoClassicInfo::SFI_EnvironmentAndHolder,
                                                  CalypsoClassicInfo::RECORD_NUMBER_1);

        /*
         * Add the selection case to the current selection
         *
         * (we could have added other cases here)
         */
        auto abstract = std::reinterpret_pointer_cast
                             <AbstractSeSelectionRequest<AbstractApduCommandBuilder>>(
                                 poSelectionRequest);
        seSelection.prepareSelection(abstract);

        /*
         * Actual PO communication: operate through a single request the Calypso PO selection
         * and the file read
         */
        std::shared_ptr<AbstractMatchingSe> matchingSe =
            seSelection.processExplicitSelection(poReader)->getActiveMatchingSe();
        calypsoPo = std::dynamic_pointer_cast<CalypsoPo>(matchingSe);
        return true;
    } else {
        logger->error("No PO were detected\n");
    }
    return false;
}

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    /* Get the instance of the SeProxyService (Singleton pattern) */
    SeProxyService& seProxyService = SeProxyService::getInstance();

    /* Assign PcscPlugin to the SeProxyService */
    seProxyService.registerPlugin(std::make_shared<PcscPluginFactory>());

    /*
     * Get a PO reader ready to work with Calypso PO. Use the getReader helper method from the
     * CalypsoUtilities class.
     */
    poReader = CalypsoUtilities::getDefaultPoReader();

    /*
     * Get a SAM reader ready to work with Calypso PO. Use the getReader helper method from the
     * CalypsoUtilities class.
     */
    std::shared_ptr<SeResource<CalypsoSam>> samResource = CalypsoUtilities::getDefaultSamResource();

    logger->info("=============== UseCase Calypso #6: Verify PIN  ==================\n");
    logger->info("= PO Reader  NAME = %\n", poReader->getName());
    logger->info("= SAM Reader  NAME = %\n", samResource->getSeReader()->getName());

    if (selectPo()) {
        /* Security settings */
        auto poSecuritySettings = std::make_shared<PoSecuritySettingsBuilder>(samResource)
                                      ->pinCipheringKey(0x30, 0x79)
                                       .build();

        /* Create the PO resource */
        auto poResource = std::make_shared<SeResource<CalypsoPo>>(poReader, calypsoPo);
        const std::string pinOk = "0000";
        const std::string pinKo = "0001";

        /* create an unsecured PoTransaction */
        PoTransaction poTransactionUnsecured(poResource);

        /* Verification of the PIN (correct) out of a secure session in plain mode */
        poTransactionUnsecured.processVerifyPin(pinOk);
        logger->info("Remaining attempts #1: %\n", calypsoPo->getPinAttemptRemaining());

        /* create a secured PoTransaction */
        PoTransaction poTransaction(poResource, poSecuritySettings);

        /* Verification of the PIN (correct) out of a secure session in encrypted mode */
        poTransaction.processVerifyPin(pinOk);
        /* Log the current counter value (should be 3) */
        logger->info("Remaining attempts #2: %\n", calypsoPo->getPinAttemptRemaining());

        /* Verification of the PIN (incorrect) inside a secure session */
        poTransaction.processOpening(AccessLevel::SESSION_LVL_DEBIT);
        try {
            poTransaction.processVerifyPin(pinKo);
        } catch (const CalypsoPoCommandException& ex) {
            logger->error("PO Exception: %\n", ex.getMessage());
        }
        poTransaction.processCancel();
        /* Log the current counter value (should be 2) */
        logger->error("Remaining attempts #3: %\n", calypsoPo->getPinAttemptRemaining());

        /*
         * Verification of the PIN (correct) inside a secure session with reading of the counter
         * before
         */
        poTransaction.prepareCheckPinStatus();
        poTransaction.processOpening(AccessLevel::SESSION_LVL_DEBIT);
        /* Log the current counter value (should be 2) */
        logger->info("Remaining attempts #4: %\n", calypsoPo->getPinAttemptRemaining());
        poTransaction.processVerifyPin(pinOk);
        poTransaction.prepareReleasePoChannel();
        poTransaction.processClosing();
        /* Log the current counter value (should be 3) */
        logger->info("Remaining attempts #5: %\n", calypsoPo->getPinAttemptRemaining());
    } else {
        logger->error("The PO selection failed\n");
    }
}