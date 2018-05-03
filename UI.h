#ifndef UI_H
#define UI_H

#include "Structs.h"
#include "TextureLoading.h"
#include "Constants.h"
#include "Bool.h"
#include <math.h>
#include <stdio.h>

float barPercentage;
extern float lastBarPercentage;
extern bool hasBeenHit;

void InitializeUI();
void UpdateUI(int deltaTime);
void DrawUI();
void DrawSplash(int turns);
float GetBarSpeed(int deltaTime);

#endif // UI_H
