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
