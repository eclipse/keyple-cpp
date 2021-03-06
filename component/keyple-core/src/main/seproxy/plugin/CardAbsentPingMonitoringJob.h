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

#pragma once

/* Common */
#include "LoggerFactory.h"

/* Core */
#include "AbstractMonitoringJob.h"
#include "AbstractObservableLocalReader.h"
#include "AbstractObservableState.h"
#include "KeypleCoreExport.h"

namespace keyple {
namespace core {
namespace seproxy {
namespace plugin {

using namespace keyple::common;

/**
 * Ping the SE to detect removal thanks to the method
 * {@link AbstractObservableLocalReader#isSePresentPing()}. This method is invoked in another
 * thread.
 * <p>
 * This job should be used by readers who do not have the ability to natively detect the
 * disappearance of the SE at the end of the transaction.
 * <p>
 * It is based on sending a neutral APDU command as long as the SE is responding, an internal
 * SE_REMOVED event is fired when the SE is no longer responding.
 * <p>
 * By default a delay of 200 ms is inserted between each APDU sending .
 */
class KEYPLECORE_API CardAbsentPingMonitoringJob final : public AbstractMonitoringJob {
public:
    /**
     * Create a job monitor job that ping the SE with the method isSePresentPing()
     *
     * @param reader : reference to the reader
     */
    CardAbsentPingMonitoringJob(AbstractObservableLocalReader* reader);

    /**
     * Create a job monitor job that ping the SE with the method isSePresentPing()
     *
     * @param reader : reference to the reader
     * @param removalWait : delay between between each APDU sending
     */
    CardAbsentPingMonitoringJob(AbstractObservableLocalReader* reader, long removalWait);

    /**
     * (package-private)<br>
     */
    std::future<void> startMonitoring(AbstractObservableState* state,
                                      std::atomic<bool>& cancellationFlag) override;

    /**
     *
     */
    void monitoringJob(AbstractObservableState* state, std::atomic<bool>& cancellationFlag);

    /**
     * (package-private)<br>
     */
    void stop() override;

private:
    /**
     *
     */
    const std::shared_ptr<Logger> mLogger =
        LoggerFactory::getLogger(typeid(CardAbsentPingMonitoringJob));

    /**
     *
     */
    AbstractObservableLocalReader* mReader;

    /**
     *
     */
    std::atomic<bool> mLoop;

    /**
     *
     */
    long mRemovalWait = 200;
};

}
}
}
}
