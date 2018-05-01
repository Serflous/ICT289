#include <stdio.h>
#include <stdlib.h>

#include "Constants.h"
#include "Display.h"
#include "Input.h"

void normalKeysCallback (unsigned char key, int x, int y);
void specialKeysCallback (int key, int x, int y);

int main(int argc, char ** argv)
{
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
