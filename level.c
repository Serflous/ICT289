
#include "level.h"
#include "ObjectRendering.h"
#include "Constants.h"

//-- The following creates a hard coded level for testing. Loading a level from a file
//-- was postponed due to personnel constraints.

static struct Point3D hardcodedVertices[] = {
    {10.0, 0.0, 10.0},      // 0
    {110.0, 0.0, 10.0},     // 1
    {110.0, 0.0, 170.0},    // 2
    {10.0, 0.0, 170.0},     // 3
    {40.0, 0.0, 170.0},     // 4
    {80.0, 0.0, 170.0},     // 5
    {80.0, 0.0, 220.0},     // 6
    {40.0, 0.0, 220.0},     // 7
    {10.0, 0.0, 220.0},     // 8
    {310.0, 0.0, 220.0},    // 9
    {310.0, 0.0, 320.0},    // 10
    {10.0, 0.0, 320.0},     // 11
    {0.0, 5.0, 0.0},        // 12
    {120.0, 5.0, 0.0},      // 13
    {110.0, 5.0, 10.0},     // 14
    {10.0, 5.0, 10.0},      // 15
    {10.0, 5.0, 170.0},     // 16
    {0.0, 5.0, 180.0},      // 17
    {110.0, 5.0, 170.0},    // 18
    {120.0, 5.0, 180.0},    // 19
    {30.0, 5.0, 180.0},     // 20
    {40.0, 5.0, 170.0},     // 21
    {90.0, 5.0, 180.0},     // 22
    {80.0, 5.0, 170.0},     // 23
    {40.0, 5.0, 220.0},     // 24
    {30.0, 5.0, 210.0},     // 25
    {80.0, 5.0, 220.0},     // 26
    {90.0, 5.0, 210.0},     // 27
    {0.0, 5.0, 210.0},      // 28
    {10.0, 5.0, 220.0},     // 29
    {320.0, 5.0, 210.0},    // 30
    {310.0, 5.0, 220.0},    // 31
    {10.0, 5.0, 320.0},     // 32
    {0.0, 5.0, 330.0},      // 33
    {310.0, 5.0, 320.0},    // 34
    {320.0, 5.0, 330.0},    // 35
    {0.0, 0.0, 0.0},        // 36
    {120.0, 0.0, 0.0},      // 37
    {0.0, 0.0, 180.0},      // 38
    {120.0, 0.0, 180.0},    // 39
    {30.0, 0.0, 180.0},     // 40
    {90.0, 0.0, 180.0},     // 41
    {30.0, 0.0, 210.0},     // 42
    {90.0, 0.0, 210.0},     // 43
    {0.0, 0.0, 210.0},      // 44
    {320.0, 0.0, 210.0},    // 45
    {0.0, 0.0, 330.0},      // 46
    {320.0, 0.0, 330.0}     // 47
};

static struct IndexedQuad hardcodedGreenPolys[] = {
    {3,2,1,0},
    {7,6,5,4},
    {11,10,9,8}
};

static struct IndexedQuad hardcodedInnerWallPolys[] = {
    {0, 1, 14, 15},
    {15,16,3,0},
    {1, 2, 18, 14},
    {5,23,18,2},
    {3, 16, 21, 4},
    {21,24,7,4},
    {5, 6, 26, 23},
    {24,29,8,7},
    {9,31,26,6},
    {9, 10, 34, 31},
    {8, 29, 32, 11},
    {11, 32, 34, 10}
};

static struct IndexedQuad hardcodedOuterWallPolys[] = {
    {37,36,12,13},
    {38,17,12,36},
    {19,39,37,13},
    {17,38,40,20},
    {22,41,39,19},
    {40,42,25,20},
    {41,22,27,43},
    {28,25,42,44},
    {28,44,46,33},
    {33,46,47,35},
    {35,47,45,30},
    {43,26,30,45}
};

static struct IndexedQuad hardcodedTopWallPolys[] = {
    {15,14,13,12},
    {17,16,15,12},
    {13, 14, 18, 19},
    {16, 17, 20, 21},
    {23,22,19,18},
    {25,24,21,20},
    {22, 23, 26, 27},
    {24, 25, 28, 29},
    {31,30,27,26},
    {33,32,29,28},
    {30, 31, 34, 35},
    {32, 33, 35, 34}
};

//-- Creates a hard coded test level and stores it in the provided level structure.

