#include <math.h>
#include "BallPhysics.h"

//-- Calculate2DVector
//-- Takes:       A reference to a vector of movement, an angle in degrees and a magnitude.
//-- Process:     The function calculates a vector that corresponds to the provided angle and stores it
//                in the movement vector. It also stores the magnitude of the vector, which is basically the
//                speed at which the ball will travel.
//-- Returns:     Nothing.
//-- Limitations: Currently, the function only supports 2D vectors on an X/Z plane.

void Calculate2DVector (struct MovementVector3D *vector, float angle, float magnitude)
{
    //-- Convert the angle to radians

    float radians = angle * M_PI / 180;

    //-- Calculate the vector

    vector->x = sin(radians);
    vector->z = cos(radians);
    vector->y = 0;

    //-- Store the magnitude

    vector->magnitude = magnitude;
}

//-- ApplyMovement
//-- Takes:       A reference to a point corresponding to the location of the ball and a movement vector to apply.
//-- Process:     It adds the vector of movement to the position of the ball. Effectively, it moves the ball one step.
//-- Returns:     Nothing.
//-- Limitations: Currently, the function only supports 2D vectors on an X/Z plane. It does not support slopes or
//                gravity.

void ApplyMovement (struct Point3D *location, struct MovementVector3D movement)
{
    //-- For each coordinate of the location, add the relevant vector value multiplied by the magnitude

    location->x += movement.x * movement.magnitude;
    location->y += movement.y * movement.magnitude;
    location->z += movement.z * movement.magnitude;
}

//-- ApplyFriction
//-- Takes:       A reference to a vector of movement and the rolling resistance of the surface.
//-- Process:     The function drains the vector's magnitude by the rolling resistance. If the magnitude gets
//                close to zero (within 0.002) it will be set to zero.
//-- Returns:     Whether the ball is now stopped. That is, magnitude is zero.
//-- Limitations: None.
//-- Notes:       The correct rolling resistance of baize is 0.005 - 0.015
//--              (http://billiards.colostate.edu/threads/physics.html)

bool ApplyFriction (struct MovementVector3D *movement, GLfloat rollingResistance) {

    //-- If we're not moving, leave

    if (movement->magnitude == 0) {
        return TRUE;
    }

    //-- Drop the magnitude of the movement vector by the required amount

    movement->magnitude -= rollingResistance;

    //-- If we're moving so slow that it's basically stopped, zero the movement vector magnitude.

    if (movement->magnitude < STOPPED_THRESHOLD) {
        movement->magnitude = 0;
        return TRUE;
    }

    return FALSE;
}

//-- ApplyImpact
//-- Takes:       A reference to a vector of movement for the ball, a vector of the wall it has hit and the coefficient
//                of restitution (how much speed is lost in the collision).
//-- Process:     The function reflects the ball depending on the vector of movement and the angle of the wall. It then
//--              drains the specified amount of speed from the ball.
//-- Returns:     Whether the ball is now stopped. That is, magnitude is zero.
//-- Limitations: Currently, the function only supports walls which are straight up and down or straight left
//                and right.
//-- Notes:       The correct coefficient of restitution for a golf ball on wood is approx 0.67
//--              (http://iopscience.iop.org/article/10.1088/1757-899X/36/1/012038/meta)

bool ApplyImpact (struct MovementVector3D *movement, struct Vector3D obstacleFace, GLfloat coefficientOfRestitution)
{
    //---------- First, reflect the vector

    //-- Check if we are reflecting off of a line parallel with the Z-axis

    if (obstacleFace.x == 0 && (obstacleFace.z == 1 || obstacleFace.z == -1)) {

        //-- If so, reverse the x movement

        movement->x *= -1;
    }

    //-- Check if we are reflecting off of a line parallel with the X-axis

    else if (obstacleFace.z == 0 && (obstacleFace.x == 1 || obstacleFace.x == -1)) {

        //-- If so, reverse the z movement

        movement->z *= -1;
    }

    //---------- Then, drop the speed of the ball as the impact drains momentum

    //-- If we're not moving, leave. Given we are currently impacting a wall, this shouldn't
    //-- be possible but better safe than sorry.

    if (movement->magnitude == 0) {
        return TRUE;
    }

    //-- Drop the magnitude of the movement vector by the required amount

    movement->magnitude *= coefficientOfRestitution;

    //-- If we're moving so slow that it's basically stopped, zero the movement vector magnitude.

    if (movement->magnitude < STOPPED_THRESHOLD) {
        movement->magnitude = 0;
        return TRUE;
    }

    return FALSE;
}
