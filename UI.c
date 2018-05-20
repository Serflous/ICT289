#include "UI.h"

struct Texture texPowerTitle;
struct Texture texPowerBar;
struct Texture texPowerBarFill;
struct Texture texUIBarCorner;
struct Texture texUIBarLine;
struct Texture texSplashScreen;
float barPercentage;
float lastBarPercentage;
bool hasBeenHit;
bool spaceDown;

void InitializeUI()
{
    texPowerTitle = LoadTexture("res/powerTitle.raw", 64, 32, 4);
    texPowerBar = LoadTexture("res/powerBar.raw", 16, 128, 4);
    texPowerBarFill = LoadTexture("res/powerBarFill.raw", 16, 16, 4);
    texUIBarCorner = LoadTexture("res/UI_Frame_Corner.raw", 32, 32, 4);
    texUIBarLine = LoadTexture("res/UI_Frame_Line.raw", 1, 32, 4);
    texSplashScreen = LoadTexture("res/SplashScreen.raw", 1024, 512, 4);
    barPercentage = 0;
    lastBarPercentage = 0;
    spaceDown = FALSE;
    hasBeenHit = FALSE;
}

void DrawString(const char * string, struct Point2D position, struct Point3D colour, struct Point3D scale)
{
    glPushAttrib(GL_ENABLE_BIT);
    glDisable(GL_TEXTURE_2D);
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(position.x, position.y, -1);
    glScalef(scale.x, scale.y, scale.z);
    glRotatef(180, 1, 0, 0);

    glColor4f(colour.x, colour.y, colour.z, 1.0f);
    glutStrokeString(GLUT_STROKE_ROMAN, string);

    glPopMatrix();
    glPopAttrib();
}

