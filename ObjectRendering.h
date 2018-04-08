#ifndef OBJECTRENDERING_H_INCLUDED
#define OBJECTRENDERING_H_INCLUDED

#include <GL/glut.h>
#include "Bool.h"
#include "Constants.h"
#include "Structs.h"

void drawBall (struct Point3D position, struct Colour colour);
void drawArrow (struct Point3D, float angle, struct Colour colour);
void drawCourse (struct Point3D position);

#endif
