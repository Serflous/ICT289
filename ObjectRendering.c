#include "ObjectRendering.h"

//-- Renders the ball, given it's position and colour

void drawBall (struct Point3D position, struct Colour colour) {

    //-- Set the colour

    glColor3f(colour.red, colour.green, colour.blue);

    //-- Render the ball at the correct position

    glPushMatrix();
    glTranslatef(position.x, position.y, position.z);
    glutSolidSphere(BALL_SIZE_PX, BALL_DETAIL_LEVEL, BALL_DETAIL_LEVEL);
    glPopMatrix();
}

//-- Renders the ball's directional arrow (part of the UI), given a colour, angle and the
//-- position of the ball (around which it rotates).

void drawArrow (struct Point3D ballPosition, float angle, struct Colour colour) {

    //-- Set the colour

    glColor3f(colour.red, colour.green, colour.blue);

    glPushMatrix();

    glTranslatef(ballPosition.x, ballPosition.y, ballPosition.z);
    glRotatef(angle, 0, 1, 0);
    glTranslatef(0, 0, 5);
    glutSolidCone(0.8, 12, 10, 10);

    glPopMatrix();
}

//-- Draws the golf course hole relative to the course. It assumes the hole sits on the course
//-- surface (and therefore doesn't need a Y coordinate).

//-- However, the function also currently assumes the course is flat.

void drawHole (GLfloat x, GLfloat z, GLfloat radius) {

    glColor3f(0, 0, 0);
    glPushMatrix();

    //-- Note below: We need to add a tiny amount to the Y so the hole sits
    //-- on top of the course surface

    glTranslatef(coursePosition.x + x, coursePosition.y + 0.1, coursePosition.z + z);

    glBegin(GL_POLYGON);

    //-- Draw a disk by stepping around a circle and building a polygon in our wake

    for (int i = 360; i > 0; i -= (360 / HOLE_DETAIL_LEVEL)) {
      float angleInRadians = i * (M_PI / 180.0);
      glVertex3f(cos(angleInRadians) * radius, 0, sin(angleInRadians) * radius);
    }

    glEnd();

	glPopMatrix();
}

//-----------------------------------------------------------------------------------

//-- This point onwards are temporary functions that draw a hard coded golf course.
//-- The eventual aim was to load the course from a file but as we are one member down
//-- we elected to keep the hard coded version and forego the versatility of loading it.

//-- Hard coded vertices for the course

 struct Point3D vertices[] = {

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
    {320.0, 5.0, 330.0}     // 35
};

//-- Draws a four sided polygon. A helper function for rendering the course.

void drawSquarePoly (int v1, int v2, int v3, int v4) {

    //-- Note that the vertices are given in centimeters and must be multiplies by the pixels per centimeter.
    //-- We do this in code in case the pixels per centimeter change

    glBegin(GL_POLYGON);
        glVertex3f(vertices[v1].x * PIXELS_PER_CM, vertices[v1].y * PIXELS_PER_CM, vertices[v1].z * PIXELS_PER_CM);
        glVertex3f(vertices[v2].x * PIXELS_PER_CM, vertices[v2].y * PIXELS_PER_CM, vertices[v2].z * PIXELS_PER_CM);
        glVertex3f(vertices[v3].x * PIXELS_PER_CM, vertices[v3].y * PIXELS_PER_CM, vertices[v3].z * PIXELS_PER_CM);
        glVertex3f(vertices[v4].x * PIXELS_PER_CM, vertices[v4].y * PIXELS_PER_CM, vertices[v4].z * PIXELS_PER_CM);
    glEnd();
}

//-- Renders the golf course.

void drawCourse (struct Point3D position) {

    glPushMatrix();
    glTranslatef(position.x, position.y, position.z);

    //-- Draw the base of the course (the green)

    glColor3f(0, 1, 0);

    drawSquarePoly(3,2,1,0);
    drawSquarePoly(7,6,5,4);
    drawSquarePoly(11,10,9,8);

    //-- Draw the tops of the walls

    glColor3f(0.490, 0.3137, 0.1411);
    drawSquarePoly(15,14,13,12);
    drawSquarePoly(17,16,15,12);
    drawSquarePoly(13, 14, 18, 19);
    drawSquarePoly(16, 17, 20, 21);
    drawSquarePoly(23,22,19,18);
    drawSquarePoly(25,24,21,20);
    drawSquarePoly(22, 23, 26, 27);
    drawSquarePoly(24, 25, 28, 29);
    drawSquarePoly(31,30,27,26);
    drawSquarePoly(33,32,29,28);
    drawSquarePoly(30, 31, 34, 35);
    drawSquarePoly(32, 33, 35, 34);

    //-- Draw the sides of ,the walls

    glColor3f(0.3921, 0.2196, 0.0470);
    drawSquarePoly(0, 1, 14, 15);
    drawSquarePoly(15,16,3,0);
    drawSquarePoly(1, 2, 18, 14);
    drawSquarePoly(5,23,18,2);
    drawSquarePoly(3, 16, 21, 4);
    drawSquarePoly(21,24,7,4);
    drawSquarePoly(5, 6, 26, 23);
    drawSquarePoly(24,29,8,7);
    drawSquarePoly(9,31,26,6);
    drawSquarePoly(9, 10, 34, 31);
    drawSquarePoly(8, 29, 32, 11);
    drawSquarePoly(11, 32, 34, 10);

    glPopMatrix();
}
