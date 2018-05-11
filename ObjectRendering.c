#include "ObjectRendering.h"
#include <math.h>

//-- Renders the ground - a circular, spotlight-like area around the course.

void drawGround (struct Point3D position) {
    glColor3f(0, 0.5, 0);

    glPushMatrix();
    glTranslatef(position.x, position.y, position.z);
    drawDisc(250, 100);
	glPopMatrix();
}

//-- Renders the ball, given it's position and colour

void drawBall (struct Point3D position, struct Colour colour) {

    //-- Set the colour

    glColor3f(colour.red, colour.green, colour.blue);

    //-- Render the ball at the correct position

    glPushMatrix();
    glTranslatef(position.x, position.y, position.z);
    glutSolidSphere(BALL_RADIUS_PX, BALL_DETAIL_LEVEL, BALL_DETAIL_LEVEL);

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
    glutSolidCone(1.5, 20, 10, 10);

    glPopMatrix();
}

//-- Draws the golf course hole relative to the course.

void drawHole (GLfloat x, GLfloat y, GLfloat z, GLfloat radius) {

    glColor3f(1, 0, 0);
    glPushMatrix();

    glTranslatef(x, y, z);
    drawDisc(radius, HOLE_DETAIL_LEVEL);

	glPopMatrix();
}

//-- Renders a disc. Used for the ground and hole.

void drawDisc (float radius, int detailLevel) {

    glBegin(GL_POLYGON);

    //-- Draw a disk by stepping around a circle and building a polygon in our wake

    for (int i = 360; i > 0; i -= (360 / detailLevel)) {
      float angleInRadians = i * (M_PI / 180.0);
      glVertex3f(cos(angleInRadians) * radius, 0, sin(angleInRadians) * radius);
    }

    glEnd();
}
