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

/* Calypso */
#include "AbstractSamResponseParser.h"
#include "KeypleCalypsoExport.h"
#include "UnlockCmdBuild.h"

namespace keyple {
namespace calypso {
namespace command {
namespace sam {
namespace parser {
namespace security {

using namespace keyple::calypso::command::sam;
using namespace keyple::calypso::command::sam::builder::security;

/**
 * Unlock response parser.
 */
class KEYPLECALYPSO_API UnlockRespPars final : public AbstractSamResponseParser {
public:
    /**
     * Instantiates a new keyple::calypso::command::sam::parser::security::UnlockRespPars
     *
     * @param response the response
     * @param builder the reference to the builder that created this parser
     */
    UnlockRespPars(const std::shared_ptr<ApduResponse> response, UnlockCmdBuild* builder);

protected:
    /**
     *
     */
    const std::map<int, std::shared_ptr<StatusProperties>>& getStatusTable() const override;

private:
    /**
     *
     */
    static const std::map<int, std::shared_ptr<StatusProperties>> STATUS_TABLE;
};

}
}
}
}
}
}
