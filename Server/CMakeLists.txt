cmake_minimum_required(VERSION 3.27)
project(Server)

# We don't have crow on our system so we need to download it and build it.

include(FetchContent)

FetchContent_Declare(
  asio
  GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
  GIT_TAG asio-1-31-0
)

FetchContent_Declare(
  crow
  GIT_REPOSITORY https://github.com/CrowCpp/Crow.git
  GIT_TAG v1.2.0
)


FetchContent_MakeAvailable(asio)
set(ASIO_INCLUDE_DIR ${asio_SOURCE_DIR}/asio/include)

FetchContent_MakeAvailable(crow)



add_executable(server main.cpp)

target_include_directories(server PRIVATE 
    ${ASIO_INCLUDE_DIR}
    ${crow_SOURCE_DIR}/include
)
