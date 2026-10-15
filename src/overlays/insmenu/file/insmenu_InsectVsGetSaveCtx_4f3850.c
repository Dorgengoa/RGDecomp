#include "types.h"
/* insmenu 0x004F3850 -- jr $31 / lw $2, -0xE7C($28)  (gp - 0xE7C = 0x004842F4) */
extern s32 D_004842F4;
s32 insmenu_InsectVsGetSaveCtx_4f3850(void) { return D_004842F4; }
