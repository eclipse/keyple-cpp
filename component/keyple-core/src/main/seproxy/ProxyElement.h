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

#include <map>
#include <string>

namespace keyple {
namespace core {
namespace seproxy {

/**
 * (package-private)<br>
 * Allow keyple::core::seproxy::message::ProxyReader and keyple::core::seproxy::ReaderPlugin to
 * receive configuration parameters
 */
class ProxyElement {
public:
    /**
     *
     */
    virtual ~ProxyElement() = default;

    /**
     * C++ vs. Java: hack to avoid linker issues. Should be removed in 1.0
     *
     * @return the unique name of the item
     */
    virtual const std::string& getName() const = 0;

    /**
     * Gets the parameters
     *
     * @return the configuration of the item
     */
    virtual const std::map<const std::string, const std::string>& getParameters() const = 0;

    /**
     * Allows to define a proprietary setting for a reader or a plugin (contactless protocols
     * polling sequence, baud rate, … etc.).
     *
     * @param key the parameter key
     * @param value the parameter value
     * @throw IllegalArgumentException if the parameter or the value is not supported
     * @throw KeypleReaderIOException if the communication with the reader or the SE has failed
     */
    virtual void setParameter(const std::string& key, const std::string& value) = 0;

    /**
     * allows to define a set of proprietary settings for a reader or a plugin (contactless
     * protocols polling sequence, baud rate, … etc.).
     *
     * @param parameters Parameters to setup
     * @throw IllegalArgumentException if the parameters or the values is not  supported
     * @throw KeypleException if the parameter fails to be set up
     */
    virtual void setParameters(const std::map<const std::string, const std::string>& parameters)
    {
        (void)parameters;
    }
};

}
}
}
