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

#include <string>
#include <unordered_map>
#include <vector>
#include <stdexcept>
#include <memory>

/* Common */
#include "LoggerFactory.h"

/* Core */
#include "Tag.h"

/* Calypso */
#include "AbstractPoResponseParser.h"
#include "AbstractApduResponseParser.h"
#include "GetDataFciCmdBuild.h"

namespace keyple {
namespace calypso {
namespace command {
namespace po {
namespace parser {

using namespace keyple::calypso::command::po;
using namespace keyple::calypso::command::po::builder;
using namespace keyple::core::seproxy::message;
using namespace keyple::core::util::bertlv;
using namespace keyple::common;

/**
 * Extracts information from the FCI data returned is response to the selection
 * application command.
 * <p>
 * Provides getter methods for all relevant information.
 */
class KEYPLECALYPSO_API GetDataFciRespPars final
: public AbstractPoResponseParser {
public:
    /**
     * Instantiates a new GetDataFciRespPars from the ApduResponse to a
     * selection application command.
     * <p>
     * The expected FCI structure of a Calypso PO follows this scheme: <code>
     * T=6F L=XX (C)                FCI Template
     *      T=84 L=XX (P)           DF Name
     *      T=A5 L=22 (C)           FCI Proprietary Template
     *           T=BF0C L=19 (C)    FCI Issuer Discretionary Data
     *                T=C7 L=8 (P)  Application Serial Number
     *                T=53 L=7 (P)  Discretionary Data (Startup Information)
     * </code>
     * <p>
     * The ApduResponse provided in argument is parsed according to the above
     * expected structure.
     * <p>
     * DF Name, Application Serial Number and Startup Information are extracted.
     * <p>
     * The 7-byte startup information field is also split into 7 private field
     * made available through dedicated getter methods.
     * <p>
     * All fields are pre-initialized to handle the case where the parsing fails.
     * <p>
     *
     * @param response the select application response from Get Data APDU command
     * @param builder the reference to the builder that created this parser
     */
    GetDataFciRespPars(std::shared_ptr<ApduResponse> response,
                       GetDataFciCmdBuild* builder);

    /**
     *
     */
    bool isValidCalypsoFCI() const;

    /**
     *
     */
    const std::vector<uint8_t>& getDfName() const;

    /**
     *
     */
    const std::vector<uint8_t>& getApplicationSerialNumber() const;

    /**
     *
     */
    const std::vector<uint8_t>& getDiscretionaryData() const;

    /**
     *
     */
    bool isDfInvalidated() const;

protected:
    /**
     *
     */
    const std::shared_ptr<Logger> logger =
        LoggerFactory::getLogger(typeid(GetDataFciRespPars));

    /**
     *
     */
    const std::map<int, std::shared_ptr<StatusProperties>>& getStatusTable()
        const override;

private:
    /**
     *
     */
    static const std::map<int, std::shared_ptr<StatusProperties>> STATUS_TABLE;

    /**
     * Buffer indicator to buffer size lookup table
     */
    static std::vector<int> const BUFFER_SIZE_INDICATOR_TO_BUFFER_SIZE;

    /* BER-TLV tags definitions */
    /*
     * FCI Template: application class, constructed, tag number Fh => tag field
     * 6Fh
     */
    static const std::shared_ptr<Tag> TAG_FCI_TEMPLATE;
    /*
     * DF Name: context-specific class, primitive, tag number 4h => tag field
     * 84h
     */
    static const std::shared_ptr<Tag> TAG_DF_NAME;

    /**
     * FCI Proprietary Template: context-specific class, constructed, tag number
     * 5h => tag field A5h
     */
    static const std::shared_ptr<Tag> TAG_FCI_PROPRIETARY_TEMPLATE;

    /**
     * FCI Issuer Discretionary Data: context-specific class, constructed, tag
     * number Ch => tag field BF0Ch
     */
    static const std::shared_ptr<Tag> TAG_FCI_ISSUER_DISCRETIONARY_DATA;

    /*
     * Application Serial Number: private class, primitive, tag number 7h => tag
     * field C7h
     */
    static const std::shared_ptr<Tag> TAG_APPLICATION_SERIAL_NUMBER;

    /*
     * Discretionary Data: application class, primitive, tag number 13h => tag
     * field 53h
     */
    static const std::shared_ptr<Tag> TAG_DISCRETIONARY_DATA;

    /**
     * Attributes result of th FCI parsing
     */
    bool mIsDfInvalidated = false;
    bool mIsValidCalypsoFCI = false;

    std::vector<uint8_t> mDfName;
    std::vector<uint8_t> mApplicationSN;
    std::vector<uint8_t> mDiscretionaryData;
};

}
}
}
}
}
