/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsStateIdle_4ed150 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x004ED150 (pass-27 window) -- clear a gp flag, return 1 */
extern u8 D_00484304;
s32 insmenu_InsectVsStateIdle_4ed150(void) { D_00484304 = 0; return 1; }
