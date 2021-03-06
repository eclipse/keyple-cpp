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

#include <ostream>

#include "KeypleCoreExport.h"

namespace keyple {
namespace core {
namespace seproxy {
namespace protocol {

/**
 *
 */
enum class TransmissionMode { NONE = 0, CONTACTS, CONTACTLESS };

/**
 *
 */
KEYPLECORE_API std::ostream& operator<<(std::ostream& os,
                                        const TransmissionMode& tm);

}
}
}
}
