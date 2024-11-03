cmake_minimum_required(VERSION 3.27)
project(HUB)


find_package(PkgConfig REQUIRED)
pkg_check_modules(BLUEZ REQUIRED bluez)

#Include directories
include_directories(${BLUEZ_INCLUDE_DIRS})

add_executable(hub main.cpp)

# Link libraries
target_link_libraries(hub ${BLUEZ_LIBRARIES})