set(DMTCP_PLUGINS "")
# NOTE:   First append to this must set it directly.

# =====================================================

set(SOURCES_libpid
    pid/pid.cpp;pid/pid_filewrappers.cpp;pid/pid_miscwrappers.cpp;pid/pid_syscallsreal.c;pid/pidwrappers.cpp;pid/sched_wrappers.cpp;pid/virtualpidtable.cpp
)
add_library(dmtcp_pid MODULE ${SOURCES_libpid})
set(DMTCP_PLUGINS libdmtcp_pid.so)
target_link_libraries(dmtcp_pid dl;pthread)
target_link_libraries(dmtcp_pid -Xlinker -znow  -Wl,--unresolved-symbols=ignore-all)
target_include_directories(dmtcp_pid PRIVATE pid)
INSTALL(TARGETS dmtcp_pid LIBRARY DESTINATION lib/dmtcp)

# =====================================================

set(SOURCES_libipc
    ipc/connection.cpp ipc/connectionidentifier.cpp ipc/connectionlist.cpp ipc/ipc.cpp ipc/event/eventconnection.cpp ipc/event/eventconnlist.cpp ipc/event/eventwrappers.cpp ipc/event/util_descriptor.cpp ipc/file/fileconnection.cpp ipc/file/fileconnlist.cpp ipc/file/filewrappers.cpp ipc/file/openwrappers.cpp ipc/file/posixipcwrappers.cpp ipc/file/ptyconnection.cpp ipc/file/ptyconnlist.cpp ipc/file/ptywrappers.cpp ipc/socket/connectionrewirer.cpp ipc/socket/kernelbufferdrainer.cpp ipc/socket/socketconnection.cpp ipc/socket/socketconnlist.cpp ipc/socket/socketwrappers.cpp ipc/ssh/ssh.cpp ipc/ssh/sshdrainer.cpp
)
add_library(dmtcp_ipc MODULE ${SOURCES_libipc})
set(DMTCP_PLUGINS ${DMTCP_PLUGINS} libdmtcp_ipc.so)
target_link_libraries(dmtcp_ipc dl;pthread;rt)
target_link_libraries(dmtcp_ipc -Xlinker -znow  -Wl,--unresolved-symbols=ignore-all)
target_include_directories(dmtcp_ipc PRIVATE ipc ipc/ssh)
INSTALL(TARGETS dmtcp_ipc LIBRARY DESTINATION lib/dmtcp)

# =====================================================

set(SOURCES_libtimer
    timer/timer_create.cpp timer/timerlist.cpp timer/timerwrappers.cpp
)
add_library(dmtcp_timer MODULE ${SOURCES_libtimer})
set(DMTCP_PLUGINS ${DMTCP_PLUGINS} libdmtcp_timer.so)
target_link_libraries(dmtcp_timer dl;pthread)
target_link_libraries(dmtcp_timer -Xlinker -znow  -Wl,--unresolved-symbols=ignore-all)
target_include_directories(dmtcp_timer PRIVATE timer)
INSTALL(TARGETS dmtcp_timer LIBRARY DESTINATION lib/dmtcp)

# # =====================================================

set(SOURCES_libsvipc
    svipc/sysvipc.cpp svipc/sysvipcwrappers.cpp
)
add_library(dmtcp_svipc MODULE ${SOURCES_libsvipc})
set(DMTCP_PLUGINS ${DMTCP_PLUGINS} libdmtcp_svipc.so)
target_link_libraries(dmtcp_svipc dl;pthread)
target_link_libraries(dmtcp_svipc -Xlinker -znow  -Wl,--unresolved-symbols=ignore-all)
target_include_directories(dmtcp_svipc PRIVATE svipc)
INSTALL(TARGETS dmtcp_svipc LIBRARY DESTINATION lib/dmtcp)

# # =====================================================

