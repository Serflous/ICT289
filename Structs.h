#ifndef STRUCTS_H
#define STRUCTS_H

struct Point3D
{
    float x, y, z;
};

struct UV
{
    float u, v;
};

struct Texture
{
    GLuint texId;
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

struct Level
{
    struct Entity * entities;
    struct Camera camera;
};

#endif // STRUCTS_H
