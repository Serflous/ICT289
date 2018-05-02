#include <stdio.h>
#include <stdlib.h>

#include "Constants.h"
#include "Input.h"
#include "ConsoleIO.h"

void initialiseGameState();

void InitializeGLUT(int * argc, char ** argv);
void DisplayCallback();
void ReshapeCallback(int x, int y);
void Update();

struct GameState {

    struct Level   level;
    struct Camera  camera;
    struct Ball    ball;

    float   arrowAngle;
    float   power;
    int     powerDirection;
    int     ellapsedTime;
    int     numberOfStrokes;
    bool    gameOver;
};

//-- Global variables

struct GameState game;

int main(int argc, char ** argv)
{
    initialiseGameState();
   // userPreferencesAndInstructions(&game.level);

    InitializeGLUT(&argc, argv);

    //-- Initialise input callbacks
    InputInitialize();
    glutKeyboardFunc(NormalKeyDownCallback);
    glutKeyboardUpFunc(NormalKeyUpCallback);
    glutSpecialFunc(SpecialKeyDownCallback);
    glutSpecialUpFunc(SpecialKeyUpCallback);

    glutMainLoop();

    return 0;
}

void initialiseGameState() {
    hardcodedLevel(&game.level);
    game.arrowAngle = 0.0;
    game.power = 0.0;
    game.powerDirection = 1;
    game.ellapsedTime = 0;
    game.numberOfStrokes = 0;
    game.gameOver = FALSE;

    game.camera.position.x = 0;
    game.camera.position.y = 100;
    game.camera.position.z = 650;
    game.camera.up.x = 0;
    game.camera.up.y = 1;
    game.camera.up.z = 0;
    game.camera.forward.x = 0;
    game.camera.forward.y = -1;
    game.camera.forward.z = 0;
    game.camera.angle = 0;
}

//-- Glut ----------

void Update()
{
    glutTimerFunc(1000/TARGET_FPS, Update, 0);
    if(IsKeyDown(ESCAPE_KEY, FALSE))
    {
        exit(0);
    }
    UpdateUI();

    glutPostRedisplay();
}

void InitializeGLUT(int * argc, char ** argv)
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH); // Initialize display modes, with RGBA, double buffering, and a depth buffer.
    glutInitWindowPosition(INIT_WINDOW_POS_X, INIT_WINDOW_POS_Y);
    glutInitWindowSize(INIT_WINDOW_SIZE_X, INIT_WINDOW_SIZE_Y);
    glutCreateWindow(WINDOW_TITLE);
    glutDisplayFunc(DisplayCallback);
    glutReshapeFunc(ReshapeCallback);
    glClearColor(0, 0, 0, 1.0f);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //-- Backface culling

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

   // previousTime = glutGet(GLUT_ELAPSED_TIME);

   // balloonTex = LoadTexture("res/balloon.raw", 512, 512, 4);

   glutTimerFunc(1000/TARGET_FPS, Update, 0);
    InitializeUI();
}

void placeCamera () {

    gluLookAt(game.camera.position.x, game.camera.position.y, game.camera.position.z,
              game.camera.forward.x, game.camera.forward.y, game.camera.forward.z,
              game.camera.up.x, game.camera.up.y, game.camera.up.z);

    glRotatef(game.camera.angle, 0, 1, 0);
}

void drawGround (GLfloat radius) {


    glColor3f(0, 0.5, 0);
    glPushMatrix();

    //-- Note below: We need to add a tiny amount to the Y so the hole sits
    //-- on top of the course surface

    glTranslatef(0, game.level.position.y - 2, 0);

    glBegin(GL_POLYGON);

    //-- Draw a disk by stepping around a circle and building a polygon in our wake

    for (int i = 360; i > 0; i -= (360 / 100)) {
      float angleInRadians = i * (M_PI / 180.0);
      glVertex3f(cos(angleInRadians) * radius, 0, sin(angleInRadians) * radius);
    }

    glEnd();

	glPopMatrix();
}

void DisplayCallback()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //-- Place camera

    placeCamera();

    //-- Draw 3D

    drawGround(250);

    //-- Draw 2D / UI

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



