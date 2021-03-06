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

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "AppendRecordRespPars.h"

/* Core */
#include "ApduResponse.h"
#include "ByteArrayUtil.h"
#include "KeypleSeCommandException.h"

using namespace testing;

using namespace keyple::calypso::command::po::parser;
using namespace keyple::core::command::exception;
using namespace keyple::core::seproxy::message;
using namespace keyple::core::util;

static const std::string SW1SW2_KO = "6A82";
static const std::string SW1SW2_OK = "9000";

TEST(AppendRecordRespParsTest, appendRecordRespPars_badStatus)
{
    AppendRecordRespPars appendRecordRespPars(
            std::make_shared<ApduResponse>(
                ByteArrayUtil::fromHex(SW1SW2_KO), nullptr),
            nullptr);

    EXPECT_THROW(appendRecordRespPars.checkStatus(), KeypleSeCommandException);
}

TEST(AppendRecordRespParsTest, appendRecordRespPars_goodStatus)
{
    AppendRecordRespPars appendRecordRespPars(
            std::make_shared<ApduResponse>(
                ByteArrayUtil::fromHex(SW1SW2_OK), nullptr),
            nullptr);

    appendRecordRespPars.checkStatus();
}
