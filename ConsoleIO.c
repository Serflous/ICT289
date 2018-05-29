#include "ConsoleIO.h"
#include <stdlib.h>
#include <stdio.h>

//-- Text/console functions -------------------

//-- Clears the screen. Windows only.

void clear(){
    system("cls");
}

//-- Reads a number between 1 and 3 from the user.

int getMenuChoice () {

    char input;
    do {
        printf ("\n Please select 1-3: ");
        input = getchar();

        if (input != '\n')          // Pick up the enter key press, if it hasn't already
            getchar();

    } while (input != '1' && input != '2' && input != '3');

    return (int)(input - '0');        // Apparently this works even with unicode
}

//-- Display information to the user about the game and get their preferences for surface materials.

void userPreferencesAndInstructions (struct Level *level) {
    clear();

    //-- Playing surface

    printf ("\n Minigolf\n ========\n\n");
    printf (" What kind of surface do you want to play on?\n");
    printf ("  1. Grass (normal)\n");
    printf ("  2. Ice (slippery)\n");
    printf ("  3. Dirt (lots of drag)\n");

    int surfaceChoice = getMenuChoice();

    //-- Wall construction

    printf ("\n What kind of walls do you want?\n");
    printf ("  1. Wood (normal)\n");
    printf ("  2. Rubber (bouncy)\n");
    printf ("  3. Cloth (absorbing)\n");

    int wallChoice = getMenuChoice();

    //-- Instructions

    clear();
    printf ("\n Minigolf\n ========\n\n");
    printf (" - Press A or S to rotate the camera around the course.\n");
    printf (" - Press the left or right arrow keys to set the direction to hit the ball.\n");
    printf (" - Hold down space to build power and release it to hit the ball.\n");
    printf (" - Press escape to quit.\n");

    printf ("\n Press enter to start.");
    getchar();

    //-- Update the level according to the user's choices. First, the surface

    switch (surfaceChoice) {
        case 1: // Set surface texture here
                level->rollingResistance = 5.0;
                break;
        case 2: // Set surface texture here
                level->rollingResistance = 2.0;
                break;
        case 3: // Set surface texture here
                level->rollingResistance = 10.0;
                break;
    }

    //-- ... then the wall

    switch (wallChoice) {
        case 1: // Set wall textures here
                level->coefficientOfRestitution = 0.67;
                break;
        case 2: // Set wall textures here
                level->coefficientOfRestitution = 0.9;
                break;
        case 3: // Set wall textures here
                level->coefficientOfRestitution = 0.3;
                break;
    }
}

void loadSelectedTextures(struct Level * level)
{
    if(level->rollingResistance == 5.0f)
        level->texFloor = LoadTexture("res/grass.raw", 512, 512, 4);
    else if(level->rollingResistance == 2.0f)
        level->texFloor = LoadTexture("res/ice.raw", 512, 512, 4);
    else if(level->rollingResistance == 10.0f)
        level->texFloor = LoadTexture("res/dirt.raw", 512, 512, 4);

    if(level->coefficientOfRestitution == 0.67f)
    {
        level->texWallInner = LoadTexture("res/wood-dark.raw", 512, 512, 4);
        level->texWallOuter = LoadTexture("res/wood-light.raw", 512, 512, 4);
    }
    else if(level->coefficientOfRestitution == 0.9f)
    {
        level->texWallInner = LoadTexture("res/rubber-dark.raw", 512, 512, 4);
        level->texWallOuter = LoadTexture("res/rubber-light.raw", 512, 512, 4);
    }
    else if(level->coefficientOfRestitution == 0.3f)
    {
        level->texWallInner = LoadTexture("res/cloth-dark.raw", 512, 512, 4);
        level->texWallOuter = LoadTexture("res/cloth-light.raw", 512, 512, 4);
    }
}
