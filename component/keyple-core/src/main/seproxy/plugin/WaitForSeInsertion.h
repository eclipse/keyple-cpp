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

/* Core */
#include "AbstractMonitoringJob.h"
#include "AbstractObservableState.h"
#include "AbstractObservableLocalReader.h"
#include "KeypleCoreExport.h"

/* Common */
#include "LoggerFactory.h"

namespace keyple {
namespace core {
namespace seproxy {
namespace plugin {

/**
 * Wait for Se Insertion State
 * <p>
 * The state during which the insertion of an SE is expected.
 * <ul>
 * <li>Upon SE_INSERTED event, the default selection is processed if required and if the conditions
 * are met (ALWAYS or SE MATCHED) the machine changes state for WAIT_FOR_SE_PROCESSING.
 * <li>Upon STOP_DETECT event, the machine changes state for WAIT_FOR_SE_DETECTION.
 * <li>Upon SE_REMOVED event, the machine changes state for WAIT_FOR_SE_DETECTION.
 * </ul>
 */
class KEYPLECORE_API WaitForSeInsertion final : public AbstractObservableState {
public:
    /**
     *
     */
    WaitForSeInsertion(AbstractObservableLocalReader* reader);

    /**
     *
     */
    WaitForSeInsertion(AbstractObservableLocalReader* reader,
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
    const std::shared_ptr<Logger> mLogger = LoggerFactory::getLogger(typeid(WaitForSeInsertion));
};

}
}
}
}
