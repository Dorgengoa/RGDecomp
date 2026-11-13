# SPDX-License-Identifier: CC0-1.0
# Online Insectron 2-Player Battle transport (lane insnet, docs/INSECTRON-VERSUS.md "Online").
# Plain Winsock / BSD sockets; nothing opens a socket unless the player hosts or joins.
add_library(rg_net STATIC rg_net.h rg_net.c)
target_include_directories(rg_net PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(rg_net PRIVATE rg_flags)
if(WIN32)
  target_link_libraries(rg_net PUBLIC ws2_32)
endif()

add_executable(rg-net-tests tests/net_tests.c)
target_link_libraries(rg-net-tests PRIVATE rg_net rg_flags)
foreach(t frames stream address loopback)
  add_test(NAME net.${t} COMMAND rg-net-tests ${t})
  set_tests_properties(net.${t} PROPERTIES TIMEOUT 60 LABELS net)
endforeach()

foreach(t rg_net rg-net-tests)
  if(WIN32)
    target_compile_definitions(${t} PRIVATE _CRT_SECURE_NO_WARNINGS _WINSOCK_DEPRECATED_NO_WARNINGS)
  endif()
  if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(${t} PRIVATE -Wall -Wextra)
  endif()
endforeach()
