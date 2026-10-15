#include "types.h"
/* insmenu 0x004F3320 -- jr $31 / lw $2, -0xE74($28)  (gp - 0xE74 = 0x004842FC) */
extern s32 D_004842FC;
s32 insmenu_InsectVsGetMsgTable_4f3320(void) { return D_004842FC; }
