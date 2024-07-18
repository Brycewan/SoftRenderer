cmake_minimum_required(VERSION 3.27)

project(SoftwareRenderer VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the include directory
include_directories(include)

# Add the SDL2 library
link_directories(${PROJECT_SOURCE_DIR}/lib/SDL)

# Add the source files
file(GLOB SOURCES "src/window/*.cpp")

# Add the executable
add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES} src/main.cpp)

# Link SDL2
target_link_libraries(SoftwareRenderer ${PROJECT_SOURCE_DIR}/lib/SDL/SDL2.lib ${PROJECT_SOURCE_DIR}/lib/SDL/SDL2main.lib)

# Copy SDL2.dll to the output directory
add_custom_command(TARGET SoftwareRenderer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/lib/SDL/SDL2.dll $<TARGET_FILE_DIR:SoftwareRenderer>)

