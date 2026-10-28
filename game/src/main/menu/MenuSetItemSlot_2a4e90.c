/* rgp:protos */
#define RGP_SELF_MenuSetItemSlot_2a4e90 1
#include "port/game_protos.h"
#line 1
#include "types.h"
void MenuSetItemSlot_2a4e90(u8 *p, s32 i, s32 v)
{
    s32 t;

    /* `slti $1` = the $at compare class: `i > 2`, not `i >= 3`. */
    if (i < 0 || i > 2) return;
    t = i * 8;
    *(s32 *)(t + (s32)p + 0x54) = v;
}
