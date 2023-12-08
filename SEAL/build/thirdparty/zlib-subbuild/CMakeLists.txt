# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.16.3)

# We name the project and the target for the ExternalProject_Add() call
# to something that will highlight to the user what we are working on if
# something goes wrong and an error message is produced.

project(zlib-populate NONE)

include(ExternalProject)
ExternalProject_Add(zlib-populate
                     "UPDATE_DISCONNECTED" "False" "GIT_REPOSITORY" "https://github.com/madler/zlib.git" "GIT_TAG" "04f42ceca40f73e2978b50e93806c2a18c1281fc"
                    SOURCE_DIR          "/home/wentao/workspace/wentao/SmartAffair/SEAL/build/thirdparty/zlib-src"
                    BINARY_DIR          "/home/wentao/workspace/wentao/SmartAffair/SEAL/build/thirdparty/zlib-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
                    USES_TERMINAL_DOWNLOAD  YES
                    USES_TERMINAL_UPDATE    YES
)
