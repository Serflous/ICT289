#include "UI.h"

struct Texture texPowerTitle;
struct Texture texPowerBar;
struct Texture texPowerBarFill;
struct Texture texUIBarCorner;
struct Texture texUIBarLine;
float barPercentage;
bool spaceDown;

void InitializeUI()
{
    texPowerTitle = LoadTexture("res/powerTitle.raw", 64, 32, 4);
    texPowerBar = LoadTexture("res/powerBar.raw", 16, 128, 4);
    texPowerBarFill = LoadTexture("res/powerBarFill.raw", 16, 16, 4);
    texUIBarCorner = LoadTexture("res/UI_Frame_Corner.raw", 32, 32, 4);
    texUIBarLine = LoadTexture("res/UI_Frame_Line.raw", 1, 32, 4);
    barPercentage = 0;
    spaceDown = FALSE;
}

void DrawUI()
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
        glMatrixMode(GL_PROJECTION);
    glPopMatrix();
}

void UpdateUI()
{
    if(IsKeyDown(' ', FALSE) && spaceDown == FALSE)
    {
        spaceDown = TRUE;
        barPercentage = 0.01f;
    }
    if(IsKeyUp(' ', FALSE) && spaceDown == TRUE)
    {
        spaceDown = FALSE;
        printf("Power: %f\n", barPercentage);
    }
    if(spaceDown == TRUE)
    {
        barPercentage += GetBarSpeed();
        if(barPercentage > 1)
            barPercentage = 0.01f;
    }
    else
    {
        barPercentage = 0;
    }
}

float GetBarSpeed()
{
    return 0.1f * powf(barPercentage, 1.4f);
}
