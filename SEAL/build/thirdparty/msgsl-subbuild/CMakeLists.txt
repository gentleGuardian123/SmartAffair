# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.16.3)

# We name the project and the target for the ExternalProject_Add() call
# to something that will highlight to the user what we are working on if
# something goes wrong and an error message is produced.

project(msgsl-populate NONE)

include(ExternalProject)
ExternalProject_Add(msgsl-populate
                     "UPDATE_DISCONNECTED" "False" "GIT_REPOSITORY" "https://github.com/microsoft/GSL.git" "GIT_TAG" "a3534567187d2edc428efd3f13466ff75fe5805c"
                    SOURCE_DIR          "/home/wentao/workspace/wentao/SmartAffair/SEAL/build/thirdparty/msgsl-src"
                    BINARY_DIR          "/home/wentao/workspace/wentao/SmartAffair/SEAL/build/thirdparty/msgsl-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
                    USES_TERMINAL_DOWNLOAD  YES
                    USES_TERMINAL_UPDATE    YES
)
