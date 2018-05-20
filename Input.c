#include "Input.h"

bool keys[TOTAL_KEYS];
float wheelScroll;

void InputInitialize()
{
    for(int i = 0; i < TOTAL_KEYS; i++)
    {
        keys[i] = FALSE;
    }
    wheelScroll = 500;
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

void MouseCallback(int button, int state, int x, int y)
{
    if(button == 3)
    {
        wheelScroll -= 3;
        if(wheelScroll < 134)
            wheelScroll = 134;
    }
    if(button == 4)
    {
        wheelScroll += 3;
        if(wheelScroll > 758)
            wheelScroll = 758;
    }
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
