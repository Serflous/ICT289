#include <stdio.h>
#include <stdlib.h>

#include "Constants.h"
#include "Input.h"
#include "ConsoleIO.h"
#include "ObjectRendering.h"
#include "BallPhysics.h"
#include "UI.h"

void initialiseGameState();

void InitializeGLUT(int * argc, char ** argv);
void DisplayCallback();
void ReshapeCallback(int x, int y);
void Update();
void Quit();

struct GameState {

    struct Level   level;
    struct Camera  camera;
    struct Ball    ball;

    float   arrowAngle;
    float   power;
    int     powerDirection;
    int     ellapsedTime, previousTime;
    int     numberOfStrokes;
    bool    gameOver, ballInHole;
};

//-- Global variables

struct GameState game;
bool isSplashing;

int main(int argc, char ** argv)
{
    initialiseGameState();
    isSplashing = FALSE;

    //userPreferencesAndInstructions(&(game.level));
    InitializeGLUT(&argc, argv);

    //-- Initialise input callbacks
    InputInitialize();
    glutKeyboardFunc(NormalKeyDownCallback);
    glutKeyboardUpFunc(NormalKeyUpCallback);
    glutSpecialFunc(SpecialKeyDownCallback);
    glutSpecialUpFunc(SpecialKeyUpCallback);

    glutMainLoop();

    return 0;
}

void initialiseGameState() {
    hardcodedLevel(&(game.level));
    game.arrowAngle = 0.0;
    game.power = 1.0;
    game.powerDirection = 1;
    game.ellapsedTime = game.previousTime = 0;
    game.numberOfStrokes = 0;
    game.gameOver = FALSE;
    game.ballInHole = FALSE;

    game.ball.position.x = game.level.ballStartingPosition.x + game.level.position.x;
    game.ball.position.y = game.level.ballStartingPosition.y + game.level.position.y;
    game.ball.position.z = game.level.ballStartingPosition.z + game.level.position.z;
    game.ball.hasStopped = TRUE;

    game.camera.position.x = game.level.cameraPosition.x;
    game.camera.position.y = game.level.cameraPosition.y;
    game.camera.position.z = game.level.cameraPosition.z;

    game.camera.up.x = 0;
    game.camera.up.y = 1;
    game.camera.up.z = 0;
    game.camera.forward.x = 0;
    game.camera.forward.y = -1;
    game.camera.forward.z = 0;
    game.camera.angle = game.level.cameraStartingAngle;
}

bool ballHitsHole () {

    float holeX = game.level.holePosition.x + game.level.position.x;
    float holeZ = game.level.holePosition.z + game.level.position.z;

    float xDistance = game.ball.position.x - holeX;
    float zDistance = game.ball.position.z - holeZ;

    float totalDistance = sqrt((xDistance * xDistance) + (zDistance * zDistance));

    return (totalDistance <= HOLE_RADIUS_PX / 2);
}

//-- Glut ----------

