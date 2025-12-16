cmake_minimum_required(VERSION 3.20)
project(OpenGLTest)

set(CMAKE_CXX_STANDARD 17)

# -----------------------------
# GLFW
# -----------------------------
if (EXISTS "/opt/homebrew/lib/libglfw.3.dylib")
    set(GLFW3_INCLUDE_DIR "/opt/homebrew/include")
    set(GLFW3_LIBRARY "/opt/homebrew/lib/libglfw.3.dylib")
elseif (EXISTS "/usr/local/lib/libglfw.3.dylib")
    set(GLFW3_INCLUDE_DIR "/usr/local/include")
    set(GLFW3_LIBRARY "/usr/local/lib/libglfw.3.dylib")
else ()
    message(FATAL_ERROR "GLFW not found. Install with: brew install glfw")
endif ()

include_directories(${GLFW3_INCLUDE_DIR})

# -----------------------------
# GLEW
# -----------------------------
set(GLEW_INCLUDE_DIR "/opt/homebrew/include")
set(GLEW_LIBRARY "/opt/homebrew/lib/libGLEW.dylib")

include_directories(${GLEW_INCLUDE_DIR})

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

# -----------------------------
# Link libraries and frameworks
# -----------------------------
target_link_libraries(OpenGL
        ${GLFW3_LIBRARY}
        ${GLEW_LIBRARY}
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
)
