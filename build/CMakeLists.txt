cmake_minimum_required(VERSION 3.16)
project(paintdotnix)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "-lharfbuzz -std=c++23")
set(CMAKE_EXPORT_COMPILE_COMMANDS )
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../output)

set(VENDOR_HEADER_FILES
                )

set(INTERNAL_HEADER_FILES
                ../internal/text_renderer/text_renderer.h
                )

set(VENDOR_SOURCE_FILES
                )

set(INTERNAL_SOURCE_FILES
                ../internal/text_renderer/text_renderer.cpp
                )

set(SOURCE_FILES ../src/main.cpp
                ${INTERNAL_SOURCE_FILES}
                ${VENDOR_SOURCE_FILES}
                ${INTERNAL_HEADER_FILES}
                ${VENDOR_HEADER_FILES}
                )

include_directories(../vendor
                ../internal/text_renderer
                )

add_executable(paintdotnix ${SOURCE_FILES})
target_precompile_headers(paintdotnix PRIVATE ${VENDOR_HEADER_FILES})
