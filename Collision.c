#include "Collision.h"
#include "Structs.h"

bool isColliding(struct Ball ball, struct WallCollsion * walls, int numWalls, struct Point3D levelPosition, struct Vector3D * facing)
{
    struct Point3D ballAbsPosition = ball.position;
    // Loop every wall
    for(int i = 0; i < numWalls; i++)
    {
        struct Point2D closestPoint;
        float x1 = walls[i].x1 + levelPosition.x;
        float x2 = walls[i].x2 + levelPosition.x;
        float z1 = walls[i].z1 + levelPosition.z;
        float z2 = walls[i].z2 + levelPosition.z;
        FindClosestPointInLine(x1, z1, x2, z2, ballAbsPosition, &closestPoint);

        // Find distance between closest point and ball
        double distance = DistanceBetweenBallAndWall(ballAbsPosition, closestPoint);

        // Is distance <= radius
        if(distance <= BALL_RADIUS_PX)
        {
            // Colliding.
            facing->x = walls[i].face.x;
            facing->y = walls[i].face.y;
            facing->z = walls[i].face.z;
            return TRUE;
        }
    }
    return FALSE;
}

void FindClosestPointInLine(float x1, float z1, float x2, float z2, struct Point3D point, struct Point2D * closestPoint)
{
    float lineOneFromPointX = point.x - x1;
    float lineOneFromPointZ = point.z - z1;
    float lineOneFromLineTwoX = x2 - x1;
    float lineOneFromLineTwoZ = z2 - z1;
    float mag = lineOneFromLineTwoX * lineOneFromLineTwoX + lineOneFromLineTwoZ * lineOneFromLineTwoZ;
    float dot = lineOneFromLineTwoX * lineOneFromPointX + lineOneFromLineTwoZ * lineOneFromPointZ;
    float t = dot / mag;
    if(t < 0)
    {
        closestPoint->x = x1;
        closestPoint->y = z1;
    }
    else if(t > 1)
    {
        closestPoint->x = x2;
        closestPoint->y = z2;
    }
    else
    {
        closestPoint->x = x1 + lineOneFromLineTwoX * t;
        closestPoint->y = x2 + lineOneFromLineTwoZ * t;
    }
}

double DistanceBetweenBallAndWall(struct Point3D ball, struct Point2D wall)
{
    float dx = wall.x - ball.x;
    float dz = wall.y - ball.z;
    return sqrt(dx*dx + dz*dz);
}
