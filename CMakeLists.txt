cmake_minimum_required(VERSION 3.21)
project(l2bin_wrapper
        VERSION 1.0.0
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (NOT DEFINED FILENAME_TO_REPLACE)
    set(FILENAME_TO_REPLACE L2.bin)
endif ()
if (NOT DEFINED FILENAME_TO_LAUNCH)
    set(FILENAME_TO_LAUNCH L2.exe)
endif ()
if (NOT DEFINED OVERRIDE_IP)
    set(OVERRIDE_IP 0)
endif ()
if (NOT DEFINED ADDRESS_OVERRIDE_IP)
    set(ADDRESS_OVERRIDE_IP 127.0.0.1)
endif ()
if (NOT DEFINED OVERRIDE_L2INI)
    set(OVERRIDE_L2INI 1)
endif ()
if (NOT DEFINED FILENAME_OVERRIDE_L2INI)
    set(FILENAME_OVERRIDE_L2INI L2_.ini)
endif ()
if (NOT DEFINED OVERRIDE_USERINI)
    set(OVERRIDE_USERINI 0)
endif ()
if (NOT DEFINED FILENAME_OVERRIDE_USERINI)
    set(FILENAME_OVERRIDE_USERINI User_.ini)
endif ()

configure_file(customization.h.in customization.h)
configure_file(version.h.in version.h)
add_executable(${PROJECT_NAME}
        main.cpp
        res/version.rc
        src/args.cpp
        src/args.h
        src/paths.cpp
        src/paths.h)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${FILENAME_TO_REPLACE})

target_include_directories(${PROJECT_NAME}
        PUBLIC "${PROJECT_BINARY_DIR}")

add_definitions(-DUNICODE -D_UNICODE -D_WINDOWS -D_X86_)
target_compile_options(${PROJECT_NAME}
        PRIVATE /sdl
        PRIVATE /W3
        PRIVATE /permissive-)
target_link_options(${PROJECT_NAME}
        PRIVATE /SUBSYSTEM:WINDOWS
        PRIVATE "/MANIFESTUAC:level='asInvoker' uiAccess='false'")

configure_file(LICENSE LICENSE COPYONLY)
configure_file(README.md README.md COPYONLY)

if (${CREATE_VERSION_FILE})
    file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/version.txt ${PROJECT_VERSION}${VERSION_SUFFIX})
endif ()

add_custom_command(TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND move /Y ${FILENAME_TO_REPLACE}.exe ${FILENAME_TO_REPLACE}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>)
