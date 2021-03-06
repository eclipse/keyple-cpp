/******************************************************************************
 * Copyright (c) 2018 Calypso Networks Association                            *
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

#include "ReaderPlugin.h"

namespace keyple {
namespace core {
namespace seproxy {

class PluginFactory {
public:
    /**
     *
     */
    virtual ~PluginFactory() = default;

    /**
     * Retrieve the name of the plugin that will be instantiated by this factory
     * (can be static or dynamic)
     *
     * @return pluginName
     */
    virtual const std::string& getPluginName() const = 0;


    /**
     * Retrieve an instance of a plugin (can be a singleton or not)
     *
     * @return instance of a ReaderPlugin
     * @throw KeyplePluginInstantiationException if instantiation failed,
     *        mostly when the third party library which manages the Se Reader
     *        interface is not ready
     */
    virtual std::shared_ptr<ReaderPlugin> getPlugin() const = 0;
};

}
}
}
