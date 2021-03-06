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
#include <memory>

/* Core */
#include "AbstractSamResponseParser.h"
#include "KeypleCalypsoExport.h"
#include "SvCheckCmdBuild.h"

namespace keyple {
namespace calypso {
namespace command {
namespace sam {
namespace parser {
namespace security {

using namespace keyple::calypso::command::sam;
using namespace keyple::calypso::command::sam::builder::security;
using namespace keyple::core::seproxy::message;

/**
 * Select diversifier response parser. See specs: Calypso / page 54 / 7.4.2 -
 * Session MAC computation
 */
class KEYPLECALYPSO_API SvCheckRespPars final
: public AbstractSamResponseParser {
public:
    /**
     * Instantiates a new SvCheckRespPars.
     *
     * @param response from the SAM
     * @param builder the reference to the builder that created this parser
     */
    SvCheckRespPars(const std::shared_ptr<ApduResponse> response,
                    SvCheckCmdBuild* builder);

protected:
    /**
     *
     */
    const std::map<int, std::shared_ptr<StatusProperties>>&
        getStatusTable() const override;

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
