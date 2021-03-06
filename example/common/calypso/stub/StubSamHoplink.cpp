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

#include "StubSamHoplink.h"
#include "ByteArrayUtil.h"

namespace keyple {
namespace example {
namespace calypso {
namespace pc {
namespace stub {
namespace se {

using namespace keyple::plugin::stub;
using namespace keyple::core::util;

const std::string StubSamHoplink::seProtocol = "PROTOCOL_ISO7816_3";

StubSamHoplink::StubSamHoplink()
{
    /* Select Diversifier */
    addHexCommand("8014 0000 08 0000000011223344", "9000");
    /* Get Challenge */
    addHexCommand("0084000004", "C1C2C3C49000");
    /* Digest Init */
    addHexCommand(
        "808A00FF3A300E03082ED700300E300102030405060708090A0B0C0D0E0F1011121314"
        "15161718191A1B1C1D1E1F202122232425262728292A2B2C2D2E2F30",
        "9000");
    /* Digest Update */
    addHexCommand("808C00000500B201A420", "9000");
    /* Digest Update */
    addHexCommand("808C00002200000000000000000000000000000000000000000000000000"
                  "000000000000009000",
                  "9000");
    /* Digest Update */
    addHexCommand("808C00000500B201D430", "9000");
    /* Digest Update */
    addHexCommand("808C0000320102030405060708090A0B0C0D0E0F10111213141516171819"
                  "1A1B1C1D1E1F202122232425262728292A2B2C2D2E2F309000",
                  "9000");
    /* Digest Update */
    addHexCommand("808C00000500B201A420", "9000");
    /* Digest Update */
    addHexCommand("808C00002200000000000000000000000000000000000000000000000000"
                  "000000000000009000",
                  "9000");
    /* Digest Update */
    addHexCommand("808C00000500B201D430", "9000");
    /* Digest Update */
    addHexCommand("808C0000320102030405060708090A0B0C0D0E0F10111213141516171819"
                  "1A1B1C1D1E1F202122232425262728292A2B2C2D2E2F309000",
                  "9000");
    /* Digest Close */
    addHexCommand("808E000004", "050607089000");
    /* Digest Authenticate */
    addHexCommand("808200000401020304", "9000");
}

std::vector<char> StubSamHoplink::getATR()
{
    return ByteArrayUtil::fromHex(ATR_HEX);
}

std::string StubSamHoplink::getSeProcotol()
{
    return seProtocol;
}

}
}
}
}
}
}

