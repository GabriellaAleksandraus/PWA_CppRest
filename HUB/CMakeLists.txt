cmake_minimum_required(VERSION 3.25)
project(HUB)

include(FetchContent)

# is to include the library into this project
FetchContent_Declare(
    cpr 
    GIT_REPOSITORY https://github.com/libcpr/cpr.git
    GIT_TAG 1.11.0
)

# Actually downloads the files
FetchContent_MakeAvailable(cpr)

# Most linux systems already have these libraries so we just want to find them on the computer
find_package(PkgConfig REQUIRED)
pkg_check_modules(BLUEZ REQUIRED bluez)

# Add the files needed to run the program
add_executable(hub main.cpp)

#Include directories
target_include_directories(hub PRIVATE 
    ${BLUEZ_INCLUDE_DIRS}
    ${cpr_SOURCE_DIR}/include/cpr
)


# Link libraries
target_link_libraries(hub PRIVATE 
    ${BLUEZ_LIBRARIES}
    cpr::cpr
)
