#include "Collision.h"
#include "Structs.h"

bool isColliding(struct Ball ball, struct WallCollsion * walls, int numWalls, struct Point3D levelPosition, struct Vector3D * facing)
{
    struct Point3D ballAbsPosition = ball.position;
    // Loop every wall
    for(int i = 0; i < numWalls; i++)
    {
        struct Point2D closestPoint;
        struct WallCollsion wall = walls[i];
        float x1 = wall.x1 + levelPosition.x;
        float x2 = wall.x2 + levelPosition.x;
        float z1 = wall.z1 + levelPosition.z;
        float z2 = wall.z2 + levelPosition.z;
        FindClosestPointInLine(x1, z1, x2, z2, ballAbsPosition, &closestPoint);

        // Find distance between closest point and ball
        double distance = DistanceBetweenBallAndWall(ballAbsPosition, closestPoint);

        // Is distance <= radius
        if(distance <= BALL_RADIUS_PX)
        {
            // Colliding.
            facing->x = wall.face.x;
            facing->y = wall.face.y;
            facing->z = wall.face.z;
            return TRUE;
        }
    }
    return FALSE;
}

void FindClosestPointInLine(float x1, float z1, float x2, float z2, struct Point3D point, struct Point2D * closestPoint)
{
    float dx = x2 - x1;
    float dz = z2 - z1;
    float distance = ((point.x - x1) * dx + (point.z - z1) * dz) / (dx * dx + dz * dz);
    if(distance < 0)
    {
        closestPoint->x = x1;
        closestPoint->y = z1;
    }
    else if(distance > 1)
    {
        closestPoint->x = x2;
        closestPoint->y = z2;
    }
    else
    {
        closestPoint->x = x1 + distance * dx;
        closestPoint->y = z1 + distance * dz;
    }
}

double DistanceBetweenBallAndWall(struct Point3D ball, struct Point2D wall)
{
    float dx = wall.x - ball.x;
    float dz = wall.y - ball.z;
    return sqrt(dx*dx + dz*dz);
}
