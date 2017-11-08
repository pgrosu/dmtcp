# USAGE:
#   See CMakeLists.txt at top-level

cmake_minimum_required(VERSION 2.8.0)
project(dmtcp)

# We should conditionalize this based on result of ./configure
SET( CMAKE_C_FLAGS  "${CMAKE_CXX_FLAGS} -fPIC -g3 -O0" )
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fPIC -g3 -O0" )
# SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS}" )
# target-specific version of compile options;
#    target property, file property, or add flags in add_executable/library()
# target_compile_options(example PUBLIC -std=c++1y -Wall -Wfloat-conversion)


# These are global include directories
# target_include_directories exists for target-specific incluces.
# Top-level CMakeLists.txt already hs include_directories for include, jalib
# This include directory is for all targets in this directory only.
include_directories(./)

# A target is simply a Makefile target.
# So next, we do the individual targets.  Each target is created using
#  add_executable() or add_library() or add_custom_target()
#  add_custom_command() can modify the recipes for targets
#    (see example with libmtcp.a, below)
# When 'mytarget' exists, then 'make mytarget' works.

# file(GLOB SOURCES "src/*.cpp")
#   available instead of set(SOURCES ...)

# =====================================================

# Libraries:
set(SOURCES_libdmtcpinternal
    dmtcpmessagetypes.cpp;coordinatorapi.cpp;workerstate.cpp;dmtcp_dlsym.cpp;uniquepid.cpp;shareddata.cpp;util_exec.cpp;util_misc.cpp;util_init.cpp;jalibinterface.cpp;processinfo.cpp;procselfmaps.cpp
   )
set(SOURCES_libnohijack nosyscallsreal.c;dmtcpnohijackstubs.cpp)
set(SOURCES_libjalib
    ../jalib/jalib.cpp;../jalib/jassert.cpp;../jalib/jbuffer.cpp;../jalib/jfilesystem.cpp;../jalib/jserialize.cpp;../jalib/jsocket.cpp;../jalib/jtimer.cpp;../jalib/jalloc.cpp
   )
set(SOURCES_libsyscallsreal syscallsreal.c;trampolines.cpp)
set(SOURCES_libdmtcp_a
    dmtcpworker.cpp; threadsync.cpp; coordinatorapi.cpp; execwrappers.cpp; signalwrappers.cpp; terminal.cpp; alarm.cpp; threadwrappers.cpp; miscwrappers.cpp; ckptserializer.cpp; writeckpt.cpp; glibcsystem.cpp; threadlist.cpp; siginfo.cpp; dmtcpplugin.cpp; popen.cpp; syslogwrappers.cpp; dmtcp_dlsym.cpp; plugininfo.cpp; pluginmanager.cpp; dmtcpmessagetypes.cpp; workerstate.cpp; uniquepid.cpp; shareddata.cpp; util_exec.cpp; processinfo.cpp; procselfmaps.cpp; ../jalib/jalib.cpp;../jalib/jassert.cpp;../jalib/jbuffer.cpp;../jalib/jfilesystem.cpp;../jalib/jserialize.cpp;../jalib/jsocket.cpp;../jalib/jtimer.cpp;../jalib/jalloc.cpp; syscallsreal.c; trampolines.cpp; mtcp/restore_libc.c
)

add_library(dmtcpinternal STATIC ${SOURCES_libdmtcpinternal})
add_library(jalib STATIC ${SOURCES_libjalib})
add_library(syscallsreal STATIC ${SOURCES_libsyscallsreal})
add_library(nohijack STATIC ${SOURCES_libnohijack})
add_library(dmtcp_a STATIC ${SOURCES_libdmtcp_a})

# =====================================================

set(SOURCES_dmtcp_coordinator
    dmtcp_coordinator.cpp;lookup_service.cpp;restartscript.cpp
   )

set(LIBS_src dmtcpinternal;jalib;nohijack)

add_executable(dmtcp_coordinator ${SOURCES_dmtcp_coordinator})
target_link_libraries(dmtcp_coordinator ${LIBS_src};pthread;rt)
INSTALL(TARGETS dmtcp_coordinator RUNTIME DESTINATION bin)

# =====================================================

add_executable(dmtcp_command dmtcp_command.cpp)
target_link_libraries(dmtcp_command ${LIBS_src};pthread;rt;dl)
INSTALL(TARGETS dmtcp_command RUNTIME DESTINATION bin)

# =====================================================

add_executable(dmtcp_nocheckpoint dmtcp_nocheckpoint.c)
target_link_libraries(dmtcp_nocheckpoint -static)
INSTALL(TARGETS dmtcp_nocheckpoint RUNTIME DESTINATION bin)

# =====================================================

add_executable(dmtcp_launch dmtcp_launch.cpp)
target_link_libraries(dmtcp_launch ${LIBS_src};pthread;rt;dl)
INSTALL(TARGETS dmtcp_launch RUNTIME DESTINATION bin)

# =====================================================

add_executable(dmtcp_restart dmtcp_restart.cpp util_exec.cpp)
target_link_libraries(dmtcp_restart ${LIBS_src};pthread;rt;dl)
INSTALL(TARGETS dmtcp_restart RUNTIME DESTINATION bin)