void DrawUI(int par, int turns)
{
    // UI BAR RGB(135, 209, 237)
    int windowWidth = glutGet(GLUT_WINDOW_WIDTH); // Window Width
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT); // Window Height
    int powerTitleStartX = windowWidth - texPowerTitle.texWidth; // Calculate the x position of the title.
    int powerBarStartX = windowWidth - (texPowerTitle.texWidth / 2) - (texPowerBar.texWidth  /2); // Calculate the X position of the power bar outline
    int powerBarStartY = texPowerTitle.texHeight + 10; // Calculate the Y position of the power bar outline
    float barHeight = (texPowerBar.texHeight) * (1 - barPercentage); // Calculate the height of the bar to draw based on percentage
    float texBarHeight = (texPowerBar.texHeight - barHeight) / texPowerBarFill.texHeight; // Calculate the value of the texture height. Values > 1 create tiling effect.
    float uiBarWidth = windowWidth / 5;
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
        glLoadIdentity();
        glOrtho(0, windowWidth, windowHeight, 0, -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
            glLoadIdentity();
            // Draw UI Bar
            // Texture coords > 1 create tiling effect.
            // Top Left Corner
            glBindTexture(GL_TEXTURE_2D, texUIBarCorner.texId);
            glBegin(GL_QUADS);
                glTexCoord2f(0, 0);
                glVertex3f(windowWidth - uiBarWidth, 0, 0);
                glTexCoord2f(0, 1);
                glVertex3f(windowWidth - uiBarWidth, texUIBarCorner.texHeight, 0);
                glTexCoord2f(1, 1);
                glVertex3f(windowWidth - uiBarWidth + texUIBarCorner.texWidth, texUIBarCorner.texHeight, 0);
                glTexCoord2f(1, 0);
                glVertex3f(windowWidth - uiBarWidth + texUIBarCorner.texWidth, 0, 0);
            glEnd();
            // Top Right Corner
            glBegin(GL_QUADS);
                glTexCoord2f(0, 1);
                glVertex3f(windowWidth - texUIBarCorner.texWidth, 0, 0);
                glTexCoord2f(1, 1);
                glVertex3f(windowWidth - texUIBarCorner.texWidth, texUIBarCorner.texHeight, 0);
                glTexCoord2f(1, 0);
                glVertex3f(windowWidth, texUIBarCorner.texHeight, 0);
                glTexCoord2f(0, 0);
                glVertex3f(windowWidth, 0, 0);
            glEnd();
            // Bottom Left
            glBegin(GL_QUADS);
                glTexCoord2f(1, 0);
                glVertex3f(windowWidth - uiBarWidth, windowHeight - texUIBarCorner.texHeight, 0);
                glTexCoord2f(0, 0);
                glVertex3f(windowWidth - uiBarWidth, windowHeight, 0);
                glTexCoord2f(0, 1);
                glVertex3f(windowWidth - uiBarWidth + texUIBarCorner.texWidth, windowHeight, 0);
                glTexCoord2f(1, 1);
                glVertex3f(windowWidth - uiBarWidth + texUIBarCorner.texWidth, windowHeight - texUIBarCorner.texHeight, 0);
            glEnd();
            // Bottom Right
            glBegin(GL_QUADS);
                glTexCoord2f(1, 1);
                glVertex3f(windowWidth - texUIBarCorner.texWidth, windowHeight - texUIBarCorner.texHeight, 0);
                glTexCoord2f(1, 0);
                glVertex3f(windowWidth - texUIBarCorner.texWidth, windowHeight, 0);
                glTexCoord2f(0, 0);
                glVertex3f(windowWidth, windowHeight, 0);
                glTexCoord2f(0, 1);
                glVertex3f(windowWidth, windowHeight - texUIBarCorner.texHeight, 0);
            glEnd();
            // Middle Lines
            glBindTexture(GL_TEXTURE_2D, texUIBarLine.texId);
            glBegin(GL_QUADS);
                glTexCoord2f(windowWidth - uiBarWidth + texUIBarCorner.texWidth, 0);
                glVertex3f(windowWidth - uiBarWidth + texUIBarCorner.texWidth, 0, 0);
                glTexCoord2f(windowWidth - uiBarWidth + texUIBarCorner.texWidth, 1);
                glVertex3f(windowWidth - uiBarWidth + texUIBarCorner.texWidth, windowHeight, 0);
                glTexCoord2f(windowWidth - texUIBarCorner.texWidth, 1);
                glVertex3f(windowWidth - texUIBarCorner.texWidth, windowHeight, 0);
                glTexCoord2f(windowWidth - texUIBarCorner.texWidth, 0);
                glVertex3f(windowWidth - texUIBarCorner.texWidth, 0, 0);
            glEnd();
            //Left Side Lines
            glBegin(GL_QUADS);
                glTexCoord2f(windowWidth - uiBarWidth, 0);
                glVertex3f(windowWidth - uiBarWidth, texUIBarCorner.texHeight, 0);
                glTexCoord2f(windowWidth - uiBarWidth, 1);
                glVertex3f(windowWidth - uiBarWidth, windowHeight - texUIBarCorner.texHeight, 0);
                glTexCoord2f(windowWidth - uiBarWidth + texUIBarCorner.texWidth, 1);
                glVertex3f(windowWidth - uiBarWidth + texUIBarCorner.texWidth, windowHeight - texUIBarCorner.texHeight, 0);
                glTexCoord2f(windowWidth - uiBarWidth + texUIBarCorner.texWidth, 0);
                glVertex3f(windowWidth - uiBarWidth + texUIBarCorner.texWidth, texUIBarCorner.texHeight, 0);
            glEnd();
            // Right Side Lines
            glBegin(GL_QUADS);
                glTexCoord2f(windowWidth - texUIBarCorner.texWidth, 0);
                glVertex3f(windowWidth - texUIBarCorner.texWidth, texUIBarCorner.texHeight, 0);
                glTexCoord2f(windowWidth - texUIBarCorner.texWidth, 1);
                glVertex3f(windowWidth - texUIBarCorner.texWidth, windowHeight - texUIBarCorner.texHeight, 0);
                glTexCoord2f(windowWidth, 1);
                glVertex3f(windowWidth, windowHeight - texUIBarCorner.texHeight, 0);
                glTexCoord2f(windowWidth, 0);
                glVertex3f(windowWidth, texUIBarCorner.texHeight, 0);
            glEnd();

            // Draw Power Title
            glBindTexture(GL_TEXTURE_2D, texPowerTitle.texId);
            glBegin(GL_QUADS);
                glTexCoord2f(0, 0);
                glVertex3f(powerTitleStartX, 0, 0);
                glTexCoord2f(0, 1);
                glVertex3f(powerTitleStartX, texPowerTitle.texHeight, 0);
                glTexCoord2f(1, 1);
                glVertex3f(powerTitleStartX + texPowerTitle.texWidth, texPowerTitle.texHeight, 0);
                glTexCoord2f(1, 0);
                glVertex3f(powerTitleStartX + texPowerTitle.texWidth, 0, 0);
            glEnd();

            // Draw Power Bar
            glBindTexture(GL_TEXTURE_2D, texPowerBar.texId);
            glBegin(GL_QUADS);
                glTexCoord2f(0, 0);
                glVertex3f(powerBarStartX, powerBarStartY, 0);
                glTexCoord2f(0, 1);
                glVertex3f(powerBarStartX, powerBarStartY + texPowerBar.texHeight, 0);
                glTexCoord2f(1, 1);
                glVertex3f(powerBarStartX + texPowerBar.texWidth, powerBarStartY + texPowerBar.texHeight, 0);
                glTexCoord2f(1, 0);
                glVertex3f(powerBarStartX + texPowerBar.texWidth, powerBarStartY, 0);
            glEnd();

            // Fill Power Bar
            glBindTexture(GL_TEXTURE_2D, texPowerBarFill.texId);
            glBegin(GL_QUADS);
                glTexCoord2f(0, 0);
                glVertex3f(powerBarStartX, powerBarStartY + barHeight, 0);
                glTexCoord2f(0, texBarHeight);
                glVertex3f(powerBarStartX, powerBarStartY + texPowerBar.texHeight, 0);
                glTexCoord2f(1, texBarHeight);
                glVertex3f(powerBarStartX + texPowerBarFill.texWidth, powerBarStartY + texPowerBar.texHeight, 0);
                glTexCoord2f(1, 0);
                glVertex3f(powerBarStartX + texPowerBarFill.texWidth, powerBarStartY + barHeight, 0);
            glEnd();
        glPopMatrix();
        struct Point2D powerTextPos, courseParPos, playerMovesTakenPos;
        powerTextPos.x = windowWidth - (uiBarWidth / 3);
        powerTextPos.y = powerBarStartY + texPowerBar.texHeight + 20;
        courseParPos.x = windowWidth - uiBarWidth + 5;
        courseParPos.y = powerBarStartY + texPowerBar.texHeight + 50;
        playerMovesTakenPos.x = windowWidth - uiBarWidth + 5;
        playerMovesTakenPos.y = powerBarStartY + texPowerBar.texHeight + 90;
        struct Point3D colour;
        colour.x = 0;
        colour.y = 0;
        colour.z = 0;
        struct Point3D scale;
        scale.x = 0.1f;
        scale.y = 0.1f;
        scale.z = 0.1f;
        char * powerTextBuffer[50];
        char * courseParTextBuffer[50];
        char * playerMovesTakenTextBuffer[50];
        snprintf(powerTextBuffer, sizeof(powerTextBuffer) - 1, "Power: %.2f", lastBarPercentage);
        snprintf(courseParTextBuffer, sizeof(courseParTextBuffer) - 1, "Course Par: %i", par);
        snprintf(playerMovesTakenTextBuffer, sizeof(playerMovesTakenTextBuffer) - 1, "Moves Taken: %i", turns);
        DrawString(powerTextBuffer, powerTextPos, colour, scale);
        scale.x = 0.2f;
        scale.y = 0.2f;
        scale.z = 0.2f;
        DrawString(courseParTextBuffer, courseParPos, colour, scale);
        DrawString(playerMovesTakenTextBuffer, playerMovesTakenPos, colour, scale);
        glMatrixMode(GL_PROJECTION);
    glPopMatrix();
}

