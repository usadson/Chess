# SPDX-License-Identifier: BSD-2-Clause
#
# Copyright (C) 2021 Tristan Gerritsen <tristan@thewoosh.org>
# All Rights Reserved.

option(ENABLE_PCH "Enable PreCompiledHeaders" ON)

#if (ENABLE_PCH)
#    add_library(PCH_Libraries INTERFACE)
#    target_precompile_headers(PCH_Libraries INTERFACE
#             C++ standard libraries
#	    <map>
#            <memory>
#            <string>
#            <vector>
#
#             Our own libraries
#	    <nlohmann/json.hpp>
#	    <fmt/core.h>
#	    <fmt/format.h>
#    )
#    target_link_libraries(project_diagnostics INTERFACE PCH_Libraries)
#endif()
