#include "UI.h"

struct Texture texPowerTitle;
struct Texture texPowerBar;
struct Texture texPowerBarFill;
float barPercentage;

void InitializeUI()
{
    texPowerTitle = LoadTexture("res/powerTitle.raw", 64, 32, 4);
    texPowerBar = LoadTexture("res/powerBar.raw", 16, 128, 4);
    texPowerBarFill = LoadTexture("res/powerBarFill.raw", 16, 16, 4);
    barPercentage = 0;
}

void DrawUI()
{
    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
    int powerTitleStartX = windowWidth - texPowerTitle.texWidth;
    int powerBarStartX = windowWidth - (texPowerTitle.texWidth / 2) - (texPowerBar.texWidth  /2);
    int powerBarStartY = texPowerTitle.texHeight + 10;
    float barHeight = (texPowerBar.texHeight) * (1 - barPercentage);
    float texBarHeight = barHeight / 16.0f;
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
        glLoadIdentity();
        glOrtho(0, windowWidth, windowHeight, 0, -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
            glLoadIdentity();
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
