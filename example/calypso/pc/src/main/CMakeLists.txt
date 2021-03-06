#/*************************************************************************************************
# * Copyright (c) 2020 Calypso Networks Association                                               *
# * https://www.calypsonet-asso.org/                                                              *
# *                                                                                               *
# * See the NOTICE file(s) distributed with this work for additional information regarding        *
# * copyright ownership.                                                                          *
# *                                                                                               *
# * This program and the accompanying materials are made available under the terms of the Eclipse *
# * Public License 2.0 which is available at http://www.eclipse.org/legal/epl-2.0                 *
# *                                                                                               *
# * SPDX-License-Identifier: EPL-2.0                                                              *
# *************************************************************************************************/

PROJECT(ExamplePc C CXX)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(VERSION_MAJOR "0")
SET(VERSION_MINOR "9")
SET(VERSION_PATCH "0")

SET(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

SET(PACKAGE_NAME "ExamplePc")
SET(PACKAGE_VERSION ${VERSION})
SET(PACKAGE_STRING "${PACKAGE_NAME} ${PACKAGE_VERSION}")

SET(CMAKE_MACOSX_RPATH 1)
SET(CMAKE_CXX_STANDARD 11)

INCLUDE(CMakeLists.txt.demo_calypsoclassic_pcsc)
INCLUDE(CMakeLists.txt.demo_calypsoclassic_stub)
INCLUDE(CMakeLists.txt.usecase_calypso1_explicitselectionaid_pcsc)
INCLUDE(CMakeLists.txt.usecase_calypso1_explicitselectionaid_stub)
INCLUDE(CMakeLists.txt.usecase_calypso2_defaultselectionnotification_pcsc)
INCLUDE(CMakeLists.txt.usecase_calypso2_defaultselectionnotification_stub)
INCLUDE(CMakeLists.txt.usecase_calypso3_rev1selection_pcsc)
INCLUDE(CMakeLists.txt.usecase_calypso4_poauthentication_pcsc)
INCLUDE(CMakeLists.txt.usecase_calypso4_poauthentication_stub)
INCLUDE(CMakeLists.txt.usecase_calypso5_multiplesession_pcsc)
INCLUDE(CMakeLists.txt.usecase_calypso6_verifypin_pcsc)
INCLUDE(CMakeLists.txt.usecase_calypso7_storedvalue_simplereload_pcsc)
INCLUDE(CMakeLists.txt.usecase_calypso8_storedvalue_debitinsession_pcsc)