void hardcodedLevel (struct Level *level) {

    //-- Par for the course. Currently a guess.

    level->par = 3;

    //-- Default values for the physical attributes

    level->rollingResistance = 5.0;
    level->coefficientOfRestitution = 0.67;

    //-- Position of the hole relative to the course

    level->holePosition.x = 280;
    level->holePosition.y = 0.2;    // Has to be slightly above the surface so as not to appear glitchy
    level->holePosition.z = 270;

    //-- Position of the camera relative to the world, plus it's initial angle

    level->cameraPosition.x = 0;
    level->cameraPosition.y = 500;
    level->cameraPosition.z = 500;
    level->cameraStartingAngle = 45.0;

    //-- Ball starting position relative to the course, plus the angle it's "facing".

    level->ballStartingPosition.x = 60;
    level->ballStartingPosition.y = BALL_RADIUS_PX;
    level->ballStartingPosition.z = 30;
    level->ballStartingAngle = 0.0;

    //-- Position of the level model relative to the world

    level->position.x = -155;
    level->position.y = 0;
    level->position.z = -165;

    //-- Load up the vertices

    level->numberOfVertices = 48;
    level->vertices = calloc(level->numberOfVertices, sizeof(struct Point3D));

    for (int i = 0; i < level->numberOfVertices; i++) {
        level->vertices[i].x = hardcodedVertices[i].x;
        level->vertices[i].y = hardcodedVertices[i].y;
        level->vertices[i].z = hardcodedVertices[i].z;
    }

    //-- Load the polygons for the course green

    level->numberOfGreenPolys = 3;
    level->greenPolys = calloc(level->numberOfGreenPolys, sizeof(struct IndexedQuad));

    for (int i = 0; i < level->numberOfGreenPolys; i++) {
        for (int j = 0; j < 4; j++) {
            level->greenPolys[i].vertexArrayIndices[j] = hardcodedGreenPolys[i].vertexArrayIndices[j];
        }
    }

    //-- Load the polygons for the inner walls. Note that these are important for collision
    //-- detection

    level->numberOfInnerWallPolys = 12;
    level->innerWallPolys = calloc(level->numberOfInnerWallPolys, sizeof(struct IndexedQuad));

    for (int i = 0; i < level->numberOfInnerWallPolys; i++) {
        for (int j = 0; j < 4; j++) {
            level->innerWallPolys[i].vertexArrayIndices[j] = hardcodedInnerWallPolys[i].vertexArrayIndices[j];
        }
    }

    //-- Load the polygons for the outer walls.

    level->numberOfOuterWallPolys = 12;
    level->outerWallPolys = calloc(level->numberOfOuterWallPolys, sizeof(struct IndexedQuad));

    for (int i = 0; i < level->numberOfOuterWallPolys; i++) {
        for (int j = 0; j < 4; j++) {
            level->outerWallPolys[i].vertexArrayIndices[j] = hardcodedOuterWallPolys[i].vertexArrayIndices[j];
        }
    }

    //-- Load the polygons for the top walls.

    level->numberOfTopWallPolys = 12;
    level->topWallPolys = calloc(level->numberOfTopWallPolys, sizeof(struct IndexedQuad));

    for (int i = 0; i < level->numberOfTopWallPolys; i++) {
        for (int j = 0; j < 4; j++) {
            level->topWallPolys[i].vertexArrayIndices[j] = hardcodedTopWallPolys[i].vertexArrayIndices[j];
        }
    }
}

//-- A helper function that draws a four sided polygon from four indices into an array of vertices.

void drawQuadPoly (struct Point3D *vertices, struct IndexedQuad poly) {

    glBegin(GL_POLYGON);
        for (int i = 0; i < 4; i++) {
            glVertex3f(vertices[poly.vertexArrayIndices[i]].x, vertices[poly.vertexArrayIndices[i]].y, vertices[poly.vertexArrayIndices[i]].z);
        }
    glEnd();
}

//-- Draw a level - green, walls and hole

void drawLevel (struct Level *level) {

    glPushMatrix();
    glTranslatef(level->position.x, level->position.y, level->position.z);

    //-- Draw the green

    glColor3f(0, 0.7, 0);

    for (int i = 0; i < level->numberOfGreenPolys; i++) {
        drawQuadPoly (level->vertices, level->greenPolys[i]);
    }

    //-- Draw the inner walls

    glColor3f(0.3921, 0.2196, 0.0470);

    for (int i = 0; i < level->numberOfInnerWallPolys; i++) {
        drawQuadPoly (level->vertices, level->innerWallPolys[i]);
    }

    //-- Draw the outer walls

    glColor3f(0.3921, 0.2196, 0.0470);

    for (int i = 0; i < level->numberOfOuterWallPolys; i++) {
        drawQuadPoly (level->vertices, level->outerWallPolys[i]);
    }

    //-- Draw the top walls

    glColor3f(0.490, 0.3137, 0.1411);

    for (int i = 0; i < level->numberOfTopWallPolys; i++) {
        drawQuadPoly (level->vertices, level->topWallPolys[i]);
    }

    //-- Draw the hole

    glColor3f(0, 0, 0);
    glTranslatef(level->holePosition.x, level->holePosition.y, level->holePosition.z);
    drawDisc(HOLE_RADIUS_PX, HOLE_DETAIL_LEVEL);

    glPopMatrix();
}

//-- Free up all the memory used by the Level

void freeLevel (struct Level *level) {
    free (level->vertices);
    free (level->greenPolys);
    free (level->innerWallPolys);
    free (level->outerWallPolys);
    free (level->topWallPolys);
}
