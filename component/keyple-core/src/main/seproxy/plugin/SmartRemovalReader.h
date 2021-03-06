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

/**
 * Interface implemented by the readers able to handle natively the SE removal process.
 */
class SmartRemovalReader : public virtual ObservableReaderNotifier {
public:
    /**
     *
     */
    virtual ~SmartRemovalReader()
    {
        stopWaitForCardRemoval();
    }

    /**
     * Wait until the SE disappears.
     * <p>
     * This method must be implemented by the plugin's reader class when it implements the
     * {@link SmartRemovalReader} interface. The reader implementation must manage the SE removal
     * process itself. (for example by using the analogous waitForCardAbsent method in the case of a
     * plugin based on smartcard.io [PC/SC]).
     * <p>
     * In the case where the reader plugin is not able to handle the SE removal process itself (not
     * implementing the {@link SmartRemovalReader} interface, then it is managed by the
     * isSePresentPing method defined in this class.
     * <p>
     * Returns true if the SE has disappeared.
     * <p>
     * *
     *
     * @return presence status
     * @throw KeypleReaderIOException if the communication with the reader or the SE has failed
     */
    virtual bool waitForCardAbsentNative() = 0;

    /**
     * Interrupts the waiting of the removal of the SE
     */
    virtual void stopWaitForCardRemoval() {}
};

}
}
}
}
