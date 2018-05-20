#ifndef INPUT_H

#include "Bool.h"
#define TOTAL_KEYS 363

extern bool keys[TOTAL_KEYS];
extern float wheelScroll;

void InputInitialize();
void NormalKeyDownCallback(char key, int x, int y);
void NormalKeyUpCallback(char key, int x, int y);
void SpecialKeyDownCallback(int key, int x, int y);
void SpecialKeyUpCallback(int key, int x, int y);
void MouseCallback(int button, int state, int x, int y);
bool IsKeyDown(int key, bool isSpecial);
bool IsKeyUp(int key, bool isSpecial);

#endif // INPUT_H
