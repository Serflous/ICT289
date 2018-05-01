#ifndef STRUCTS_H
#define STRUCTS_H

#include "Bool.h"

// Cross platform freeglut compile
#ifdef _WIN32
    #include <GL/freeglut.h>
#elif __APPLE__
    #include <GLUT/glut.h>
#endif

struct Colour {
    float red, green, blue;
};

struct Point3D
{
    float x, y, z;
};

struct Vector3D {
	GLfloat x, y, z;
};

struct MovementVector3D {
	GLfloat x, y, z, magnitude;
};

struct UV
{
    float u, v;
};

struct Texture
{
    GLuint texId;
    int texWidth;
    int texHeight;
};

struct Model
{
    struct Point3D * verts;
    struct UV * uvs;
    struct Point3D * norms;
};

struct Entity
{
    struct Model model;
    struct Point3D position;
    struct Point3D scale;
    struct Point3D rotation;
};

struct Camera
{
    struct Point3D position;
    struct Point3D forward;
    struct Point3D up;
};

struct Ball {

    struct Point3D position;
    struct MovementVector3D motion;
    bool hasStopped;
};

#endif // STRUCTS_H
