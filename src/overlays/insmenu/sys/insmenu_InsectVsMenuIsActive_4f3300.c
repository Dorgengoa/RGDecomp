#include "types.h"
/* insmenu 0x004F3300 -- lh $2, gp-0xE70 / slt $2, $0, $2.  The compare
 * result is the RETURN VALUE, so it has to land in $2; there is no branch
 * and the $at class does not reach here. */
extern s16 D_00484300;
s32 insmenu_InsectVsMenuIsActive_4f3300(void) { return D_00484300 > 0; }
