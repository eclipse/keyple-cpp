/******************************************************************************
 * Copyright (c) 2020 Calypso Networks Association                            *
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

#include <vector>
#include <memory>

/* Calypso */
#include "AbstractPoResponseParser.h"
#include "KeypleCalypsoExport.h"
#include "PoGetChallengeCmdBuild.h"

namespace keyple {
namespace calypso {
namespace command {
namespace po {
namespace parser {
namespace security {

using namespace keyple::calypso::command::po::builder::security;
using namespace keyple::core::command;
using namespace keyple::core::seproxy::message;

/**
 * PO Get challenge response parser. See specs: Calypso / page 108 / 9.54 - Get
 * challenge
 */
class KEYPLECALYPSO_API PoGetChallengeRespPars final
: public AbstractPoResponseParser {
public:
    /**
     * Instantiates a new PoGetChallengeRespPars.
     *
     * @param response the response from PO Get Challenge APDU Command
     * @param builder the reference to the builder that created this parser
     */
    PoGetChallengeRespPars(std::shared_ptr<ApduResponse> response,
                           PoGetChallengeCmdBuild* builder);

    /**
     *
     */
    std::vector<uint8_t> getPoChallenge() const;
};

}
}
}
}
}
}
