cmake_minimum_required (VERSION 3.11)

project(ftxui-game LANGUAGES CXX VERSION 1.0.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Threads)
find_package(ftxui 5 REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE src)

target_link_libraries(${PROJECT_NAME}
  PRIVATE ftxui::screen ftxui::dom ftxui::component
)
install(TARGETS ${PROJECT_NAME} RUNTIME)
