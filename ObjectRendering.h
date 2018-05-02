#ifndef OBJECTRENDERING_H_INCLUDED
#define OBJECTRENDERING_H_INCLUDED

#include <GL/glut.h>
#include "Constants.h"
#include "Structs.h"

void drawDisc (float radius, int detailLevel);
void drawGround (struct Point3D position);
void drawBall (struct Point3D position, struct Colour colour);
void drawArrow (struct Point3D, float angle, struct Colour colour);
void drawCourse (struct Point3D position);

#endif
