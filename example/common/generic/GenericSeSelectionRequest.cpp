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

#include "GenericSeSelectionRequest.h"

/* Core */
#include "ChannelControl.h"

namespace keyple {
namespace example {
namespace generic {
namespace common {

using GenericMatchingSe = GenericSeSelectionRequest::GenericMatchingSe;

/* GENERIC MATCHING SE -------------------------------------------------------------------------- */

GenericMatchingSe::GenericMatchingSe(std::shared_ptr<SeResponse> selectionResponse,
                                     const TransmissionMode& transmissionMode)
: AbstractMatchingSe(selectionResponse, transmissionMode) {}

/* GENERIC SE SELECTION REQUEST ----------------------------------------------------------------- */

GenericSeSelectionRequest::GenericSeSelectionRequest(std::shared_ptr<SeSelector> seSelector)
: AbstractSeSelectionRequest(seSelector),
  mTransmissionMode(seSelector->getSeProtocol()->getTransmissionMode()) {}

const std::shared_ptr<AbstractMatchingSe> GenericSeSelectionRequest::parse(
    std::shared_ptr<SeResponse> seResponse)
{
    return std::make_shared<AbstractMatchingSe>(seResponse, mTransmissionMode);
}

}
}
}
}
