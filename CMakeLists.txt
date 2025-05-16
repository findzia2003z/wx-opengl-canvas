cmake_minimum_required(VERSION 3.10)
project(GLCanvasApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(OpenGL REQUIRED)
find_package(wxWidgets REQUIRED gl core base)
include(${wxWidgets_USE_FILE})

# Add source files
set(SOURCES
    src/main.cpp
    src/MainFrame.cpp
    src/GLCanvas.cpp
    src/ControlPanel.cpp
)

set(HEADERS
    include/MainFrame.h
    include/GLCanvas.h
    include/ControlPanel.h
)

# Add executable
add_executable(${PROJECT_NAME} WIN32 ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${OPENGL_INCLUDE_DIR}
)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${wxWidgets_LIBRARIES}
    ${OPENGL_LIBRARIES}
)

# Copy resources to build directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources) 