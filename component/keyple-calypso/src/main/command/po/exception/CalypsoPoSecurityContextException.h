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

#include "CalypsoPoCommand.h"
#include "CalypsoPoCommandException.h"

namespace keyple {
namespace calypso {
namespace command {
namespace po {
namespace exception {

/**
 * The exception {@code CalypsoPoSecurityContextException} indicates that the
 * security conditions are not fulfilled (e.g. no session, wrong key).
 */
class CalypsoPoSecurityContextException final
: public CalypsoPoCommandException {
public:
    /**
     * @param message the message to identify the exception context
     * @param command the Calypso PO command
     * @param statusCode the status code
     */
    CalypsoPoSecurityContextException(
      const std::string& message,
      const std::shared_ptr<CalypsoPoCommand> command,
      const int statusCode)
    : CalypsoPoCommandException(message, command, statusCode) {}
};

}
}
}
}
}
