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

#include <memory>

/* Calypso */
#include "AbstractPoCommandBuilder.h"
#include "CalypsoPoCommand.h"
#include "PoClass.h"

/* Calypso */
#include "KeypleCalypsoExport.h"

/* Forward declaration */
namespace keyple { namespace calypso { namespace command { namespace po {
    namespace parser { class GetDataFciRespPars; } } } } }

namespace keyple {
namespace calypso {
namespace command {
namespace po {
namespace builder {

using namespace keyple::calypso::command;
using namespace keyple::calypso::command::po;
using namespace keyple::calypso::command::po::parser;
using namespace keyple::core::seproxy::message;

/**
* This class provides the dedicated constructor to build the Get data APDU
* commands.
*
* This command can not be sent in session because it would generate a 6Cxx
* status in contact mode and thus make calculation of the digest impossible.
*
*/
class KEYPLECALYPSO_API GetDataFciCmdBuild final
: public AbstractPoCommandBuilder<GetDataFciRespPars> {
public:
    /**
     * Instantiates a new GetDataFciCmdBuild.
     *
     * @param poClass indicates which CLA byte should be used for the Apdu
     */
    GetDataFciCmdBuild(PoClass poClass);

    /**
     *
     */
    std::shared_ptr<GetDataFciRespPars> createResponseParser(
        std::shared_ptr<ApduResponse> apduResponse) override;

    /**
     * This command doesn't modify the contents of the PO and therefore doesn't
     * uses the session buffer.
     *
     * @return false
     */
    bool isSessionBufferUsed() const override;

private:
    /**
     *
     */
    const CalypsoPoCommand& command = CalypsoPoCommand::GET_DATA_FCI;
};

}
}
}
}
}
