#
#
#  MIT License
#
#  Copyright (c) 2024-2025 Yafiyogi
#
#  Permission is hereby granted, free of charge, to any person obtaining a copy
#  of this software and associated documentation files (the "Software"), to deal
#  in the Software without restriction, including without limitation the rights
#  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#  copies of the Software, and to permit persons to whom the Software is
#  furnished to do so, subject to the following conditions:
#
#  The above copyright notice and this permission notice shall be included in all
#  copies or substantial portions of the Software.
#
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#  SOFTWARE.
#
#

# PKG_CONFIG_PATH=${HOME}/code/tp/lib/pkgconfig:${HOME}/code/tp/share/pkgconfig:${PKG_CONFIG_PATH} cmake --fresh -DCMAKE_INSTALL_PREFIX=${HOME}/code/cpp/build -DYY_THIRD_PARTY_LIBRARY=${HOME}/code/tp -DCMAKE_POSITION_INDEPENDENT_CODE=TRUE -DCMAKE_BUILD_TYPE=Release .
# cmake --fresh -DCMAKE_INSTALL_PREFIX=${HOME}/code/cpp/build -DYY_THIRD_PARTY_LIBRARY=${HOME}/code/tp -DCMAKE_POSITION_INDEPENDENT_CODE=TRUE -DCMAKE_BUILD_TYPE=Release .

cmake_minimum_required(VERSION 3.25)

project(yy_prometheus LANGUAGES CXX VERSION 0.0.1)

set(YY_ROOT "${PROJECT_SOURCE_DIR}/..")
set(YY_CMAKE "${YY_ROOT}/yy_cmake")

include(${YY_CMAKE}/cmake_common.txt)
include(${YY_CMAKE}/cmake_clang_tidy.txt)

add_library(yy_prometheus STATIC)

target_compile_options(yy_prometheus
  PRIVATE
    "-DSPDLOG_COMPILED_LIB"
    "-DSPDLOG_FMT_EXTERNAL")

target_include_directories(yy_prometheus
  PRIVATE
    "${CMAKE_INSTALL_PREFIX}/include")

target_include_directories(yy_prometheus
  SYSTEM PRIVATE
    "${YY_THIRD_PARTY_LIBRARY}/include" )

target_sources(yy_prometheus
  PRIVATE
    yy_prometheus_cache.cpp
    yy_prometheus_configure.cpp
    yy_prometheus_metric_data.cpp
    yy_prometheus_metric_format.cpp
    yy_prometheus_style.cpp
  PUBLIC FILE_SET HEADERS
    FILES
      yy_prometheus_cache.h
      yy_prometheus_configure.h
      yy_prometheus_defaults.h
      yy_prometheus_metric_data.h
      yy_prometheus_metric_format.h
      yy_prometheus_metric_types.h
      yy_prometheus_style.h)

install(TARGETS yy_prometheus
  EXPORT yy_prometheusTargets
  FILE_SET HEADERS DESTINATION include/yy_prometheus)

install(EXPORT yy_prometheusTargets
  NAMESPACE yy_prometheus::
  DESTINATION lib/cmake/yy_prometheus)

include(CMakePackageConfigHelpers)
write_basic_package_version_file("yy_prometheusConfigVersion.cmake"
  VERSION ${yy_prometheus_VERSION}
  COMPATIBILITY AnyNewerVersion)

install(FILES "yy_prometheusConfig.cmake" "${CMAKE_CURRENT_BINARY_DIR}/yy_prometheusConfigVersion.cmake"
    DESTINATION lib/cmake/yy_prometheus)

#add_subdirectory(unit_tests)

add_yy_tidy_all(yy_prometheus)
