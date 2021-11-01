#include "PrimitiveCube.h"

// OpenGL
#include "glew.h"
#include "SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#define PI 3.1415926535898
#define Cos(th) cos(PI/180*(th))
#define Sin(th) sin(PI/180*(th))
#define DEF_D 5

void PrimitiveCube::DrawCube()
{
    int th2, ph2, i, j, k;

    glBegin(GL_QUAD_STRIP);
    for (j = 0; j <= 360; j += DEF_D) {
        glColor3f(1.0, 1.0, 0.0);
        glVertex3f(Cos(j), +1, Sin(j));
        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(Cos(j), -1, Sin(j));
    }
    glEnd();

    /* top and bottom circles */
    /* reuse the currentTexture on top and bottom) */
    for (i = 1; i >= -1; i -= 2) {
        glBegin(GL_TRIANGLE_FAN);
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(0, i, 0);
        for (k = 0; k <= 360; k += DEF_D) {
            glColor3f(1.0, 0.0, 0.0);
            glVertex3f(i * Cos(k), i, Sin(k));
        }
        glEnd();
    }

    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);

    glPushMatrix();
    glTranslatef(2, 2, 0);

    glDrawArrays(GL_TRIANGLES, 0, 36);

    glPopMatrix();

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}
