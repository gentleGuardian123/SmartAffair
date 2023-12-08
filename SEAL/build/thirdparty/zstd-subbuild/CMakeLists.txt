# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.16.3)

# We name the project and the target for the ExternalProject_Add() call
# to something that will highlight to the user what we are working on if
# something goes wrong and an error message is produced.

project(zstd-populate NONE)

include(ExternalProject)
ExternalProject_Add(zstd-populate
                     "UPDATE_DISCONNECTED" "False" "GIT_REPOSITORY" "https://github.com/facebook/zstd.git" "GIT_TAG" "e47e674cd09583ff0503f0f6defd6d23d8b718d3"
                    SOURCE_DIR          "/home/wentao/workspace/wentao/SmartAffair/SEAL/build/thirdparty/zstd-src"
                    BINARY_DIR          "/home/wentao/workspace/wentao/SmartAffair/SEAL/build/thirdparty/zstd-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
                    USES_TERMINAL_DOWNLOAD  YES
                    USES_TERMINAL_UPDATE    YES
)
