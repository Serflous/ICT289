#include <stdio.h>
#include <stdlib.h>

#include "Constants.h"
#include "Display.h"
#include "Input.h"
#include "ConsoleIO.h"

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

void normalKeysCallback (unsigned char key, int x, int y);
void specialKeysCallback (int key, int x, int y);
void initialiseGameState();

int main(int argc, char ** argv)
{
    initialiseGameState();
    userPreferencesAndInstructions(&game.level);

    InitializeGLUT(&argc, argv);

    //-- Initialise input callbacks

    //glutSpecialFunc(specialKeysCallback);
    //glutKeyboardFunc(normalKeysCallback);
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
}

//-- Input functions ----------

void normalKeysCallback (unsigned char key, int x, int y) {

    //-- A and S keys are used to rotate the camera and Escape is used to quit

    switch (key) {

    case 'a':
    case 'A':
        break;

    case 'w':
    case 'W':
        barPercentage += BAR_SPEED;
        if(barPercentage > 1)
            barPercentage = 1;
        break;

    case 's':
    case 'S':
        barPercentage -= BAR_SPEED;
        if(barPercentage < 0)
            barPercentage = 0;
        break;

    case ESCAPE_KEY:
        exit (0);
        break;
    }
}

void specialKeysCallback (int key, int x, int y) {

    //-- Cursor keys are used for aiming and hitting the ball

    switch (key) {

    case GLUT_KEY_UP:

        break;

    case GLUT_KEY_DOWN:

        break;

    case GLUT_KEY_LEFT:
        break;

    case GLUT_KEY_RIGHT:
        break;
    }
}
