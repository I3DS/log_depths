cmake_minimum_required(VERSION 3.0)

project(log_depths LANGUAGES CXX)

set(PROJECT_AUTHOR "SINTEF Digital")
set(PROJECT_URL "http://i3ds-h2020.eu/")
set(PROJECT_LICENSE "MPLv2")
set(PROJECT_VERSION "1.0")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package (Boost COMPONENTS program_options log REQUIRED)

add_executable(log_depths main.cpp)

set (LIBS
    zmq
    i3ds
    i3ds_asn1
    i3ds_clients
    ${Boost_LIBRARIES}
  )

target_link_libraries(log_depths ${LIBS})
