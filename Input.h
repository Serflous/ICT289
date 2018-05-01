#ifndef INPUT_H

#include "Bool.h"
#define TOTAL_KEYS 235

extern bool keys[TOTAL_KEYS];

void InputInitialize();
void NormalKeyDownCallback(char key, int x, int y);
void NormalKeyUpCallback(char key, int x, int y);
void SpecialKeyDownCallback(int key, int x, int y);
void SpecialKeyUpCallback(int key, int x, int y);
bool IsKeyDown(int key, bool isSpecial);
bool IsKeyUp(int key, bool isSpecial);

#endif // INPUT_H
