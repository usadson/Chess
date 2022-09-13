# SPDX-License-Identifier: BSD-2-Clause
#
# Copyright (C) 2021 Tristan Gerritsen <tristan@thewoosh.org>
# All Rights Reserved.

option(USE_SANITIZERS "Use sanitizers" ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ((CMAKE_CXX_COMPILER_ID STREQUAL "GNU") OR (CMAKE_CXX_COMPILER_ID MATCHES ".*Clang"))
    # Disable C++ exceptions
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti -fno-exceptions")
    add_definitions(-D_HAS_EXCEPTIONS=0)
    
    # Enalbe ASan/UBSan
    if (USE_SANITIZERS)
        add_compile_options(-fsanitize=address,undefined)
        add_link_options(-fsanitize=address,undefined)
    endif()
else (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    if(USE_SANITIZERS)
        add_compile_options(/fsanitize=address)
    endif()

    # Force UTF-8
    add_compile_options("/utf-8")
endif()
