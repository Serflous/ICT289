#include "Input.h"

bool keys[TOTAL_KEYS];

void InputInitialize()
{
    for(int i = 0; i < TOTAL_KEYS; i++)
    {
        keys[i] = FALSE;
    }
}

void NormalKeyDownCallback(char key, int x, int y)
{
    keys[key] = TRUE;
}

void NormalKeyUpCallback(char key, int x, int y)
{
    keys[key] = FALSE;
}

void SpecialKeyDownCallback(int key, int x, int y)
{
    keys[key + 255] = TRUE;
}

void SpecialKeyUpCallback(int key, int x, int y)
{
    keys[key + 255] = FALSE;
}

bool IsKeyDown(int key, bool isSpecial)
{
    key = isSpecial == FALSE ? key : key + 255;
    return keys[key];
}

bool IsKeyUp(int key, bool isSpecial)
{
    key = isSpecial == FALSE ? key : key + 255;
    return !keys[key];
}
