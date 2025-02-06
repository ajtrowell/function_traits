cmake_minimum_required(VERSION 3.5)
project(ruak)

set(CMAKE_CXX_STANDARD 20)

file(GLOB srcs src/*.cpp)

add_executable(${PROJECT_NAME} ${srcs})
target_include_directories(${PROJECT_NAME} PRIVATE "include")

include(FetchContent)

FetchContent_Declare(
  glaze
  GIT_REPOSITORY https://github.com/stephenberry/glaze.git
  GIT_TAG main
  GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(glaze)
target_link_libraries(${PROJECT_NAME} glaze::glaze)