void Update()
{
    static gameOverCountdown = 1000;

    glutTimerFunc(1000/TARGET_FPS, Update, 0);

    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    game.ellapsedTime = currentTime - game.previousTime;
    game.previousTime = currentTime;

    if (game.ballInHole) {
        gameOverCountdown -= game.ellapsedTime;

        if (gameOverCountdown <= 0) {

        }

        //return;
    }

    if(hasBeenHit == TRUE)
    {
        hasBeenHit = FALSE;
    //    struct MovementVector3D * movementVector;
        //Calculate2DVector(&game.ball.motion, game.arrowAngle, 1); //mag of 1 for testing
        Calculate2DVector(&game.ball.motion, game.arrowAngle, game.power * lastBarPercentage); // mag based on power
     //   game.ball.motion = *movementVector;
        game.ball.hasStopped = FALSE;
        game.numberOfStrokes++;
    }
    if(game.ball.hasStopped == FALSE)
    {
        ApplyMovement(&game.ball.position, game.ball.motion);

        if (ballHitsHole()) {
            game.ballInHole = TRUE;
            isSplashing = TRUE;
            glutTimerFunc(5000, Quit, 0);
        }

        //-- Friction

        // This requires some explanation. Acceleration is the change in speed divided by time and
        // speed is change in distance divided by time. As such, acceleration is the change in
        // distance divided by time, divided by time.

        // So, to adjust the friction deceleration to the correct value for the current frame rate,
        // we need to divide by the FPS twice - which is the same as dividing by the frame rate
        // squared.

        float fps = 1000.0 / game.ellapsedTime;
        game.ball.hasStopped = ApplyFriction(&game.ball.motion, game.level.rollingResistance / (fps * fps));
    }

    if (IsKeyDown((int)'a', FALSE) || IsKeyDown((int)'A', FALSE))
    {
        game.camera.angle += CAMERA_ROTATION_SPEED / 1000.0 * game.ellapsedTime;
    }

    if (IsKeyDown((int)'s', FALSE) || IsKeyDown((int)'S', FALSE))
    {
        game.camera.angle -= CAMERA_ROTATION_SPEED  / 1000.0 * game.ellapsedTime;
    }
    if(IsKeyDown(ESCAPE_KEY, FALSE))
    {
        isSplashing = TRUE;
        glutTimerFunc(5000, Quit, 0);
    }

    if (game.ball.hasStopped) {
        if(IsKeyDown(LEFT_ARROW_KEY, TRUE))
        {
            game.arrowAngle += ARROW_ROTATION_SPEED / 1000.0 * game.ellapsedTime;
        }
        if(IsKeyDown(RIGHT_ARROW_KEY, TRUE))
        {
            game.arrowAngle -= ARROW_ROTATION_SPEED / 1000.0 * game.ellapsedTime;
        }
    }
    UpdateUI(game.ellapsedTime);
    glutPostRedisplay();
}

void InitializeGLUT(int * argc, char ** argv)
{
    glutInit(argc, argv);
    glutSetOption(GLUT_MULTISAMPLE, 8);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE); // Initialize display modes, with RGBA, double buffering, and a depth buffer, and multi sampling.
    glutInitWindowPosition(INIT_WINDOW_POS_X, INIT_WINDOW_POS_Y);
    glutInitWindowSize(INIT_WINDOW_SIZE_X, INIT_WINDOW_SIZE_Y);
    glutCreateWindow(WINDOW_TITLE);
    glutDisplayFunc(DisplayCallback);
    glutReshapeFunc(ReshapeCallback);
    glClearColor(0, 0, 0, 1.0f);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //-- Backface culling

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

    game.previousTime = glutGet(GLUT_ELAPSED_TIME);

    glutTimerFunc(1000/TARGET_FPS, Update, 0);
    InitializeUI();

    //-- Set the GLUT window to be the one in focus

#ifdef _WIN32
   SetForegroundWindow(FindWindowA(NULL, WINDOW_TITLE));
#endif // _WIN32
}

void placeCamera () {

    gluLookAt(game.camera.position.x, game.camera.position.y, game.camera.position.z,
              game.camera.forward.x, game.camera.forward.y, game.camera.forward.z,
              game.camera.up.x, game.camera.up.y, game.camera.up.z);

    glRotatef(game.camera.angle, 0, 1, 0);
}

void DisplayCallback()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushAttrib(GL_ENABLE_BIT);
    glDisable(GL_TEXTURE_2D);

    //-- Place camera

    placeCamera();

    //-- Draw 3D

    struct Point3D groundPosition = {0, game.level.position.y - 2, 0};
    struct Colour ballColour = {1, 1, 1};
    struct Colour arrowColour = {1, 1, 0};

    drawGround(groundPosition);
    drawLevel (&game.level);

    if (!game.ballInHole) {
        drawBall(game.ball.position, ballColour);

        if (game.ball.hasStopped) {
            drawArrow(game.ball.position, game.arrowAngle, arrowColour);
        }
    }

    glPopAttrib();

    //-- Draw 2D / UI

    if(isSplashing == FALSE)
    {
        DrawUI();
    }
    else
    {
        DrawSplash(game.numberOfStrokes);
    }
    glutSwapBuffers();
}

void ReshapeCallback(int x, int y)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, x, y);
    gluPerspective(PERSPECTIVE_FOV, x/y, PERSPECTIVE_NEAR, PERSPECTIVE_FAR);
    glMatrixMode(GL_MODELVIEW);
}

void Quit()
{
    glutDestroyWindow(glutGetWindow());
}

