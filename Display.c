#include "Display.h"

const int INIT_WINDOW_SIZE_X = 1280;
const int INIT_WINDOW_SIZE_Y = 720;
const int INIT_WINDOW_POS_X = -1;
const int INIT_WINDOW_POS_Y = -1;
const char * WINDOW_TITLE = "ICT289 Game";
const int PERSPECTIVE_FOV = 45;
const float PERSPECTIVE_NEAR = 0.1f;
const float PERSPECTIVE_FAR = 1000.0f;

struct Texture balloonTex;

void InitializeGLUT(int * argc, char ** argv)
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH); // Initialize display modes, with RGBA, double buffering, and a depth buffer.
    glutInitWindowPosition(INIT_WINDOW_POS_X, INIT_WINDOW_POS_Y);
    glutInitWindowSize(INIT_WINDOW_SIZE_X, INIT_WINDOW_SIZE_Y);
    glutCreateWindow(WINDOW_TITLE);
    glutDisplayFunc(DisplayCallback);
    glutIdleFunc(DisplayCallback);
    glutReshapeFunc(ReshapeCallback);
    glClearColor(0.3922f, 0.5843f, 0.9294f, 1.0f);
    //glClearColor(0, 0, 0, 1.0f);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //-- Backface culling

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

    balloonTex = LoadTexture("res/balloon.raw", 512, 512, 4);
    InitializeUI();
}

void DisplayCallback()
{
    Update();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw 3D
    /*glBindTexture(GL_TEXTURE_2D, balloonTex.texId);
    glBegin(GL_TRIANGLES);
        glTexCoord2f(0, 0);
        glVertex3f(-0.5f, 0.5f, -5);
        glTexCoord2f(0, 1);
        glVertex3f(-0.5f, -0.5f, -5);
        glTexCoord2f(1, 1);
        glVertex3f(0.5f, -0.5f, -5);

        glTexCoord2f(0, 0);
        glVertex3f(-0.5f, 0.5f, -5);
        glTexCoord2f(1, 1);
        glVertex3f(0.5f, -0.5f, -5);
        glTexCoord2f(1, 0);
        glVertex3f(0.5f, 0.5f, -5);
    glEnd();*/

    // Draw 2D / UI
    DrawUI();
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

void Update()
{
    //printf("Update\n");
    if(IsKeyDown(ESCAPE_KEY, FALSE))
    {
        exit(0);
    }
    UpdateUI();
}
