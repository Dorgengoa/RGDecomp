#include "types.h"
/* insmenu 0x004EE190 (pass-27 window) -- clear a gp flag, return 1 */
extern u8 D_00484304;
s32 insmenu_InsectVsStateIdle_4ee190(void) { D_00484304 = 0; return 1; }
