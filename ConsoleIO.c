#include "ConsoleIO.h"
#include <stdlib.h>
#include <stdio.h>

//-- Text/console functions ----------

void clear(){
    system("cls");
}

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

void userPreferencesAndInstructions (struct Level *level) {
    clear();

    printf ("\n Minigolf\n ========\n\n");
    printf (" What kind of surface do you want to play on?\n");
    printf ("  1. Grass (normal)\n");
    printf ("  2. Ice (slippery)\n");
    printf ("  3. Dirt (lots of drag)\n");

    int surfaceChoice = getMenuChoice();

    printf ("\n What kind of walls do you want?\n");
    printf ("  1. Wood (normal)\n");
    printf ("  2. Rubber (bouncy)\n");
    printf ("  3. Cloth (absorbing)\n");

    int wallChoice = getMenuChoice();

    clear();
    printf ("\n Minigolf\n ========\n\n");
    printf (" - Press A or S to rotate the camera around the course.\n");
    printf (" - Press the left or right arrow keys to set the direction to hit the ball.\n");
    printf (" - Hold down space to build power and release it to hit the ball.\n");
    printf (" - Press escape to quit.\n");

    printf ("\n Press enter to start.");
    getchar();

    //-- Update the level according to the user's choices

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
