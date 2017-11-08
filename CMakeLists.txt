# USAGE:
#  ./configure && mkdir -p build && cd build && cmake .. && make && make install
#  To make only a specific target, try 'make dmtcpinternal'
#    to make libdmtcpinternal.a.  This works with target names,
#    which are the first arguments to add_Executable() and add_library().
# By default, this creates all targets in the build directory.
#   For debugging:  cmake -D CMAKE_BUILD_TYPE-release ..

# Build/Install variables available:
#   CMAKE_BINARY_DIR (build dir), CMAKE_SOURCE_DIR, CMAKE_CURRENT_SOURCE_DIR,
#   CMAKE_INSTALL_PREFIX (default: /usr/local; can change in call to 'cmake'),
# 'make DESTDIR=/home/gene install' will install
#     to /home/gene/${CMAKE_INSTALL_PREFIX}/XXX
#     where XXX is bin, lib, include, man, etc., specified in INSTALL().

# USAGE (Graphviz for dependency graph):
#   https://cmake.org/Wiki/CMake:For_CMake_Hackers#Generating_Dependency_Graphs_with_CMake
#   https://cmake.org/cmake/help/v3.2/prop_gbl/GLOBAL_DEPENDS_DEBUG_MODE.html
#  And available starting with CMAKE-3.7:
#   https://cmake.org/cmake/help/latest/prop_dir/BUILDSYSTEM_TARGETS.html#prop_dir:BUILDSYSTEM_TARGETS

# USAGE (CPack):
#  mkdir -p build && cd build && cmake ..
#  cd build && cpack -D CPACK_GENERATOR="TGZ" ..
#  OR:  Depend on CPACK_GENERATOR variable at end of this file: cpack ..
# QUESTION:
#  What is: cpack -D CPACK_GENERATOR="Unix Makefiles" ..
#  supposed to do, and why doesn't it work?

# GOTCHAS:
#  https://samthursfield.wordpress.com/2015/11/21/cmake-dependencies-between-targets-and-files-and-custom-commands/

# RELEASE and DEBUG versions:
#  https://stackoverflow.com/questions/7724569/debug-vs-release-in-cmake
# USEFUL VARIABLES:
#  https://cmake.org/Wiki/CMake_Useful_Variables

# Don't forget to delete CMakeCache.txt to remove old cached values
# TO SEE OUTPUT OF 'make':
#   cmake -D CMAKE_VERBOSE_MAKEFILE=1 ..
#   OR:  make VERBOSE=1
# TO SEE OTHER OPTIONS, DO:
#   cmake -i ..

# Capture special variables set by call to ./configure
message("-- Including autoconf variables as CMake variables:")
include(CMakeAutoconf.txt)

cmake_minimum_required(VERSION 2.8.0)
project(dmtcp)
set(CMAKE_BUILD_TYOE release)

message("-- CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS:  ${CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS} (removing this flag)")
SET(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")

# target_include_directories(include)

# target_compile_options(example PUBLIC -std=c++1y -Wall -Wfloat-conversion)

include_directories(include jalib)

add_subdirectory(src)
add_subdirectory(src/plugin)

# =====================================================

add_custom_target(
   contrib
   COMMAND make
   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/contrib
   COMMENT "Building contrib directory"
   VERBATIM
)

# =====================================================

# set(SOURCES_dmtcp_coordinator
#     dmtcp_coordinator.cpp lookup_service.cpp restartscript.cpp
#    )

# file(GLOB SOURCES "src/*.cpp")
#

# add_executable(dmtcp_coordinator ${SOURCES_dmtcp_coordinator})

# INSTALL(TARGETS dmtcp_coordinator DESTINATION bin)

# set(CPACK_CMAKE_GENERATOR "Unix Makefile")
set(CPACK_CMAKE_GENERATOR "TGZ")
set(CPACK_PACKAGE_NAME "${AC_package}")  # results in lower-case "dmtcp"
set(CPACK_PACKAGE_VERSION "${AC_package_version}")
set(CPACK_PACKAGE_URL "${AC_package_url}")

# This must be last.
include(CPack)
