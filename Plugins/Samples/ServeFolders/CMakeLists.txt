cmake_minimum_required(VERSION 2.8)

project(ServeFolders)

SET(SERVE_FOLDERS_VERSION "0.0" CACHE STRING "Version of the plugin")
SET(STATIC_BUILD OFF CACHE BOOL "Static build of the third-party libraries (necessary for Windows)")
SET(ALLOW_DOWNLOADS OFF CACHE BOOL "Allow CMake to download packages")
SET(USE_SYSTEM_JSONCPP ON CACHE BOOL "Use the system version of JsonCpp")

set(ORTHANC_ROOT ${CMAKE_SOURCE_DIR}/../../../)
set(SAMPLES_ROOT ${CMAKE_SOURCE_DIR}/..)

include(CheckIncludeFiles)
include(CheckIncludeFileCXX)
include(${CMAKE_SOURCE_DIR}/../Common/OrthancPlugins.cmake)
include(${ORTHANC_ROOT}/Resources/CMake/DownloadPackage.cmake)
include(${ORTHANC_ROOT}/Resources/CMake/JsonCppConfiguration.cmake)

add_library(ServeFolders SHARED 
  Plugin.cpp
  ${JSONCPP_SOURCES}
  )


message("Setting the version of the plugin to ${SERVE_FOLDERS_VERSION}")
add_definitions(-DSERVE_FOLDERS_VERSION="${SERVE_FOLDERS_VERSION}")

set_target_properties(ServeFolders PROPERTIES 
  VERSION ${SERVE_FOLDERS_VERSION} 
  SOVERSION ${SERVE_FOLDERS_VERSION})

install(
  TARGETS ServeFolders
  RUNTIME DESTINATION lib    # Destination for Windows
  LIBRARY DESTINATION share/orthanc/plugins    # Destination for Linux
  )
