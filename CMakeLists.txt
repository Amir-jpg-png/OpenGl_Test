cmake_minimum_required(VERSION 3.20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(OpenGLTest)
set(CMAKE_CXX_STANDARD 17)

# -----------------------------
# required libraries
# -----------------------------
find_package(glfw3 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

# -----------------------------
# Executable
# -----------------------------
add_executable(OpenGL
        Application.cpp
        include/Renderer.hpp
        include/VertexBuffer.hpp
        include/IndexBuffer.hpp
        include/VertexArray.hpp
        include/VertexBufferLayout.hpp
        src/Renderer.cpp
        src/VertexBuffer.cpp
        src/IndexBuffer.cpp
        src/VertexArray.cpp
        src/Shader.cpp
        include/Shader.hpp
        lib/stb_image.h
        lib/stb_image.cpp
        include/Texture.hpp
        src/Texture.cpp
)

#-------------------------------
# Link Libraries
#-------------------------------
target_link_libraries(OpenGL
    PRIVATE
        glfw
        GLEW::GLEW
        OpenGL::GL
)

#------------------------------
# Set output directory
#------------------------------

set_target_properties(OpenGL PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)
