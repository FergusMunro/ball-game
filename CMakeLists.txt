cmake_minimum_required(VERSION 3.28.3)
project(ballGame VERSION 1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(CTest)
enable_testing()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

find_package(raylib REQUIRED)
find_package(Catch2 REQUIRED)

file(GLOB_RECURSE SRC_FILES src/main/*.cpp)
add_executable(${PROJECT_NAME} ${SRC_FILES} ${CMAKE_CURRENT_SOURCE_DIR}/Main.cpp)

file(GLOB_RECURSE TEST_FILES src/test/*.cpp)
add_executable(tests ${SRC_FILES} ${TEST_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib)

target_include_directories(tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib)

target_link_libraries(${PROJECT_NAME} PUBLIC raylib)
target_link_libraries(tests PRIVATE Catch2::Catch2 raylib)

add_test(tests, "${CMAKE_CURRENT_SOURCE_DIR}/bin/tests")
