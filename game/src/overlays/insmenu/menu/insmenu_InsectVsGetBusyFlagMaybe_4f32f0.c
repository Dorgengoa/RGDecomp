/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsGetBusyFlagMaybe_4f32f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x004F32F0 -- jr $31 / lbu $2, gp-0xE6C in the delay slot.  No
 * `andi` after it, so the return is s32 and the promotion is free. */
extern u8 D_00484304;
s32 insmenu_InsectVsGetBusyFlagMaybe_4f32f0(void) { return D_00484304; }
