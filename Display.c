#include "Display.h"

const int INIT_WINDOW_SIZE_X = 1280;
const int INIT_WINDOW_SIZE_Y = 720;
const int INIT_WINDOW_POS_X = -1;
const int INIT_WINDOW_POS_Y = -1;
const char * WINDOW_TITLE = "ICT289 Game";
const int PERSPECTIVE_FOV = 45;
const float PERSPECTIVE_NEAR = 0.1f;
const float PERSPECTIVE_FAR = 1000.0f;

void InitializeGLUT(int * argc, char ** argv)
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH); // Initialize display modes, with RGBA, double buffering, and a depth buffer.
    glutInitWindowPosition(INIT_WINDOW_POS_X, INIT_WINDOW_POS_Y);
    glutInitWindowSize(INIT_WINDOW_SIZE_X, INIT_WINDOW_SIZE_Y);
    glutCreateWindow(WINDOW_TITLE);
    glutDisplayFunc(DisplayCallback);
    glutReshapeFunc(ReshapeCallback);
    glClearColor(0.3922f, 0.5843f, 0.9294f, 1.0f);

    //-- Backface culling

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

}

void DisplayCallback()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
        glColor3f(0.4039f, 0.7373f, 0.6314f);
        glVertex3f(0.0f, 0.5f, -2.0f);
        glColor3f(0.5882f, 0.1294f, 0.2118f);
        glVertex3f(0.5f, -0.5f, -3.0f);
        glColor3f(0.2235f, 0.302f, 0.5176f);
        glVertex3f(-0.5f, -0.5f, -4.0f);
    glEnd();

    glutSwapBuffers();
}

void ReshapeCallback(int x, int y)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, x, y);
    gluPerspective(PERSPECTIVE_FOV, x/y, PERSPECTIVE_NEAR, PERSPECTIVE_FAR);
    glMatrixMode(GL_MODELVIEW);
}
