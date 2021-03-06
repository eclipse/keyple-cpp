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

#include "SelectFileCmdBuild.h"

/* Calypso */
#include "SelectFileRespPars.h"

/* Core */
#include "ApduResponse.h"
#include "ByteArrayUtil.h"

/* Common */
#include "IllegalStateException.h"
#include "stringhelper.h"

namespace keyple {
namespace calypso {
namespace command {
namespace po {
namespace builder {

using namespace keyple::calypso::command::po;
using namespace keyple::calypso::command;
using namespace keyple::calypso::command::po::parser;
using namespace keyple::common;
using namespace keyple::common::exception;
using namespace keyple::core::seproxy::message;
using namespace keyple::core::util;

SelectFileCmdBuild::SelectFileCmdBuild(const PoClass& poClass,
                                       const SelectFileControl selectFileControl)
: AbstractPoCommandBuilder<SelectFileRespPars>(
      std::make_shared<CalypsoPoCommand>(CalypsoPoCommand::SELECT_FILE),
      nullptr),
  mPath({}),
  mSelectFileControl(selectFileControl)
{
    const uint8_t cla = poClass.getValue();
    uint8_t p1;
    uint8_t p2;

    const std::vector<uint8_t> selectData = {0x00, 0x00};
    switch (selectFileControl) {
    case SelectFileControl::FIRST_EF:
        p1 = 0x02;
        p2 = 0x00;
        break;
    case SelectFileControl::NEXT_EF:
        p1 = 0x02;
        p2 = 0x02;
        break;
    case SelectFileControl::CURRENT_DF:
        p1 = 0x09;
        p2 = 0x00;
        break;
    default:
        throw IllegalStateException("Unsupported selectFileControl parameter " +
                                    StringHelper::toString(selectFileControl));
    }

    mRequest = setApduRequest(cla, command, p1, p2, selectData, 0x00);

    const std::string extraInfo = "SELECTIONCONTROL=" + StringHelper::toString(selectFileControl);
    addSubName(extraInfo);
}

SelectFileCmdBuild::SelectFileCmdBuild(
  const PoClass& poClass, const std::vector<uint8_t>& selectionPath)
: AbstractPoCommandBuilder<SelectFileRespPars>(
      std::make_shared<CalypsoPoCommand>(CalypsoPoCommand::SELECT_FILE),
      nullptr),
  mPath(selectionPath),
  mSelectFileControl(SelectFileControl::NONE)
{
    /* Handle the REV1 case */
    const uint8_t p1 = poClass == PoClass::LEGACY ? 0x08 : 0x09;

    mRequest = setApduRequest(poClass.getValue(), command, p1, 0x00, selectionPath, 0x00);

    const std::string extraInfo = "SELECTIONPATH=" + ByteArrayUtil::toHex(selectionPath);
    addSubName(extraInfo);
}

std::shared_ptr<SelectFileRespPars> SelectFileCmdBuild::createResponseParser(
    std::shared_ptr<ApduResponse> apduResponse)
{
    return std::make_shared<SelectFileRespPars>(apduResponse, this);
}

bool SelectFileCmdBuild::isSessionBufferUsed() const
{
    return false;
}

const std::vector<uint8_t>& SelectFileCmdBuild::getPath() const
{
    return mPath;
}

SelectFileControl SelectFileCmdBuild::getSelectFileControl() const
{
    return mSelectFileControl;
}

}
}
}
}
}
