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

#include "StubSe2.h"
#include "ByteArrayUtil.h"

namespace keyple {
namespace example {
namespace common {
namespace calypso {
namespace stub {

using namespace keyple::core::util;
using namespace keyple::plugin::stub;

const std::string StubSe2::seProtocol = "PROTOCOL_ISO14443_4";

StubSe2::StubSe2() {}

const std::vector<uint8_t>& StubSe2::getATR()
{
    return atr;
}

std::string StubSe2::getSeProcotol()
{
    return seProtocol;
}

}
}
}
}
}
