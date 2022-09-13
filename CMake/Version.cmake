# SPDX-License-Identifier: BSD-2-Clause
#
# Copyright (C) 2021 Tristan Gerritsen <tristan@thewoosh.org>
# All Rights Reserved.

set(VERSION_MAJOR 2022)
set(VERSION_MINOR 06)
set(VERSION_PATCH 0)

add_compile_definitions(MANGO_VERSION_MAJOR=${VERSION_MAJOR}
						MANGO_VERSION_MINOR=${VERSION_MINOR}
						MANGO_VERSION_PATCH=${VERSION_PATCH})
