#
# Copyright (c) 2018 Calypso Networks Association https://www.calypsonet-asso.org/
#
# All rights reserved. This program and the accompanying materials are made available under the
# terms of the Eclipse Public License version 2.0 which accompanies this distribution, and is
# available at https://www.eclipse.org/org/documents/epl-2.0/EPL-2.0.html
#

PROJECT(KeyplePluginStub C CXX)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(VERSION_MAJOR "0")
SET(VERSION_MINOR "8")
SET(VERSION_PATCH "1")

SET(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

SET(PACKAGE_NAME "KeyplePluginStub")
SET(PACKAGE_VERSION ${VERSION})
SET(PACKAGE_STRING "${PACKAGE_NAME} ${PACKAGE_VERSION}")

SET(CMAKE_MACOSX_RPATH 1)
SET(CMAKE_CXX_STANDARD 11)

SET(LIBRARY_NAME keyplepluginstub)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DKEYPLEPLUGINSTUB_EXPORT")

INCLUDE_DIRECTORIES(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/java/org/eclipse/keyple

	# Core
	${CMAKE_CURRENT_SOURCE_DIR}/../../../../keyple-core/src/main/util
	${CMAKE_CURRENT_SOURCE_DIR}/../../../../keyple-core/src/main/seproxy
	${CMAKE_CURRENT_SOURCE_DIR}/../../../../keyple-core/src/main/seproxy/event
	${CMAKE_CURRENT_SOURCE_DIR}/../../../../keyple-core/src/main/seproxy/exception
	${CMAKE_CURRENT_SOURCE_DIR}/../../../../keyple-core/src/main/seproxy/message
	${CMAKE_CURRENT_SOURCE_DIR}/../../../../keyple-core/src/main/seproxy/plugin
	${CMAKE_CURRENT_SOURCE_DIR}/../../../../keyple-core/src/main/seproxy/plugin/local
	${CMAKE_CURRENT_SOURCE_DIR}/../../../../keyple-core/src/main/seproxy/plugin/local/state
	${CMAKE_CURRENT_SOURCE_DIR}/../../../../keyple-core/src/main/seproxy/plugin/local/monitoring
	${CMAKE_CURRENT_SOURCE_DIR}/../../../../keyple-core/src/main/seproxy/protocol
	${CMAKE_CURRENT_SOURCE_DIR}/../../../../keyple-core/src/main/transaction

	# Helpers
	${CMAKE_CURRENT_SOURCE_DIR}/../../../../keyple-common/src/main
	${CMAKE_CURRENT_SOURCE_DIR}/../../../../keyple-common/src/main/exception
)

ADD_LIBRARY(${LIBRARY_NAME} SHARED

	${CMAKE_CURRENT_SOURCE_DIR}/StubPluginFactory.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/StubPluginImpl.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/StubPoolPluginFactory.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/StubPoolPluginImpl.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/StubProtocolSetting.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/StubReaderImpl.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/StubSecureElement.cpp
)

SET(LINK_LIBS keyplecore)

TARGET_LINK_LIBRARIES(${LIBRARY_NAME} ${LINK_LIBS})
