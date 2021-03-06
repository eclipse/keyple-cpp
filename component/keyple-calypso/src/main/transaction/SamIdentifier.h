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

#include <memory>

/* Calypso */
#include "KeypleCalypsoExport.h"
#include "SamRevision.h"

namespace keyple {
namespace calypso {
namespace transaction {

using namespace keyple::calypso::command::sam;

/**
 * Holds the needed data to proceed a SAM selection.
 * <p>
 * SAM Revision (see keyple::calypso::command::sam::SamRevision)
 * <p>
 * Serial Number (may be a regular expression)
 * <p>
 * Group reference (key group reference)
 */
class KEYPLECALYPSO_API SamIdentifier {
public:
    /**
     * Builder for a keyple::calypso::transaction::SamIdentifier
     *
     * @since 0.9
     */
    class KEYPLECALYPSO_API SamIdentifierBuilder final {
    public:
        /**
         * Allow access to private members
         */
        friend SamIdentifier;

        /**
         * Sets the targeted SAM revision
         *
         * @param samRevision the keyple::calypso::command::sam::SamRevision of the targeted SAM
         * @return the builder instance
         */
        SamIdentifierBuilder& samRevision(const SamRevision& samRevision);

        /**
         * Sets the targeted SAM serial number
         *
         * @param serialNumber the serial number of the targeted SAM as regex
         * @return the builder instance
         */
        SamIdentifierBuilder& serialNumber(const std::string& serialNumber);

        /**
         * Sets the targeted SAM group reference
         *
         * @param groupReference the group reference of the targeted SAM as a
         *        string
         * @return the builder instance
         */
        SamIdentifierBuilder& groupReference(const std::string& groupReference);

        /**
         * Build a new {@code SamIdentifier}.
         *
         * @return a new instance
         */
        std::shared_ptr<SamIdentifier> build();

    private:
        /**
         *
         */
        SamRevision mSamRevision = SamRevision::NO_REV;

        /**
         *
         */
        std::string mSerialNumber = "";

        /**
         *
         */
        std::string mGroupReference = "";
    };

    /**
     * Gets a new builder.
     *
     * @return a new builder instance
     */
    static std::unique_ptr<SamIdentifierBuilder> builder();

    /**
     * @return the SAM revision
     */
    const SamRevision& getSamRevision() const;

    /**
     * @return the SAM serial number
     */
    const std::string& getSerialNumber() const;

    /**
     * @return the group reference
     */
    const std::string& getGroupReference() const;

    /**
     * Compare two SamIdentifiers with the following rules:
     * <ul>
     * <li>when the provided keyple::calypso::transaction::SamIdentifier is null the result is
     * true</li>
     * <li>when the provided keyple::calypso::transaction::SamIdentifier is not null
     * <ul>
     * <li>the AUTO revision matches any revision</li>
     * <li>if not null, the serial number is used as a regular expression to
     * check the current serial number</li>
     * <li>if not null the group reference is compared as a string</li>
     * </ul>
     * </li>
     * </ul>
     *
     * @param samIdentifier the keyple::calypso::transaction::SamIdentifier object to be compared to
     *        the current object
     * @return true if the identifier provided matches the current identifier
     */
    bool matches(const std::shared_ptr<SamIdentifier> samIdentifier) const;

    /**
     * Private constructor
     *
     * C++ vs. Java: constructor is private in Java but prevents the use of
     *               make_shared.
     */
    SamIdentifier(const SamIdentifierBuilder* builder);

private:
    /**
     *
     */
    const SamRevision mSamRevision = SamRevision::NO_REV;

    /**
     *
     */
    const std::string mSerialNumber;

    /**
     *
     */
    const std::string mGroupReference;
};

}
}
}
