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

#include "Exception.h"

namespace keyple {
namespace common {
namespace exception {

class InterruptedException : public Exception {
public:
    /**
     *
     */
    InterruptedException(const std::string& name) : Exception(name) {}

    /**
     *
     */
    InterruptedException(const std::string& name, const std::exception& cause)
    : Exception(name, cause) {}
};

}
}
}
