cmake_minimum_required(VERSION 2.8.0)
project(dmtcp)

SET( CMAKE_C_FLAGS "${CMAKE_CXXFLAGS} -fPIC -g3 -O0" )
SET( CMAKE_CXX_FLAGS "${CMAKE_CXXFLAGS} -fPIC -g3 -O0" )

include_directories(./)

set(SOURCES_rse
  replace_symbols_elf.c; util.c;
)
add_executable(dmtcp_replace_symbols_elf ${SOURCES_rse})
INSTALL(TARGETS dmtcp_replace_symbols_elf RUNTIME DESTINATION bin)

#=================================================================

set (DMTCP_EXECUTABLES dmtcp_replace_symbols_elf)

foreach (loop_var ${DMTCP_EXECUTABLES})
add_custom_target(
  private_install_${loop_var} ALL
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
                           ${loop_var} ${CMAKE_SOURCE_DIR}/bin/
  DEPENDS ${loop_var}
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/static-util
  COMMENT Copying DMTCP executables to in-source bin directory - static-util dir
)
add_dependencies(private_install_${loop_var} ${DMTCP_EXECUTABLES})
endforeach(loop_var)
