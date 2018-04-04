#ifndef BALLPHYSICS_H_INCLUDED
#define BALLPHYSICS_H_INCLUDED

#include <GL/glut.h>
#include "Bool.h"

#define STOPPED_THRESHOLD 0.002

struct Point {
    GLfloat x, y, z;
};

struct Vector {
	GLfloat x, y, z;
};

struct MovementVector {
	GLfloat x, y, z, magnitude;
};

void Calculate2DVector (struct MovementVector *vector, float angle, float magnitude);
void ApplyMovement (struct Point *location, struct MovementVector movement);
bool ApplyFriction (struct MovementVector *movement, GLfloat percentageReduction);
bool ApplyImpact (struct MovementVector *movement, struct Vector obstacleFace, GLfloat coefficienOfRestitution);

#endif // BALLPHYSICS_H_INCLUDED
