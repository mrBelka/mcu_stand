cmake_minimum_required(VERSION 3.15)						
set(PROJECT_NAME simple_web) 					 
project("${PROJECT_NAME}")
set(CMAKE_CXX_STANDARD 20)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GPIODCXX REQUIRED libgpiodcxx>=2.0)

include_directories("./ext/asio-cpp")
include_directories("./ext/crow-cpp")

add_executable("${PROJECT_NAME}" main.cpp)

target_include_directories("${PROJECT_NAME}" PRIVATE ${GPIODCXX_INCLUDE_DIRS})
target_link_libraries("${PROJECT_NAME}" PRIVATE ${GPIODCXX_LIBRARIES})