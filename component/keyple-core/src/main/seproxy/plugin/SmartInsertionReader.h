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

/* Core */
#include "ObservableReaderNotifier.h"

namespace keyple {
namespace core {
namespace seproxy {
namespace plugin {

using namespace keyple::core::seproxy::event;

class SmartInsertionReader : public virtual ObservableReaderNotifier {
public:
    /**
     *
     */
    virtual ~SmartInsertionReader()
    {
        stopWaitForCard();
    }

    /**
     * Waits for a SE. Returns true if a SE is detected before the end of the provided timeout.
     * <p>
     * This method must be implemented by the plugin's reader class when it implements the
     * keyple::core::seproxy::plugin::SmartInsertionReader interface.
     * <p>
     * Returns false if no SE is detected
     *
     * @return presence status
     * @throw KeypleReaderIOException if the communication with the reader or the SE has failed
     *        (disconnection)
     */
    virtual bool waitForCardPresent() = 0;

    /**
     * Interrupts the waiting of a SE
     */
    virtual void stopWaitForCard() {}
};

}
}
}
}
