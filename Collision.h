#ifndef COLLISION_H
#define COLLISION_H
#include <math.h>
#include "Bool.h"
#include "Structs.h"
#include "Constants.h"

bool isColliding(struct Ball ball, struct WallCollsion * walls, int numWalls, struct Point3D levelPosition,  struct Vector3D * facing);
void FindClosestPointInLine(float x1, float z1, float x2, float z2, struct Point3D point, struct Point2D * closestPoint);
double DistanceBetweenBallAndWall(struct Point3D ball, struct Point2D wall);

#endif // COLLISION_H
