#include "types.h"
/* insmenu 0x004F3310 -- jr $31 / sh $4, -0x4D20($28)  (gp - 0x4D20 = 0x00480450) */
extern s16 D_00480450;
void insmenu_InsectVsSetSceneBgFlagMaybe_4f3310(s16 v) { D_00480450 = v; }
