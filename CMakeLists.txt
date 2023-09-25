cmake_minimum_required(VERSION 3.22)

project(hello_opengl VERSION 0.1.0)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")
set(CMAKE_BUILD_TYPE Debug)

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp)

add_library(glad "dependencies/library/glad.c")
target_include_directories(glad PRIVATE "dependencies/include")
target_include_directories(${PROJECT_NAME} PRIVATE "dependencies/include")
target_link_libraries(${PROJECT_NAME} glad ${CMAKE_DL_LIBS})

target_include_directories(${PROJECT_NAME} PUBLIC ${OPENGL_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
target_link_libraries(${PROJECT_NAME} "-framework IOKit")
target_link_libraries(${PROJECT_NAME} glfw ${OPENGL_gl_LIBRARY})
