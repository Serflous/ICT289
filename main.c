#include <stdio.h>
#include <stdlib.h>

#include "Display.h"

int main(int argc, char ** argv)
{
    InitializeGLUT(&argc, argv);

    glutMainLoop();

    return 0;
}
