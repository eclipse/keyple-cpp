/**************************************************************************************************
 * Copyright (c) 2018 Calypso Networks Association                                                *
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
#include "KeypleCoreExport.h"
#include "ExecutorService.h"

namespace keyple {
namespace core {
namespace seproxy {
namespace plugin {

using namespace keyple::common;

class AbstractObservableLocalReader;
enum class InternalEvent;

/**
 * The states that the reader monitoring currentState machine can have
 */
enum class MonitoringState {
    WAIT_FOR_START_DETECTION,
    WAIT_FOR_SE_INSERTION,
    WAIT_FOR_SE_PROCESSING,
    WAIT_FOR_SE_REMOVAL
};

/**
 *
 */
KEYPLECORE_API std::ostream& operator<<(std::ostream& os, const MonitoringState& ms);

/**
 * Defines a state behaviour for a keyple::core::seproxy::plugin::AbstractObservableLocalReader.
 * Handles keyple::core::seproxy::plugin::InternalEvent that might results on a switch of state.
 */
class KEYPLECORE_API AbstractObservableState {
public:
    /**
     * Get the current state identifier of the state machine
     *
     * @return the current state identifier
     */
    const MonitoringState& getMonitoringState() const;

    /**
     * Handle Internal Event Usually state is switched using method reader::switchState
     *
     * @param event internal event received by reader
     */
    virtual void onEvent(const InternalEvent event) = 0;

    /**
     * Invoked when activated, a custom behaviour can be added here
     */
    void onActivate();

    /**
     * Invoked when deactivated
     */
    void onDeactivate();

    /**
     * C++ vs. Java: protected in Java, public in C++ to try and workaround threading issues
     *
     * Background job definition if any
     */
    std::shared_ptr<AbstractMonitoringJob> mMonitoringJob;

protected:

    /**
     * Identifier of the currentState
     */
    MonitoringState mState;

    /**
     * Reference to Reader
     */
    AbstractObservableLocalReader* mReader;

    /**
     * Result of the background job if any
     */
    std::future<void>* mMonitoringEvent;

    /**
     * Executor service used to execute AbstractMonitoringJob
     */
    std::shared_ptr<ExecutorService> mExecutorService;

    /**
     *
     */
    std::atomic<bool> mCancellationFlag;

    /**
     * Create a new state with a state identifier and a monitor job
     *
     * @param state the state identifier
     * @param reader the current reader
     * @param monitoringJob the job to be executed in background (may be null if no background job
     *                      is required)
     * @param executorService the executor service
     */
    AbstractObservableState(MonitoringState state,
                            AbstractObservableLocalReader* reader,
                            std::shared_ptr<AbstractMonitoringJob> monitoringJob,
                            std::shared_ptr<ExecutorService> executorService);

    /**
     * Create a new state with a state identifier
     *
     * @param reader : observable reader this currentState is attached to
     * @param state : name of the currentState
     */
    AbstractObservableState(MonitoringState state, AbstractObservableLocalReader* reader);

    /**
     *
     */
    virtual ~AbstractObservableState() = default;

    /**
     * Switch state in the parent reader
     *
     * @param stateId the new state
     */
    void switchState(MonitoringState stateId);

private:
    /**
     *
     */
    const std::shared_ptr<Logger> mLogger= LoggerFactory::getLogger(typeid(AbstractObservableState));
};

}
}
}
}
