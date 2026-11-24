// Wedge workpiece - Graphics assignment team, AI-assisted, 2026-11-24.
#pragma once
#include "wrapper_glfw.h"

// Bottom centre is the origin; +Y is up. Dimensions: 0.16 x 0.08 x 0.12.
class Wedge
{
public:
    void makeWedge();
    void drawWedge(int drawmode);
    // Call while the OpenGL context still exists.
    void release();
    Wedge() = default;
    Wedge(const Wedge&) = delete;
    Wedge& operator=(const Wedge&) = delete;
private:
    GLuint buffers[3] = {0, 0, 0};
};
