#include <stdio.h>
#include <stdlib.h>
// Cross platform freeglut compile
#ifdef _WIN32
    #include <GL/freeglut.h>
#elif __APPLE__
    #include <GLUT/glut.h>
#endif

// GLOBALS //
const int INIT_WINDOW_SIZE_X = 1280;
const int INIT_WINDOW_SIZE_Y = 720;
const int INIT_WINDOW_POS_X = -1;
const int INIT_WINDOW_POS_Y = -1;
const char * WINDOW_TITLE = "ICT289 Game";

// Predeclare functions
void DisplayCallback();

void InitializeGLUT(int * argc, char ** argv)
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH); // Initialize display modes, with RGBA, double buffering, and a depth buffer.
    glutInitWindowPosition(INIT_WINDOW_POS_X, INIT_WINDOW_POS_Y);
    glutInitWindowSize(INIT_WINDOW_SIZE_X, INIT_WINDOW_SIZE_Y);
    glutCreateWindow(WINDOW_TITLE);
    glutDisplayFunc(DisplayCallback);
    glClearColor(0.3922f, 0.5843f, 0.9294f, 1.0f);
}

void DisplayCallback()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
        glColor3f(0.4039f, 0.7373f, 0.6314f);
        glVertex2f(0.0f, 0.5f);
        glColor3f(0.5882f, 0.1294f, 0.2118f);
        glVertex2f(0.5f, -0.5f);
        glColor3f(0.2235f, 0.302f, 0.5176f);
        glVertex2f(-0.5f, -0.5f);
    glEnd();

    glutSwapBuffers();
}

int main(int argc, char ** argv)
{
    InitializeGLUT(&argc, argv);

    glutMainLoop();

    return 0;
}