set(SOURCES_libdl
    dl/dlwrappers.cpp
)
add_library(dmtcp_dl MODULE ${SOURCES_libdl})
set(DMTCP_PLUGINS ${DMTCP_PLUGINS} libdmtcp_dl.so)
target_link_libraries(dmtcp_dl dl;pthread)
target_link_libraries(dmtcp_dl -Xlinker -znow  -Wl,--unresolved-symbols=ignore-all)
target_include_directories(dmtcp_dl PRIVATE dl)
INSTALL(TARGETS dmtcp_dl LIBRARY DESTINATION lib/dmtcp)

# # =====================================================

set(SOURCES_liballoc
    alloc/mallocwrappers.cpp alloc/mmapwrappers.cpp
)
add_library(dmtcp_alloc MODULE ${SOURCES_liballoc})
set(DMTCP_PLUGINS ${DMTCP_PLUGINS} libdmtcp_alloc.so)
target_link_libraries(dmtcp_alloc dl;pthread)
target_link_libraries(dmtcp_alloc -Xlinker -znow  -Wl,--unresolved-symbols=ignore-all)
target_include_directories(dmtcp_alloc PRIVATE alloc)
INSTALL(TARGETS dmtcp_alloc LIBRARY DESTINATION lib/dmtcp)

# =====================================================

# IN automake, i-util_ssh.o is being built from util_ssh.cpp
# and then used for libssh.a
add_library(ssh STATIC ipc/ssh/util_ssh.cpp)
target_include_directories(ssh PUBLIC ipc ipc/ssh)

add_executable(dmtcp_ssh ipc/ssh/dmtcp_ssh)
target_link_libraries(dmtcp_ssh ssh;dl;pthread)
add_executable(dmtcp_sshd ipc/ssh/dmtcp_sshd)
target_link_libraries(dmtcp_sshd ssh;dl;pthread)
INSTALL(TARGETS dmtcp_ssh dmtcp_sshd RUNTIME DESTINATION bin)

# =====================================================

set(SSH_EXECUTABLES dmtcp_ssh dmtcp_sshd)

# Starting with CMake-3.5, can specify multiple files for copying.
# Does one use '*' directly, or file(GLOB SOURCES dmtcp_*) and use CMake var?
foreach(loop_var ${SSH_EXECUTABLES})
# This can be automated using BUILDSYSTEM_TARGETS, starting with CMAKE-3.7
add_custom_target(
  private_install_${loop_var} ALL  # Add to list of 'ALL' default targets.
          # ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/bin
  # An alternative to copy is:  COMMAND ${CMAKE_COMMAND} create_symlink ...
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
                              ${loop_var} ${CMAKE_SOURCE_DIR}/bin/${loop_var}
  # This can be automated using BUILDSYSTEM_TARGETS, starting with CMAKE-3.7
  DEPENDS ${loop_var}
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/src/plugin # BINARY_DIR means "build dir"
  COMMENT Copying DMTCP ssh executables to in-source bin directory
)
add_dependencies(private_install_${loop_var} ${SSH_EXECUTABLES})
endforeach(loop_var)

# =====================================================

message("-- DMTCP Plugins:  ${DMTCP_PLUGINS}")

foreach(loop_var ${DMTCP_PLUGINS})
add_custom_target(
  private_install_${loop_var} ALL  # Add to list of 'ALL' default targets.
  # An alternative to copy is:  COMMAND ${CMAKE_COMMAND} create_symlink ...
  # COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/lib
  # COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/lib/dmtcp
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
                              ${loop_var} ${CMAKE_SOURCE_DIR}/lib/dmtcp/${loop_var}
  # This can be automated using BUILDSYSTEM_TARGETS, starting with CMAKE-3.7
  # FIXME:  If we just use ${loop_var} for DEPENDS, uses wrong WORKING_DIR
  #         Is this a bug in CMAKE-3.3?
  DEPENDS ${CMAKE_BINARY_DIR}/src/plugin/${loop_var}
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/src/plugin # BINARY_DIR means "build dir"
  COMMENT Copying DMTCP src/plugin libraries to in-source lib directory
)
add_dependencies(private_install_${loop_var} dmtcp_pid dmtcp_ipc dmtcp_timer)
endforeach(loop_var)
