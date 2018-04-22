#ifndef TEXTURELOADING_H
#define TEXTURELOADING_H

#include <stdio.h>
#ifdef _WIN32
    #include <GL/freeglut.h>
#elif __APPLE__
    #include <GLUT/glut.h>
#endif
#include "Structs.h"

extern struct Texture LoadTexture(const char * filepath, int width, int height, int byteSize);

#endif // TEXTURELOADING_H
