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

/**
 * Wait for Se Removal State
 * <p>
 * The state in which the SE is still present and awaiting removal.
 * <ul>
 * <li>Upon SE_REMOVED event, the machine changes state for WAIT_FOR_SE_INSERTION or
 * WAIT_FOR_SE_DETECTION according to the {@link ObservableReader.PollingMode} setting.
 * <li>Upon STOP_DETECT event, the machine changes state for WAIT_FOR_SE_DETECTION.
 * </ul>
 */
class KEYPLECORE_API WaitForSeRemoval final : public AbstractObservableState {
public:
    /**
     *
     */
    WaitForSeRemoval(AbstractObservableLocalReader* reader);

    /**
     *
     */
    WaitForSeRemoval(AbstractObservableLocalReader* reader,
                     std::shared_ptr<AbstractMonitoringJob> monitoringJob,
                     std::shared_ptr<ExecutorService> executorService);

    /**
     *
     */
    void onEvent(const InternalEvent event) override;

private:
    /**
     * Logger
     */
    const std::shared_ptr<Logger> mLogger = LoggerFactory::getLogger(typeid(WaitForSeRemoval));
};

}
}
}
}
