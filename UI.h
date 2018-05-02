#ifndef UI_H
#define UI_H

#include "Structs.h"
#include "TextureLoading.h"
#include "Constants.h"
#include "Bool.h"
#include <math.h>
#include <stdio.h>

float barPercentage;

void InitializeUI();
void UpdateUI(int deltaTime);
float GetBarSpeed(int deltaTime);

#endif // UI_H
