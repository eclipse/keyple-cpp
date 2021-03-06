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

/* Common */
#include "IllegalStateException.h"
#include "LoggerFactory.h"

/* Core */
#include "SeCommonProtocols.h"
#include "SeProxyService.h"
#include "StubPlugin.h"
#include "StubPluginFactory.h"
#include "StubReader.h"

/* Examples */
#include "CalypsoClassicTransactionEngine.h"
#include "StubCalypsoClassic.h"
#include "StubSamCalypsoClassic.h"
#include "StubProtocolSetting.h"

using namespace keyple::common;
using namespace keyple::common::exception;
using namespace keyple::example::calypso::common::transaction;
using namespace keyple::example::calypso::pc::stub::se;
using namespace keyple::plugin::stub;
using namespace keyple::core::seproxy;
using namespace keyple::core::seproxy::event;
using namespace keyple::core::seproxy::exception;
using namespace keyple::core::seproxy::protocol;

class Demo_CalypsoClassic_Stub {
};

std::shared_ptr<Logger> logger =
    LoggerFactory::getLogger(typeid(Demo_CalypsoClassic_Stub));

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    /* Get the instance of the SeProxyService (Singleton pattern) */
    SeProxyService& seProxyService = SeProxyService::getInstance();

    const std::string STUB_PLUGIN_NAME = "stub1";

    /* Register Stub plugin in the platform */
    std::shared_ptr<ReaderPlugin> stubPlugin =
        seProxyService.registerPlugin(std::make_shared<StubPluginFactory>(STUB_PLUGIN_NAME));

    /* Setting up the transaction engine (implements Observer) */
    std::shared_ptr<CalypsoClassicTransactionEngine> transactionEngine =
        std::make_shared<CalypsoClassicTransactionEngine>();


    /* Plug PO and SAM stub readers */
    std::dynamic_pointer_cast<StubPlugin>(stubPlugin)->plugStubReader("poReader", true);
    std::dynamic_pointer_cast<StubPlugin>(stubPlugin)->plugStubReader("samReader", true);

    std::shared_ptr<StubReader> poReader = nullptr;
    std::shared_ptr<StubReader> samReader = nullptr;
    try {
        poReader = std::dynamic_pointer_cast<StubReader>(
            stubPlugin->getReader("poReader"));
        samReader = std::dynamic_pointer_cast<StubReader>(
            stubPlugin->getReader("samReader"));
    } catch (const KeypleReaderNotFoundException& e) {
        logger->error("update - KeypleReaderNotFoundException: %\n", e);
    }

    /* Both readers are expected not null */
    if (poReader == samReader || poReader == nullptr || samReader == nullptr)
        throw IllegalStateException("Bad PO/SAM setup");

    logger->info("PO Reader  NAME = %\n", poReader->getName());
    logger->info("SAM Reader  NAME = %\n", samReader->getName());

    /* Set the PO reader protocol flag */
    poReader->addSeProtocolSetting(SeCommonProtocols::PROTOCOL_ISO14443_4,
                                   StubProtocolSetting::STUB_PROTOCOL_SETTING
                                      [SeCommonProtocols::PROTOCOL_ISO14443_4]);
    poReader->addSeProtocolSetting(SeCommonProtocols::PROTOCOL_B_PRIME,
                                   StubProtocolSetting::STUB_PROTOCOL_SETTING
                                       [SeCommonProtocols::PROTOCOL_B_PRIME]);

    /* Assign readers to the Hoplink transaction engine */
    transactionEngine->setReaders(poReader, samReader);

    /* Create 'virtual' Hoplink and SAM SE */
    std::shared_ptr<StubSecureElement> calypsoStubSe =
        std::make_shared<StubCalypsoClassic>();
    std::shared_ptr<StubSecureElement> samSE =
        std::make_shared<StubSamCalypsoClassic>();

    /* Insert the SAM into the SAM reader */
    logger->info("Insert stub SAM SE\n");
    samReader->insertSe(samSE);

    /* Set the default selection operation */
    poReader->setDefaultSelectionRequest(transactionEngine->preparePoSelection(),
                                         ObservableReader::NotificationMode::MATCHED_ONLY,
                                         ObservableReader::PollingMode::REPEATING);

    /* Set the transactionEngine as Observer of the PO reader */
    poReader->addObserver(transactionEngine);

    logger->info("Insert stub PO SE\n");
    poReader->insertSe(calypsoStubSe);

    Thread::sleep(1000);

    /* Remove SE */
    logger->info("Remove stub SAM and PO SE\n");

    poReader->removeSe();
    samReader->removeSe();

    logger->info("END\n");

    exit(0);
}
