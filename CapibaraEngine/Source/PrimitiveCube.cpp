#include "PrimitiveCube.h"
#include <corecrt_math_defines.h>

// OpenGL
#include "glew.h"
#include "SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

void PrimitiveCube::DrawCube()
{
    // vertex array
    GLfloat vertices1[] = { 1, 1, 1,  -1, 1, 1,  -1,-1, 1,      // v0-v1-v2 (front)
                       -1,-1, 1,   1,-1, 1,   1, 1, 1,      // v2-v3-v0

                        1, 1, 1,   1,-1, 1,   1,-1,-1,      // v0-v3-v4 (right)
                        1,-1,-1,   1, 1,-1,   1, 1, 1,      // v4-v5-v0

                        1, 1, 1,   1, 1,-1,  -1, 1,-1,      // v0-v5-v6 (top)
                       -1, 1,-1,  -1, 1, 1,   1, 1, 1,      // v6-v1-v0

                       -1, 1, 1,  -1, 1,-1,  -1,-1,-1,      // v1-v6-v7 (left)
                       -1,-1,-1,  -1,-1, 1,  -1, 1, 1,      // v7-v2-v1

                       -1,-1,-1,   1,-1,-1,   1,-1, 1,      // v7-v4-v3 (bottom)
                        1,-1, 1,  -1,-1, 1,  -1,-1,-1,      // v3-v2-v7

                        1,-1,-1,  -1,-1,-1,  -1, 1,-1,      // v4-v7-v6 (back)
                       -1, 1,-1,   1, 1,-1,   1,-1,-1 };    // v6-v5-v4
    // normal array
    GLfloat normals1[] = { 0, 0, 1,   0, 0, 1,   0, 0, 1,      // v0-v1-v2 (front)
                            0, 0, 1,   0, 0, 1,   0, 0, 1,      // v2-v3-v0

                            1, 0, 0,   1, 0, 0,   1, 0, 0,      // v0-v3-v4 (right)
                            1, 0, 0,   1, 0, 0,   1, 0, 0,      // v4-v5-v0

                            0, 1, 0,   0, 1, 0,   0, 1, 0,      // v0-v5-v6 (top)
                            0, 1, 0,   0, 1, 0,   0, 1, 0,      // v6-v1-v0

                           -1, 0, 0,  -1, 0, 0,  -1, 0, 0,      // v1-v6-v7 (left)
                           -1, 0, 0,  -1, 0, 0,  -1, 0, 0,      // v7-v2-v1

                            0,-1, 0,   0,-1, 0,   0,-1, 0,      // v7-v4-v3 (bottom)
                            0,-1, 0,   0,-1, 0,   0,-1, 0,      // v3-v2-v7

                            0, 0,-1,   0, 0,-1,   0, 0,-1,      // v4-v7-v6 (back)
                            0, 0,-1,   0, 0,-1,   0, 0,-1 };    // v6-v5-v4
    // color array
    GLfloat colors1[] = { 1, 1, 1,   1, 1, 0,   1, 0, 0,      // v0-v1-v2 (front)
                            1, 0, 0,   1, 0, 1,   1, 1, 1,      // v2-v3-v0

                            1, 1, 1,   1, 0, 1,   0, 0, 1,      // v0-v3-v4 (right)
                            0, 0, 1,   0, 1, 1,   1, 1, 1,      // v4-v5-v0

                            1, 1, 1,   0, 1, 1,   0, 1, 0,      // v0-v5-v6 (top)
                            0, 1, 0,   1, 1, 0,   1, 1, 1,      // v6-v1-v0

                            1, 1, 0,   0, 1, 0,   0, 0, 0,      // v1-v6-v7 (left)
                            0, 0, 0,   1, 0, 0,   1, 1, 0,      // v7-v2-v1

                            0, 0, 0,   0, 0, 1,   1, 0, 1,      // v7-v4-v3 (bottom)
                            1, 0, 1,   1, 0, 0,   0, 0, 0,      // v3-v2-v7

                            0, 0, 1,   0, 0, 0,   0, 1, 0,      // v4-v7-v6 (back)
                            0, 1, 0,   0, 1, 1,   0, 0, 1 };    // v6-v5-v4

    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glNormalPointer(GL_FLOAT, 0, normals1);
    glColorPointer(3, GL_FLOAT, 0, colors1);
    glVertexPointer(3, GL_FLOAT, 0, vertices1);

    glPushMatrix();
    glTranslatef(2, 2, 0);

    glDrawArrays(GL_TRIANGLES, 0, 36);

    glPopMatrix();

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}
