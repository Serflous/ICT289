#ifndef DISPLAY_H
#define DISPLAY_H
// Cross platform freeglut compile
#ifdef _WIN32
    #include <GL/freeglut.h>
#elif __APPLE__
    #include <GLUT/glut.h>
#endif

#include "Structs.h"
#include "TextureLoading.h"
#include "UI.h"

extern const int INIT_WINDOW_SIZE_X;
extern const int INIT_WINDOW_SIZE_Y;
extern const int INIT_WINDOW_POS_X;
extern const int INIT_WINDOW_POS_Y;
extern const char * WINDOW_TITLE;
extern const int PERSPECTIVE_FOV;
extern const float PERSPECTIVE_NEAR;
extern const float PERSPECTIVE_FAR;

void InitializeGLUT(int * argc, char ** argv);
void DisplayCallback();
void ReshapeCallback(int x, int y);

#endif // DISPLAY_H
