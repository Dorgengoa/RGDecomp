#include "types.h"
/* insmenu 0x004F3840 -- jr $31 / lw $2, -0xE78($28)  (gp - 0xE78 = 0x004842F8) */
extern s32 D_004842F8;
s32 insmenu_InsectVsGetSaveIconData_4f3840(void) { return D_004842F8; }
