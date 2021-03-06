/******************************************************************************
 * Copyright (c) 2018 Calypso Networks Association                            *
 * https://www.calypsonet-asso.org/                                           *
 *                                                                            *
 * See the NOTICE file(s) distributed with this work for additional           *
 * information regarding copyright ownership.                                 *
 *                                                                            *
 * This program and the accompanying materials are made available under the   *
 * terms of the Eclipse Public License 2.0 which is available at              *
 * http://www.eclipse.org/legal/epl-2.0                                       *
 *                                                                            *
 * SPDX-License-Identifier: EPL-2.0                                           *
 ******************************************************************************/

#pragma once

#include <list>
#include <string>
#include <vector>
#include <stdexcept>
#include <memory>

/* Common */
#include "Object.h"

/* Core */
#include "ApduResponse.h"
#include "KeypleCoreExport.h"
#include "SelectionStatus.h"

namespace keyple {
namespace core {
namespace seproxy {
namespace message {

using namespace keyple::common;

/**
 * Group of SE responses received in response to a keyple::core::seproxy::message::SeRequest.
 *
 * @see SeRequest
 */
class KEYPLECORE_API SeResponse final {
public:
    /**
     * the constructor called by a ProxyReader during the processing of the
     * ‘transmit’ method.
     *
     * @param logicalChannelIsOpen the current channel status
     * @param channelPreviouslyOpen the channel previously open
     * @param selectionStatus the SE selection status
     * @param apduResponses the apdu responses
     */
    SeResponse(const bool logicalChannelIsOpen,
               const bool channelPreviouslyOpen,
               std::shared_ptr<SelectionStatus> selectionStatus,
               const std::vector<std::shared_ptr<ApduResponse>>& apduResponses);

    /**
     * Was channel previously open.
     *
     * @return the previous currentState of the logical channel.
     */
    bool wasChannelPreviouslyOpen() const;

    /**
     * Get the logical channel status
     *
     * @return true if the logical channel is open
     */
    bool isLogicalChannelOpen() const;

    /**
     * Gets the selection status and its associated data.
     *
     * @return a keyple::core::seproxy::message::SelectionStatus object.
     */
    const std::shared_ptr<SelectionStatus> getSelectionStatus() const;

    /**
     * Gets the apdu responses.
     *
     * @return the group of APDUs responses returned by the SE application for
     *         this instance of SEResponse.
     */
    std::vector<std::shared_ptr<ApduResponse>>& getApduResponses();

    /**
     *
     */
    bool operator==(const SeResponse& o) const;
    /**
     *
     */
    bool operator!=(const SeResponse& o) const;

	/**
	 *
	 */
    friend KEYPLECORE_API std::ostream& operator<<(std::ostream& os,
                                                   const SeResponse& sr);

    /**
     *
     */
    friend KEYPLECORE_API std::ostream& operator<<(
		    std::ostream& os, const std::shared_ptr<SeResponse>& sr);

    /**
     *
     */
    friend KEYPLECORE_API std::ostream& operator<<(
		    std::ostream& os, const std::vector<std::shared_ptr<SeResponse>>& sr);

private:
    /**
     * is defined as true by the SE reader in case a logical channel was already
     * open with the target SE application.
     */
    const bool mChannelPreviouslyOpen;

    /**
     * true if the channel is open
     */
    const bool mLogicalChannelIsOpen;

    /**
     *
     */
    const std::shared_ptr<SelectionStatus> mSelectionStatus;

    /**
     * could contain a group of APDUResponse returned by the selected SE
     * application on the SE reader.
     */
    std::vector<std::shared_ptr<ApduResponse>> mApduResponses;
};

}
}
}
}
