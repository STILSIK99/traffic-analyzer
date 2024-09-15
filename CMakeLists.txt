cmake_minimum_required(VERSION 3.5...3.14)

project(remastered LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(SOURCE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/source")
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")

set(BUILD_SHARED_LIBS ON)

find_package(Qt5 COMPONENTS Core Sql REQUIRED)

#-----include pcaper lib--------------------------------------------------
set(PP_LIB "${LIB_DIR}/pcaper")
set(PP_INCLUDE_PATH "${PP_LIB}/include")
set(PP_SOURCE_PATH "${PP_LIB}/source")
set(PP_HEADERS
        ${PP_INCLUDE_PATH}/ethernet.h
        ${PP_INCLUDE_PATH}/http.h
        ${PP_INCLUDE_PATH}/ip.h
        ${PP_INCLUDE_PATH}/tcp.h
        ${PP_INCLUDE_PATH}/pcap.h
        ${PP_INCLUDE_PATH}/packet.h
        ${PP_INCLUDE_PATH}/udp.h

)
set(PP_SOURCES
        ${PP_SOURCE_PATH}/ethernet.cpp
        ${PP_SOURCE_PATH}/http.cpp
        ${PP_SOURCE_PATH}/ip.cpp
        ${PP_SOURCE_PATH}/tcp.cpp
        ${PP_SOURCE_PATH}/pcap.cpp
        ${PP_SOURCE_PATH}/packet.cpp
        ${PP_SOURCE_PATH}/udp.cpp

)
#add_subdirectory(${PP_LIB} "${CMAKE_BINARY_DIR}/lib/pcaper")

#-----include database lib------------------------------------------------
set(DB_LIB "${LIB_DIR}/database")
set(DB_INCLUDE_PATH "${DB_LIB}/include")
set(DB_SOURCE_PATH "${DB_LIB}/source")
set(DB_HEADERS
        ${DB_INCLUDE_PATH}/database.h
        ${DB_INCLUDE_PATH}/csv_report.h
)
set(DB_SOURCES
        ${DB_SOURCE_PATH}/database.cpp
        ${DB_SOURCE_PATH}/csv_report.cpp
)

#-----include source files------------------------------------------------
set(HEADERS
        ${INCLUDE_PATH}/traffic_parser.h
        ${INCLUDE_PATH}/tools.h
        ${INCLUDE_PATH}/exceptions.h
        ${INCLUDE_PATH}/config.h
        ${INCLUDE_PATH}/processor.h
        ${INCLUDE_PATH}/vars.h
)
set(SOURCES
        ${SOURCE_PATH}/traffic_parser.cpp
        ${SOURCE_PATH}/tools.cpp
        ${SOURCE_PATH}/config.cpp
        ${SOURCE_PATH}/processor.cpp
)




include_directories(
        ${PP_INCLUDE_PATH}
        ${DB_INCLUDE_PATH}
        ${INCLUDE_PATH}
)


#add_subdirectory(${SOURCE_PATH})

add_executable(remastered
        main.cpp
        ${PP_HEADERS}
        ${PP_SOURCES}
        ${DB_HEADERS}
        ${DB_SOURCES}
        ${HEADERS}
        ${SOURCES}
)

target_link_libraries(remastered
        Qt5::Core Qt5::Sql
)
