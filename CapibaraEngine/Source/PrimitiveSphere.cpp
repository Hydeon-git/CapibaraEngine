#include "PrimitiveSphere.h"
#include <corecrt_math_defines.h>

// OpenGL
#include "glew.h"
#include "SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

void PrimitiveSphere::DrawSphere()
{
    double di = 0.02;
    double dj = 0.04;
    double du = di * 2 * M_PI;
    double dv = dj * M_PI;


    for (double i = 0; i < 1.0; i += di)  //horizonal
        for (double j = 0; j < 1.0; j += dj)  //vertical
        {
            double u = i * 2 * M_PI;      //0     to  2pi
            double v = (j - 0.5) * M_PI;  //-pi/2 to pi/2

            double  p[][3] = {
                cos(v) * cos(u)      ,cos(v) * sin(u)       ,sin(v),
                cos(v) * cos(u + du) ,cos(v) * sin(u + du)  ,sin(v),
                cos(v + dv) * cos(u + du) ,cos(v + dv) * sin(u + du)  ,sin(v + dv),
                cos(v + dv) * cos(u)      ,cos(v + dv) * sin(u)       ,sin(v + dv) };

            //normal
            glNormal3d(cos(v + dv / 2) * cos(u + du / 2), cos(v + dv / 2) * sin(u + du / 2), sin(v + dv / 2));

            glBegin(GL_POLYGON);
            glTexCoord2d(i, j);    glVertex3dv(p[0]);
            glTexCoord2d(i + di, j);    glVertex3dv(p[1]);
            glTexCoord2d(i + di, j + dj); glVertex3dv(p[2]);
            glTexCoord2d(i, j + dj); glVertex3dv(p[3]);
            glEnd();
        }
}
