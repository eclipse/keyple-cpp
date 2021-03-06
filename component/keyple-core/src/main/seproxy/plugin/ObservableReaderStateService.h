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

#include <map>

/* Common */
#include "LoggerFactory.h"

/* Core */
#include "AbstractObservableLocalReader.h"
#include "AbstractObservableState.h"
#include "KeypleCoreExport.h"

namespace keyple {
namespace core {
namespace seproxy {
namespace plugin {

/**
 * Manages the internal state of an AbstractObservableLocalReader Process InternalEvent against the
 * current state
 */
class KEYPLECORE_API ObservableReaderStateService final {
public:
    /**
     *
     */
    ObservableReaderStateService(
        AbstractObservableLocalReader* reader,
        std::map<MonitoringState, std::shared_ptr<AbstractObservableState>> states,
        const MonitoringState initState);

    /**
     *
     */
    ~ObservableReaderStateService() = default;

    /**
     * Thread safe method to communicate an internal event to this reader Use this method to inform
     * the reader of external event like a tag discovered or a Se inserted
     *
     * @param event internal event
     */
    void onEvent(const InternalEvent event);

    /**
     * Thread safe method to switch the state of this reader should only be invoked by this reader
     * or its state
     *
     * @param stateId : next state to onActivate
     */
    void switchState(const MonitoringState stateId);

    /**
     * Get the reader current monitoring state
     *
     * @return current monitoring state
     */
    const MonitoringState& getCurrentMonitoringState() const;

    /**
     * C++ vs. Java: added this function to stop all potential threads
     *
     */
    std::map<MonitoringState, std::shared_ptr<AbstractObservableState>>& getStates()
    {
        return mStates;
    }

protected:
    /**
     * Get reader current state
     *
     * @return reader current state
     */
    const std::shared_ptr<AbstractObservableState> getCurrentState() const;



private:
    /**
     * Logger
     */
    const std::shared_ptr<Logger> mLogger =
        LoggerFactory::getLogger(typeid(ObservableReaderStateService));

    /**
     * AbstractObservableLocalReader to manage event and states
     */
    AbstractObservableLocalReader* mReader;

    /**
     * Map of all instantiated states possible
     */
    std::map<MonitoringState, std::shared_ptr<AbstractObservableState>> mStates;

    /**
     * Current currentState of the Observable Reader
     */
    std::shared_ptr<AbstractObservableState> mCurrentState;
};

}
}
}
}
