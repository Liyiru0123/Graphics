// Wedge workpiece - Graphics assignment team, AI-assisted, 2026-11-24.
#include "wedge.h"
#include <glm/glm.hpp>

// Build a triangular prism from six corners and eight outward-facing triangles.
// Duplicate vertices across faces so sharp edges have separate face normals.
void Wedge::makeWedge()
{
    release();
    const glm::vec3 corners[] = {
        {-0.08f, 0, -0.06f}, {0.08f, 0, -0.06f}, {0.08f, 0.08f, -0.06f},
        {-0.08f, 0,  0.06f}, {0.08f, 0,  0.06f}, {0.08f, 0.08f,  0.06f}
    };
    const unsigned triangles[8][3] = {
        {0, 2, 1}, {3, 4, 5},             // back and front
        {0, 1, 4}, {0, 4, 3},             // bottom
        {1, 2, 5}, {1, 5, 4},             // vertical end
        {0, 3, 5}, {0, 5, 2}              // sloping top
    };
    GLfloat positions[24 * 3], normals[24 * 3], colours[24 * 4];
    for (unsigned face = 0; face < 8; ++face)
    {
        const glm::vec3 a = corners[triangles[face][0]];
        const glm::vec3 b = corners[triangles[face][1]];
        const glm::vec3 c = corners[triangles[face][2]];
        // CCW winding gives the outward unit normal using the right-hand rule.
        const glm::vec3 normal = glm::normalize(glm::cross(b - a, c - a));
        for (unsigned v = 0; v < 3; ++v)
        {
            const unsigned index = face * 3 + v;
            const glm::vec3 p = corners[triangles[face][v]];
            for (unsigned axis = 0; axis < 3; ++axis)
            {
                positions[index * 3 + axis] = p[axis];
                normals[index * 3 + axis] = normal[axis];
            }
            colours[index * 4] = 0.95f;
            colours[index * 4 + 1] = 0.65f;
            colours[index * 4 + 2] = 0.12f;
            colours[index * 4 + 3] = 1.0f;
        }
    }
    glGenBuffers(3, buffers);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colours), colours, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Uses the caller's VAO, lighting program, model matrix and normal matrix.
void Wedge::drawWedge(int drawmode)
{
    for (GLuint attribute = 0; attribute < 3; ++attribute)
    {
        glBindBuffer(GL_ARRAY_BUFFER, buffers[attribute]);
        glEnableVertexAttribArray(attribute);
        glVertexAttribPointer(attribute, attribute == 1 ? 4 : 3, GL_FLOAT,
                              GL_FALSE, 0, nullptr);
    }
    GLint polygonMode[2];
    GLfloat pointSize;
    glGetIntegerv(GL_POLYGON_MODE, polygonMode);
    glGetFloatv(GL_POINT_SIZE, &pointSize);
    glPolygonMode(GL_FRONT_AND_BACK, drawmode == 1 ? GL_LINE : GL_FILL);
    glPointSize(3.0f);
    glDrawArrays(drawmode == 2 ? GL_POINTS : GL_TRIANGLES, 0, 24);
    glPolygonMode(GL_FRONT_AND_BACK, polygonMode[0]);
    glPointSize(pointSize);
    for (GLuint attribute = 0; attribute < 3; ++attribute)
        glDisableVertexAttribArray(attribute);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Explicit cleanup avoids GL calls from a global destructor after window teardown.
void Wedge::release()
{
    glDeleteBuffers(3, buffers);
    buffers[0] = buffers[1] = buffers[2] = 0;
}
