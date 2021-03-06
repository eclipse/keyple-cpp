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

#include <string>
#include <vector>
#include <memory>

/* Core */
#include "AbstractDefaultSelectionsRequest.h"
#include "KeypleCoreExport.h"
#include "ReaderEvent.h"
#include "SeReader.h"

namespace keyple {
namespace core {
namespace seproxy {
namespace event {

using namespace keyple::core::seproxy;

/**
 * The ObservableReader interface provides the API for observable readers.
 * <ul>
 * <li>Observer management
 * <li>Start/stop of SE detection
 * <li>Managing the default selection
 * <li>Definition of polling and notification modes
 * </ul>
 */
class KEYPLECORE_API ObservableReader : public virtual SeReader {
public:
    /**
     * Interface to be implemented by reader observers.
     */
    class ReaderObserver {
    public:
        /**
         *
         */
        virtual ~ReaderObserver() = default;

        /**
         *
         */
        virtual void update(const std::shared_ptr<ReaderEvent> event) = 0;
    };

    /**
     * The NotificationMode defines the expected behavior when processing a
     * default selection.
     */
    class KEYPLECORE_API NotificationMode final {
    public:
        /**
         * All SEs presented to readers are notified regardless of the result of
         * the default
         * selection.
         */
        static NotificationMode ALWAYS;

        /**
         * Only SEs that have been successfully selected (logical channel open)
         * will be notified. The others will be ignored and the application will
         * not be aware of them.
         */
        static NotificationMode MATCHED_ONLY;

        /**
         *
         */
        enum class InnerEnum { ALWAYS, MATCHED_ONLY };

        /*
         * Alex: removed 'const'
         *
         * Rationale: error: object of type 'org::eclipse::keyple::seproxy
         * ::event::ObservableReader::NotificationMode' cannot be assigned
         * because its copy assignment operator is implicitly deleted
         *   this->notificationMode = notificationMode;
         *                          ^
         * note: copy assignment operator of 'NotificationMode' is implicitly
         * deleted because field 'innerEnumValue' is of const-qualified type
         * 'const org::eclipse::keyple::seproxy::event::ObservableReader
         * ::NotificationMode::InnerEnum'
         */
        InnerEnum innerEnumValue;

        /**
         *
         */
        NotificationMode(const std::string& nameValue, InnerEnum innerEnum,
                         const std::string& name);

        /**
         *
         */
        NotificationMode(const NotificationMode& o);

        /**
         *
         */
        virtual ~NotificationMode() {}

        /**
         *
         */
        virtual std::string getName();

        /**
         * This method can be used for reverse lookup purpose
         *
         * @param name the enum name
         * @return the corresponding enum
         */
        static NotificationMode get(const std::string& name);

        /**
         *
         */
        bool operator==(const NotificationMode& other);

        /**
         *
         */
        bool operator!=(const NotificationMode& other);

        /**
         *
         */
        NotificationMode& operator=(NotificationMode o);

        /**
         *
         */
        static std::vector<NotificationMode> values();

        /**
         *
         */
        int ordinal();

        /**
         *
         */
        std::string toString();

        /**
         *
         */
        static NotificationMode valueOf(const std::string& name);

    protected:
        /**
         *
         */
        std::string name;

    private:
        /**
         *
         */
        static std::vector<NotificationMode> valueList;

        /*
         * Alex: removed 'const'
         *
         * Rationale: error: object of type 'org::eclipse::keyple::seproxy
         * ::event::ObservableReader::NotificationMode' cannot be assigned
         * because its copy assignment operator is implicitly deleted
         *   this->notificationMode = notificationMode;
         *                          ^
         * note: copy assignment operator of 'NotificationMode' is implicitly
         * deleted becaus field 'nameValue' has no copy assignment operator
         *   const std::string nameValue;
         *                     ^
         */
        std::string nameValue;

        /*
         * Alex: removed 'const'
         * Rationale: same as above
         */
        int ordinalValue;

        /**
         *
         */
        static int nextOrdinal;

        /**
         * Reverse Lookup Implementation
         * <p>
         * The purpose of the lookup Map and its associated method is to allow
         * the serialization and deserialization of the enum of the notification
         * mode, especially in remote context.
         */
        static const std::map<std::string, NotificationMode> lookup;