# =====================================================
# =====================================================

# EXPERIMENTS TO UNDERSTAND cmake
# DELETE THIS WHEN WELL UNDERSTOOD.

message(STATUS "CMAKE_ROOT=${CMAKE_ROOT}")
message(STATUS "CMAKE_SOURCE_DIR=${CMAKE_SOURCE_DIR}")
message(STATUS "CMAKE_CURRENT_SOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR}")

# include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)
#
# ExternalProject_Add(mtcp
#   SOURCE_DIR ${CMAKE_SOURCE_DIR}/mtcp
#   BUILD_IN_SOURCE 1
#   CONFIGURE_COMMAND ""
#   BUILD_COMMAND make
#   # PREFIX=${CMAKE_CURRENT_BINARY_DIR}/mtcp
#   # CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/install
# )

# =====================================================
# =====================================================

set(SOURCES_libdmtcp
     dmtcpworker.cpp;threadsync.cpp;coordinatorapi.cpp;execwrappers.cpp;signalwrappers.cpp;terminal.cpp;alarm.cpp;threadwrappers.cpp;miscwrappers.cpp;ckptserializer.cpp;writeckpt.cpp;glibcsystem.cpp;threadlist.cpp;siginfo.cpp;dmtcpplugin.cpp;popen.cpp;syslogwrappers.cpp;dmtcp_dlsym.cpp;plugininfo.cpp;pluginmanager.cpp
   )
add_library(dmtcp MODULE ${SOURCES_libdmtcp})
# Add mtcp/libmtcp.a to the libdmtcp.so target
add_custom_command(
   TARGET dmtcp
   PRE_BUILD
   COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIRECTORY}/bin
   COMMAND make
   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/mtcp
   COMMENT "Building libmtcp.a in mtcp dir and mtcp_restart in top-level bin"
   VERBATIM
)
set(LIBS_libdmtcp dmtcpinternal jalib syscallsreal)
target_link_libraries(dmtcp ${LIBS_libdmtcp};pthread;rt;dl -L${CMAKE_CURRENT_SOURCE_DIR}/mtcp -lmtcp)
target_link_libraries(dmtcp -Xlinker -znow)
INSTALL(TARGETS dmtcp LIBRARY DESTINATION lib/dmtcp)

# =====================================================

## DELETE THIS WHEN WE DON'T NEED THIS property EXAMPLE
## #==============================================
## # NEED TO ADD -Xlinker -znow  (or -Wl,-znow)
## get_target_property(TEMP dmtcp LINK_FLAGS)
## if(TEMP STREQUAL "TEMP-NOTFOUND")
##   SET(TEMP "") # set to empty string
## else()
##   SET(TEMP "${TEMP} ") # a space to cleanly separate from existing content
## endif()
## # append our values
## SET(TEMP "${TEMP} -Xlinker -znow" )
## set_target_properties(dmtcp PROPERTIES LINK_FLAGS ${TEMP} )


#==============================================

# As a convenience for users using DMTCP in their own account,
#   we create a local bin/lib/include in the top-level DMTCP directory.

set(DMTCP_EXECUTABLES dmtcp_command dmtcp_launch dmtcp_restart
                      dmtcp_coordinator dmtcp_nocheckpoint)

# Starting with CMake-3.5, can specify multiple files for copying.
# Does one use '*' directly, or file(GLOB SOURCES dmtcp_*) and use CMake var?
foreach(loop_var ${DMTCP_EXECUTABLES})
# This can be automated using BUILDSYSTEM_TARGETS, starting with CMAKE-3.7
add_custom_target(
  private_install_${loop_var} ALL  # Add to list of 'ALL' default targets.
          # ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/bin
  # An alternative to copy is:  COMMAND ${CMAKE_COMMAND} create_symlink ...
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
                              ${loop_var} ${CMAKE_SOURCE_DIR}/bin/
  # This can be automated using BUILDSYSTEM_TARGETS, starting with CMAKE-3.7
  DEPENDS ${loop_var}
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/src # BINARY_DIR means "build dir"
  COMMENT Copying DMTCP executables to in-source bin directory
)
add_dependencies(private_install_${loop_var} ${DMTCP_EXECUTABLES})
endforeach(loop_var)

set(DMTCP_LIBS libdmtcp.so)

foreach(loop_var ${DMTCP_LIBS})
add_custom_target(
  private_install_${loop_var} ALL  # Add to list of 'ALL' default targets.
  # An alternative to copy is:  COMMAND ${CMAKE_COMMAND} create_symlink ...
  # COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/lib
  # COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/lib/dmtcp
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
                              ${loop_var} ${CMAKE_SOURCE_DIR}/lib/dmtcp
  # This can be automated using BUILDSYSTEM_TARGETS, starting with CMAKE-3.7
  # FIXME:  If we just use ${loop_var} for DEPENDS, uses wrong WORKING_DIR
  #         Is this a bug in CMAKE-3.3?
  DEPENDS ${CMAKE_BINARY_DIR}/src/${loop_var}
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/src # BINARY_DIR means "build dir"
  COMMENT Copying DMTCP libraries to in-source lib directory
)
add_dependencies(private_install_${loop_var} dmtcp)
endforeach(loop_var)
