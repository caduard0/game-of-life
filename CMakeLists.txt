cmake_minimum_required(VERSION 3.5)
project("game-of-life" VERSION 0.1)

find_package(OpenGL REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW lib only")
set(GLFW_INSTALL OFF CACHE BOOL "GLFW lib only")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glfw")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glad")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME})

file(GLOB_RECURSE EXEC_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE PRIVATE_INCLUDE CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")

target_sources(${PROJECT_NAME} PRIVATE "${EXEC_SOURCES}")

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/gmtl/include")

target_include_directories(${PROJECT_NAME} PRIVATE "${PRIVATE_INCLUDE}")
target_include_directories(${PROJECT_NAME} PRIVATE "${OPENGL_INCLUDE_DIRS}")

target_link_libraries(${PROJECT_NAME} PRIVATE glfw glad "-static" "-static-libstdc++" "-static-libstdc++")


