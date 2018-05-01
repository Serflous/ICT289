#ifndef UI_H
#define UI_H

#include "Structs.h"
#include "TextureLoading.h"
#include "Constants.h"
#include "Bool.h"
#include <math.h>

extern float barPercentage;

void InitializeUI();
void UpdateUI();
float GetBarSpeed();

#endif // UI_H
