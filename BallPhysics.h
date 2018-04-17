#ifndef BALLPHYSICS_H_INCLUDED
#define BALLPHYSICS_H_INCLUDED

#include <GL/glut.h>
#include "Bool.h"
#include "Structs.h"

#define STOPPED_THRESHOLD 0.002

void Calculate2DVector (struct MovementVector3D *vector, float angle, float magnitude);
void ApplyMovement (struct Point3D *location, struct MovementVector3D movement);
bool ApplyFriction (struct MovementVector3D *movement, GLfloat percentageReduction);
bool ApplyImpact (struct MovementVector3D *movement, struct Vector3D obstacleFace, GLfloat coefficienOfRestitution);

#endif // BALLPHYSICS_H_INCLUDED
