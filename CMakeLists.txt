# SPDX-License-Identifier: BSD-2-Clause
#
# Copyright (C) 2021 - 2022 Tristan Gerritsen.
# All Rights Reserved.

cmake_minimum_required(VERSION 3.16)

include(CMake/Version.cmake)

project(Chess
        HOMEPAGE_URL https://gitlab.com/thewoosh/MangoTranslator
        VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
        LANGUAGES CXX)

option(ENABLE_TESTING "Enable testing" ON)

include(CMake/CompilerSettings.cmake)
include(CMake/Libraries.cmake)

include_directories(.)
include_directories(Include)
include_directories(Source)

add_library(project_diagnostics INTERFACE)
include(CMake/CompilerDiagnostics.cmake)
set_project_diagnostics(project_diagnostics)



add_subdirectory(Source)
