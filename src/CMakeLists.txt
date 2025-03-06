# The Flutter tooling requires that developers have CMake 3.10 or later
# installed. You should not increase this version, as doing so will cause
# the plugin to fail to compile for some customers of the plugin.
cmake_minimum_required(VERSION 3.10)

include(VcpkgAndroid.cmake)

project(dart_media_toolkit_library VERSION 0.0.1 LANGUAGES C)

find_package(PkgConfig REQUIRED)

pkg_check_modules(LIBAV REQUIRED IMPORTED_TARGET libavformat)

add_library(dart_media_toolkit SHARED
  "dart_media_toolkit.c"
)

set_target_properties(dart_media_toolkit PROPERTIES
  PUBLIC_HEADER dart_media_toolkit.h
  OUTPUT_NAME "dart_media_toolkit"
)

target_compile_definitions(dart_media_toolkit PUBLIC DART_SHARED_LIB)

if (ANDROID)
  # Support Android 15 16k page size
  target_link_options(dart_media_toolkit PRIVATE "-Wl,-z,max-page-size=16384")
endif()

target_link_libraries(dart_media_toolkit PkgConfig::LIBAV)
