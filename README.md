# OpenGL Test

### Repo description

This Repo is just a repo for me to test a bit and play around with OpenGL,
as well as for me to abstract away a bit of OpenGl functionality once I start
taking a look at developing a game engine.

### Project Structure

**Language**: C++, GLSL
**Build System**: CMake
**External Libraries**:

- [OpenGl](https://github.com/McNopper/OpenGL.git) (For graphics rendering)
- [stb_image](https://github.com/nothings/stb.git) (For converting resources like images into a texture format)
- [GLEW](https://github.com/nigels-com/glew.git) (For recognizing which OpenGl functions the GPU allows)
- [GLFW](https://github.com/glfw/glfw.git) (For creating windows on all operating systems, without explicitly accessing the OS API)
- [glm](https://github.com/icaven/glm.git) (OpenGL Maths library)
- [ImGui](https://github.com/ocornut/imgui.git) (GUI Library for debugging)

### Set up

As this is just a demo with no real use you can play around with it, so you yourself can learn a bit about OpenGl.

```bash
git clone https://github.com/Amir-jpg-png/OpenGl_Test.git
```

Afterwards you can build and run the project like this

```bash
./build.sh
```
