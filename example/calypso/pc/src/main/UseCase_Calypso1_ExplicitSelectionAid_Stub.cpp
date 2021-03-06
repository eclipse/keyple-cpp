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

/* Example */
#include "CalypsoClassicInfo.h"
#include "CalypsoClassicTransactionEngine.h"

/* Common */
#include "IllegalStateException.h"
#include "LoggerFactory.h"

/* Core */
#include "PoSelectionRequest.h"
#include "ReaderPlugin.h"
#include "SeCommonProtocols.h"
#include "SeProxyService.h"

/* Calypso */
#include "ReadRecordsRespPars.h"
#include "CalypsoPo.h"
#include "ElementaryFile.h"

/* Plugin */
#include "StubCalypsoClassic.h"
#include "StubSamCalypsoClassic.h"
#include "StubProtocolSetting.h"
#include "StubPlugin.h"
#include "StubPluginFactory.h"
#include "StubReader.h"

using namespace keyple::common::exception;
using namespace keyple::example::calypso::common::transaction;
using namespace keyple::example::calypso::common::postructure;
using namespace keyple::example::calypso::pc::stub::se;
using namespace keyple::plugin::stub;
using namespace keyple::core::util;
using namespace keyple::core::seproxy;
using namespace keyple::core::seproxy::event;
using namespace keyple::core::seproxy::exception;
using namespace keyple::core::seproxy::protocol;

using AidSelector = SeSelector::AidSelector;
using InvalidatedPo = PoSelector::InvalidatedPo;

class UseCase_Calypso1_ExplicitSelectionAid_Stub {
};

std::shared_ptr<Logger> logger = LoggerFactory::getLogger(
    typeid(UseCase_Calypso1_ExplicitSelectionAid_Stub));

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    /* Get the instance of the SeProxyService (Singleton pattern) */
    SeProxyService& seProxyService = SeProxyService::getInstance();

    const std::string STUB_PLUGIN_NAME = "stub1";

    /* Register Stub plugin in the platform */
    auto factory = std::make_shared<StubPluginFactory>(STUB_PLUGIN_NAME);
    std::shared_ptr<ReaderPlugin> readerPlugin = seProxyService.registerPlugin(factory);

    /* Plug the PO stub reader */
    std::dynamic_pointer_cast<StubPlugin>(readerPlugin)->plugStubReader("poReader", true);

    /* Get a PO reader ready to work with Calypso PO */
    auto poReader = std::dynamic_pointer_cast<StubReader>(readerPlugin->getReader("poReader"));

    /* Check if the reader exists */
    if (poReader == nullptr)
        throw IllegalStateException("Bad PO reader setup");

    poReader->addSeProtocolSetting(
        SeCommonProtocols::PROTOCOL_ISO14443_4,
        StubProtocolSetting::STUB_PROTOCOL_SETTING[SeCommonProtocols::PROTOCOL_ISO14443_4]);

    /* Create 'virtual' Calypso PO */
    std::shared_ptr<StubSecureElement> calypsoStubSe = std::make_shared<StubCalypsoClassic>();

    logger->info("Insert stub PO\n");
    poReader->insertSe(calypsoStubSe);

    logger->info("=============== UseCase Calypso #1: AID based explicit selection ==============" \
                 "====\n");
    logger->info("= PO Reader  NAME = %\n", poReader->getName());

    /* Check if a PO is present in the reader */
    if (poReader->isSePresent()) {

        logger->info("= #### 1st PO exchange: AID based selection with reading of Environment " \
                     "file\n");

        /* Prepare a Calypso PO selection */
        SeSelection seSelection;

        /*
         * Setting of an AID based selection of a Calypso REV3 PO
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

        /* Prepare the reading order */
        poSelectionRequest->prepareReadRecordFile(CalypsoClassicInfo::SFI_EnvironmentAndHolder,
                                                  CalypsoClassicInfo::RECORD_NUMBER_1);

        /* Add the selection case to the current selection (we could have added other cases here) */
        auto abstract = std::reinterpret_pointer_cast
                            <AbstractSeSelectionRequest<AbstractApduCommandBuilder>>(
                                poSelectionRequest);
        seSelection.prepareSelection(abstract);

        /*
         * Actual PO communication: operate through a single request the Calypso PO selection
         * and the file read
         */
        std::shared_ptr<SelectionsResult> results = seSelection.processExplicitSelection(poReader);
        std::shared_ptr<AbstractMatchingSe> matchingSe = results->getActiveMatchingSe();
        auto calypsoPo = std::dynamic_pointer_cast<CalypsoPo>(matchingSe);

        logger->info("The selection of the PO has succeeded\n");

        /* Retrieve the data read from the CalyspoPo updated during the transaction process */
        std::shared_ptr<ElementaryFile> efEnvironmentAndHolder =
                calypsoPo->getFileBySfi(CalypsoClassicInfo::SFI_EnvironmentAndHolder);
        const std::string environmentAndHolder =
                ByteArrayUtil::toHex(efEnvironmentAndHolder->getData()->getContent());

        // Log the result
        logger->info("EnvironmentAndHolder file data: %\n", environmentAndHolder);


        // Go on with the reading of the first record of the EventLog file
        logger->info("= #### 2nd PO exchange: reading transaction of the EventLog file\n");

        PoTransaction poTransaction(std::make_shared<SeResource<CalypsoPo>>(poReader, calypsoPo));

        /*
         * Prepare the reading order and keep the associated parser for later use once the
         * transaction has been processed.
         */
        poTransaction.prepareReadRecordFile(CalypsoClassicInfo::SFI_EventLog,
                                            CalypsoClassicInfo::RECORD_NUMBER_1);

        /*
         * Actual PO communication: send the prepared read order, then close the channel with
         * the PO
         */
        poTransaction.prepareReleasePoChannel();
        poTransaction.processPoCommands();
        logger->info("The reading of the EventLog has succeeded\n");

        /* Retrieve the data read from the CalyspoPo updated during the transaction process */
        std::shared_ptr<ElementaryFile> efEventLog =
            calypsoPo->getFileBySfi(CalypsoClassicInfo::SFI_EventLog);
        const std::string eventLog = ByteArrayUtil::toHex(efEventLog->getData()->getContent());

        /* Log the result */
        logger->info("EventLog file data: %\n", eventLog);

        logger->info("= #### End of the Calypso PO processing\n");
    } else {
        logger->error("The selection of the PO has failed\n");
    }

    logger->info("Remove stub PO\n");
    poReader->removeSe();

    return 0;
}
