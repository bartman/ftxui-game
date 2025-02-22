cmake_minimum_required (VERSION 3.11)

project(game LANGUAGES CXX VERSION 1.0.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Threads)
find_package(ftxui 5 REQUIRED)

add_executable(game src/main.cpp)
target_include_directories(game PRIVATE src)

target_link_libraries(game
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component # Not needed for this example.
)

