cmake_minimum_required(VERSION 3.5...3.14)

project(pcaper VERSION 1.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PP_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(PP_SOURCE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/source")

set(PCAPER_HDR
        ${PP_INCLUDE_PATH}/ethernet.h
        ${PP_INCLUDE_PATH}/http.h
        ${PP_INCLUDE_PATH}/ip.h
        ${PP_INCLUDE_PATH}/tcp.h
        ${PP_INCLUDE_PATH}/pcap.h
        ${PP_INCLUDE_PATH}/packet.h

)

set(PCAPER_SRC
        ${PP_SOURCE_PATH}/ethernet.cpp
        ${PP_SOURCE_PATH}/http.cpp
        ${PP_SOURCE_PATH}/ip.cpp
        ${PP_SOURCE_PATH}/tcp.cpp
        ${PP_SOURCE_PATH}/pcap.cpp
        ${PP_SOURCE_PATH}/packet.cpp
)

find_package(Qt5 COMPONENTS Core REQUIRED)

add_subdirectory(${PP_SOURCE_PATH})

add_library(
        ${PROJECT_NAME}
        ${PCAPER_HDR} ${PCAPER_SRC}
)

target_link_libraries(
        ${PROJECT_NAME}
        PRIVATE Qt5::Core
)
