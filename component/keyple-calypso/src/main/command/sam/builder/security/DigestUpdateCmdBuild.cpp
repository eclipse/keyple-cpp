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

#include "DigestUpdateCmdBuild.h"

/* Common */
#include "IllegalArgumentException.h"

/* Calypso */
#include "DigestUpdateRespPars.h"

namespace keyple {
namespace calypso {
namespace command {
namespace sam {
namespace builder {
namespace security {

using namespace keyple::calypso::command::sam;
using namespace keyple::calypso::command::sam::parser::security;
using namespace keyple::common::exception;

DigestUpdateCmdBuild::DigestUpdateCmdBuild(const SamRevision& revision,
                                           const bool encryptedSession,
                                           const std::vector<uint8_t>& digestData)
: AbstractSamCommandBuilder(
    std::make_shared<CalypsoSamCommand>(CalypsoSamCommand::DIGEST_UPDATE),
    nullptr)
{
    if (revision != SamRevision::NO_REV)
        mDefaultRevision = revision;

    const uint8_t cla = mDefaultRevision.getClassByte();
    const uint8_t p1 = 0x00;
    const uint8_t p2  = encryptedSession ? 0x80 : 0x00;

    if (digestData.size() == 0 || digestData.size() > 255)
        throw IllegalArgumentException("Digest data null or too long!");

    mRequest = setApduRequest(cla, mCommand, p1, p2, digestData);
}

std::shared_ptr<DigestUpdateRespPars> DigestUpdateCmdBuild::createResponseParser(
        const std::shared_ptr<ApduResponse> apduResponse)
{
    return std::make_shared<DigestUpdateRespPars>(apduResponse, this);
}

}
}
}
}
}
}
