# Install script for directory: /Users/gen/Downloads/GamePlay-deps-master/libjson-7.6.1/_internal/Source

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/Users/gen/Downloads/GamePlay-deps-master/out/external-deps")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/libjson/_internal/Source" TYPE FILE FILES
    "/Users/gen/Downloads/GamePlay-deps-master/libjson-7.6.1/_internal/Source/JSONAllocator.h"
    "/Users/gen/Downloads/GamePlay-deps-master/libjson-7.6.1/_internal/Source/JSONMemoryPool.h"
    "/Users/gen/Downloads/GamePlay-deps-master/libjson-7.6.1/_internal/Source/JSONStream.h"
    "/Users/gen/Downloads/GamePlay-deps-master/libjson-7.6.1/_internal/Source/JSONChildren.h"
    "/Users/gen/Downloads/GamePlay-deps-master/libjson-7.6.1/_internal/Source/JSONNode.h"
    "/Users/gen/Downloads/GamePlay-deps-master/libjson-7.6.1/_internal/Source/JSONValidator.h"
    "/Users/gen/Downloads/GamePlay-deps-master/libjson-7.6.1/_internal/Source/JSONDebug.h"
    "/Users/gen/Downloads/GamePlay-deps-master/libjson-7.6.1/_internal/Source/JSONPreparse.h"
    "/Users/gen/Downloads/GamePlay-deps-master/libjson-7.6.1/_internal/Source/JSONWorker.h"
    "/Users/gen/Downloads/GamePlay-deps-master/libjson-7.6.1/_internal/Source/JSONDefs.h"
    "/Users/gen/Downloads/GamePlay-deps-master/libjson-7.6.1/_internal/Source/JSONSharedString.h"
    "/Users/gen/Downloads/GamePlay-deps-master/libjson-7.6.1/_internal/Source/JSON_Base64.h"
    "/Users/gen/Downloads/GamePlay-deps-master/libjson-7.6.1/_internal/Source/JSONGlobals.h"
    "/Users/gen/Downloads/GamePlay-deps-master/libjson-7.6.1/_internal/Source/JSONSingleton.h"
    "/Users/gen/Downloads/GamePlay-deps-master/libjson-7.6.1/_internal/Source/NumberToString.h"
    "/Users/gen/Downloads/GamePlay-deps-master/libjson-7.6.1/_internal/Source/JSONMemory.h"
    "/Users/gen/Downloads/GamePlay-deps-master/libjson-7.6.1/_internal/Source/JSONStats.h"
    "/Users/gen/Downloads/GamePlay-deps-master/libjson-7.6.1/_internal/Source/internalJSONNode.h"
    "/Users/gen/Downloads/GamePlay-deps-master/libjson-7.6.1/_internal/Source/JSONDefs/GNU_C.h"
    "/Users/gen/Downloads/GamePlay-deps-master/libjson-7.6.1/_internal/Source/JSONDefs/Strings_Defs.h"
    "/Users/gen/Downloads/GamePlay-deps-master/libjson-7.6.1/_internal/Source/JSONDefs/Unknown_C.h"
    "/Users/gen/Downloads/GamePlay-deps-master/libjson-7.6.1/_internal/Source/JSONDefs/Visual_C.h"
    )
endif()

