
#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#include <math.h>
#include "Structs.h"
#include "TextureLoading.h"

struct IndexedQuad {
    int vertexArrayIndices[4];
};

struct Level
{
    int par;

    struct Point3D position;
    struct Point3D ballStartingPosition, holePosition;     // Both relative to the course
    struct Point3D cameraPosition;                         // Relative to world

    float cameraStartingAngle, ballStartingAngle;
    float rollingResistance, coefficientOfRestitution;
    struct Texture texFloor, texWall;

    int numberOfVertices;
    struct Point3D *vertices;

    int numberOfGreenPolys;
    struct IndexedQuad *greenPolys;

    int numberOfInnerWallPolys;
    struct IndexedQuad *innerWallPolys;

    int numberOfOuterWallPolys;
    struct IndexedQuad *outerWallPolys;

    int numberOfTopWallPolys;
    struct IndexedQuad *topWallPolys;

    struct WallCollsion *walls;
};

void hardcodedLevel (struct Level *level);
void drawLevel (struct Level *level);
void freeLevel (struct Level *level);

#endif // CONSTANTS_H_INCLUDED
