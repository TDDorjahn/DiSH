cmake_minimum_required(VERSION 3.20)
project(DSH)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_IGNORE_PATH "./build")
set(HOME_DIR    ${CMAKE_SOURCE_DIR})
set(CORE_DIR    ${HOME_DIR}/core)
set(EXEC_DIR    ${HOME_DIR}/exec)
set(FS_DIR      ${HOME_DIR}/fs)
set(HISTORY_DIR ${HOME_DIR}/history)
set(IO_DIR      ${HOME_DIR}/io)
set(PARSER_DIR  ${HOME_DIR}/parser)
set(SIGNALS_DIR ${HOME_DIR}/signals)
set(USR_DIR     ${HOME_DIR}/usr)

set(CORE_HEADER_DIR     ${CORE_DIR}/interface)
set(TOOLS_HEADER_DIR    ${CORE_HEADER_DIR}/tools)
set(EXEC_HEADER_DIR     ${EXEC_DIR}/interface)
set(FS_HEADER_DIR       ${FS_DIR}/interface)
set(HISTORY_HEADER_DIR  ${HISTORY_DIR}/interface)
set(IO_HEADER_DIR       ${IO_DIR}/interface)
set(PARSER_HEADER_DIR   ${PARSER_DIR}/interface)
set(SIGNALS_HEADER_DIR  ${SIGNALS_DIR}/interface)
set(USR_HEADER_DIR      ${USR_DIR}/interface)

set(CORE_SRC_DIR    ${CORE_DIR}/src)
set(EXEC_SRC_DIR    ${EXEC_DIR}/src)
set(FS_SRC_DIR      ${FS_DIR}/src)
set(HISTORY_SRC_DIR ${HISTORY_DIR}/src)
set(IO_SRC_DIR      ${IO_DIR}/src)
set(PARSER_SRC_DIR  ${PARSER_DIR}/src)
set(SIGNALS_SRC_DIR ${SIGNALS_DIR}/src)
set(USR_SRC_DIR     ${USR_DIR}/src)

set(HEADER_LIST ${CORE_HEADER_DIR} ${EXEC_HEADER_DIR} ${FS_HEADER_DIR} ${HISTORY_HEADER_DIR} ${IO_HEADER_DIR} ${PARSER_HEADER_DIR} ${SIGNALS_HEADER_DIR} ${USR_HEADER_DIR} ${TOOLS_DIR})
set(SRC_LIST ${CORE_SRC_DIR} ${EXEC_SRC_DIR} ${FS_SRC_DIR} ${HISTORY_SRC_DIR} ${IO_SRC_DIR} ${SIGNAL_SRC_DIR} ${USR_SRC_DIR})

include_directories(${HEADER_LIST})

file(GLOB_RECURSE SRCS ${SRC_LIST}/*.cpp)
file(GLOB_RECURSE HEADERS ${HEADER_LIST}/*.hpp)

add_library(dsh_lib ${SRCS})

add_executable(dsh main.cpp)
target_link_libraries(dsh PRIVATE dsh_lib)

enable_testing()
add_subdirectory(tests)