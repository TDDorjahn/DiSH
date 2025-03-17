cmake_minimum_required(VERSION 3.20)
find_package(Catch2 3 REQUIRED)

set(CMAKE_IGNORE_PATH "./build")
set(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG")

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

include_directories(${HEADER_LIST})

file(GLOB TEST_SOURCES "*.cpp")

foreach(TEST_FILE ${TEST_SOURCES})

    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)

    add_executable(${TEST_NAME} ${TEST_FILE})

    target_link_libraries(${TEST_NAME} PRIVATE Catch2::Catch2WithMain dsh_lib)

    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()