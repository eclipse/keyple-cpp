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

#include <stdexcept>
#include <memory>

#include "Object.h"
#include "AnswerToReset.h"

/* Forward class declarations */
namespace keyple {
namespace core {
namespace seproxy {
namespace message {
class ApduResponse;
}
}
}
}

namespace keyple {
namespace core {
namespace seproxy {
namespace message {

class KEYPLECORE_API SelectionStatus
: public std::enable_shared_from_this<SelectionStatus> {
public:
    /**
     *
     */
    SelectionStatus(std::shared_ptr<AnswerToReset> atr,
                    std::shared_ptr<ApduResponse> fci,
                    const bool hasMatched);

    /**
     *
     */
    virtual ~SelectionStatus() {}

    /**
     *
     */
    virtual std::shared_ptr<AnswerToReset> getAtr() const;

    /**
     *
     */
    virtual std::shared_ptr<ApduResponse> getFci() const;

    /**
     *
     */
    bool hasMatched() const;

    /**
     *
     */
    bool operator==(const SelectionStatus& o) const;

    /**
     *
     */
    bool operator!=(const SelectionStatus& o) const;

    /**
     *
     */
    friend KEYPLECORE_API std::ostream& operator<<(std::ostream& os,
                                                   const SelectionStatus& s);

    /**
     *
     */
    friend KEYPLECORE_API std::ostream& operator<<(
        std::ostream& os, const std::shared_ptr<SelectionStatus>& s);

private:
    /**
     *
     */
    const std::shared_ptr<AnswerToReset> mAtr;

    /**
     *
     */
    const std::shared_ptr<ApduResponse> mFci;

    /**
     *
     */
    const bool mIsMatching;
};

}
}
}
}
