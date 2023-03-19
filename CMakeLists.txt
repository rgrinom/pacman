cmake_minimum_required(VERSION 3.20)

project(pacman)

set(HEADERS_DIR "${PROJECT_SOURCE_DIR}/headers")
set(SRC_DIR "${PROJECT_SOURCE_DIR}/source")
set(SOURCES
  ${SRC_DIR}/main.cpp
  ${SRC_DIR}/application.cpp
  ${SRC_DIR}/ghost.cpp
  ${SRC_DIR}/grid.cpp
  ${SRC_DIR}/logic.cpp
  ${SRC_DIR}/moving_object.cpp
  ${SRC_DIR}/point.cpp
  ${SRC_DIR}/red_ghost.cpp
  ${SRC_DIR}/sfml_ui.cpp
  ${SRC_DIR}/statistics.cpp
  ${SRC_DIR}/ui.cpp
)

find_package(SFML COMPONENTS window graphics system)

add_executable(pacman ${SOURCES})

target_include_directories(pacman 
  PRIVATE
    "${PROJECT_BINARY_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/include")

set_target_properties(pacman
  PROPERTIES
    INSTALL_RPATH_USE_LINK_PATH TRUE)

target_link_libraries(pacman sfml-graphics)