        /**
         * Populating the lookup table on loading time
         */
        class StaticConstructor {
        public:
            /**
             *
             */
            StaticConstructor()
            {
                // for (NotificationMode env : NotificationMode.values())
                // {
                //     lookup.put(env.getName(), env);
                // }
            }
        };

        /**
         *
         */
        static NotificationMode::StaticConstructor staticConstructor;
    };

    /**
     * Indicates the action to be taken after processing a SE.
     */
    enum class PollingMode {
        /**
         * continue waiting for the insertion of a next SE.
         */
        REPEATING,
        /**
         * stop and wait for a restart signal.
         */
        SINGLESHOT
    };

    /**
     *
     */
    virtual ~ObservableReader() = default;

    /**
     * Add a reader observer.
     * <p>
     * The observer will receive all the events produced by this reader (card insertion, removal,
     * etc.)
     *
     * @param observer the observer object
     */
    virtual void addObserver(const std::shared_ptr<ReaderObserver> observer) = 0;

    /**
     * Remove a reader observer.
     * <p>
     * The observer will nolonger receive any of the events produced by this reader.
     *
     * @param observer the observer object
     */
    virtual void removeObserver(const std::shared_ptr<ReaderObserver> observer) = 0;

    /**
     * Remove all observers at once
     */
    virtual void clearObservers() = 0;

    /**
     * @return the number of observers
     */
    virtual int countObservers() const = 0;

    /**
     * Starts the SE detection. Once activated, the application can be notified of the arrival of an
     * SE.
     *
     * @param pollingMode indicates the action to be followed after processing the SE: if REPEATING,
     *        the SE detection is restarted, if SINGLESHOT, the SE detection is stopped until a new
     *        call to startSeDetection is made.
     */
    virtual void startSeDetection(const PollingMode pollingMode) = 0;

    /**
     * Stops the SE detection.
     * <p>
     * This method must be overloaded by readers depending on the particularity of their management
     * of the start of SE detection.
     */
    virtual void stopSeDetection() = 0;

    /**
     * Defines the selection request to be processed when an SE is inserted. Depending on the SE and
     * the notificationMode parameter, a SE_INSERTED, SE_MATCHED or no event at all will be notified
     * to the application observers.
     *
     * @param defaultSelectionsRequest the selection request to be operated
     * @param notificationMode indicates whether a SE_INSERTED event should be notified even if the
     *        selection has failed (ALWAYS) or whether the SE insertion should be ignored in this
     *        case (MATCHED_ONLY).
     */
    virtual void setDefaultSelectionRequest(
        std::shared_ptr<AbstractDefaultSelectionsRequest> defaultSelectionsRequest,
        const NotificationMode& notificationMode) = 0;

    /**
     * A combination of defining the default selection request and starting the SE detection.
     *
     * @param defaultSelectionsRequest the selection request to be operated
     * @param notificationMode indicates whether a SE_INSERTED event should be notified even if the
     *        selection has failed (ALWAYS) or whether the SE insertion should be ignored in this
     *        case (MATCHED_ONLY).
     * @param pollingMode indicates the action to be followed after processing the SE: if CONTINUE,
     *        the SE detection is restarted, if STOP, the SE detection is stopped until a new call
     *        to startSeDetection is made.
     */
    virtual void setDefaultSelectionRequest(
        std::shared_ptr<AbstractDefaultSelectionsRequest>defaultSelectionsRequest,
        const NotificationMode& notificationMode,
        const PollingMode pollingMode) = 0;

    /**
     * Terminates the processing of the SE, in particular after an interruption by exception<br>
     * Do nothing if the channel is already closed.<br>
     * Channel closing is nominally managed by using the CLOSE_AFTER flag during the last
     * transmission with the SE. However, there are cases where exchanges with the SE are
     * interrupted by an exception, in which case it is necessary to explicitly close the channel
     * using this method.
     */
    virtual void finalizeSeProcessing() = 0;
};

/**
 *
 */
KEYPLECORE_API std::ostream& operator<<(std::ostream& os, const ObservableReader::PollingMode& pm);

}
}
}
}