void DrawSplash(int turns)
{
    int windowWidth = glutGet(GLUT_WINDOW_WIDTH); // Window Width
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT); // Window Height
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
        glLoadIdentity();
        glOrtho(0, windowWidth, windowHeight, 0, -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
            glLoadIdentity();
            glBindTexture(GL_TEXTURE_2D, texSplashScreen.texId);
            glBegin(GL_QUADS);
                glTexCoord2f(0, 0);
                glVertex3f(0, 0, 0);
                glTexCoord2f(0, 1);
                glVertex3f(0, windowHeight, 0);
                glTexCoord2f(1, 1);
                glVertex3f(windowWidth, windowHeight, 0);
                glTexCoord2f(1, 0);
                glVertex3f(windowWidth, 0, 0);
            glEnd();
        glPopMatrix();
        if(turns > 0)
        {
            struct Point2D position;
            position.x = windowWidth / 4;
            position.y = windowHeight - 100;
            struct Point3D colour;
            colour.x = 0;
            colour.y = 0;
            colour.z = 0;
            struct Point3D scale;
            scale.x = 0.2f;
            scale.y = 0.2f;
            scale.z = 0.2f;
            char * turnsBuffer[50];
            snprintf(turnsBuffer, sizeof(turnsBuffer) - 1, "Moves Taken: %i", turns);
            DrawString(turnsBuffer, position, colour, scale);
        }
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
}

void UpdateUI(int deltaTime)
{
    static float hundredCount = 0;
    if(IsKeyDown(' ', FALSE) && spaceDown == FALSE)
    {
        spaceDown = TRUE;
        barPercentage = 0.01f;
    }
    if(IsKeyUp(' ', FALSE) && spaceDown == TRUE)
    {
        spaceDown = FALSE;
        lastBarPercentage = barPercentage;
        hasBeenHit = TRUE;
    }
    if(spaceDown == TRUE)
    {
        barPercentage += GetBarSpeed(deltaTime);
        if(barPercentage >= 1)
        {
            hundredCount += (deltaTime);
            barPercentage = 1;
            if(hundredCount >= 100)
            {
                barPercentage = 0.01f;
                hundredCount = 0;
            }
        }
    }
    else
    {
        barPercentage = 0;
    }
}

float GetBarSpeed(int deltaTime)
{
    float newDelta = deltaTime / 20.0f;
    if(barPercentage < 0.3)
    {
        return 0.011f * newDelta;
    }
    /*else if (barPercentage > 0.95)
    {
        return 0.001f * newDelta;
    }*/
    else
    {
        return 0.07f * powf(barPercentage, 1.4f) * newDelta;
    }
}
