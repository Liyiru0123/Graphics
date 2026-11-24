# Assembly Workcell

An interactive 3D assembly workcell built with C++ and modern OpenGL for DI41008 Graphics, Assignment 1 (Action Scene).

## Scene

- A two-link robotic arm uses parent–child transforms so the forearm follows the shoulder while rotating at the elbow.
- A feed tray slides along rails and carries a custom wedge workpiece.
- A fixture rotates with an offset jaw, and a press ram moves vertically.
- A perspective camera and a movable point light let you inspect the mechanisms and their shading.

The wedge is an original triangular prism with six corners and eight triangles. Its face normals are calculated from triangle edges and stored as vertex attributes in a VBO. The project extends the course's Lab 4 `poslight` example and uses its GLFW, GLAD and GLM setup.

## Build and run

1. On 64-bit Windows, install Visual Studio 2022 with **Desktop development with C++**, the **MSVC v143 x64/x86** toolset and a Windows SDK. The graphics driver must support OpenGL 4.2.
2. Clone the repository and open [graphics_examples.sln](first_programs/graphics_examples/graphics_examples.sln).
3. Set **postlight** as the startup project, select **Release / x64**, and press **Ctrl+F5**.

The build copies `poslight.vert` and `poslight.frag` next to `postlight.exe`. Keep these three files together when running the executable outside Visual Studio.

## Controls

| Input | Action |
| --- | --- |
| Arrow keys | Orbit around the workcell |
| Page Up / Page Down | Zoom in / out |
| A / D, W / S | Move the light along the horizontal and vertical axes |
| Q / E | Move the light along the depth axis |
| Home | Reset the camera and light |
| = or + / − | Increase / decrease animation speed |
| F | Reverse the mechanisms from their current positions |
| Space | Pause / resume animation |
| M | Toggle object colour mode |
| Period / comma | Toggle light falloff / cycle rendering modes |
| Esc | Exit |
