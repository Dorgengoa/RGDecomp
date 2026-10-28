/* rgp:protos */
#define RGP_SELF_MenuItemGridCellSetEmpty_2a4c80 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_common_subs off
/*rgp*/

typedef struct {
    s16 x0;
    s16 x2;
    s16 x4;
    s16 x6;
    u8 pad8[4];
    s16 xC;
    s16 xE;
    u8 pad10[0x10];
} E2a4;

s32 MenuItemGridCellSetEmpty_2a4c80(s32 *arg0, s32 pd1, s32 arg2)
{
    s32 base;
    E2a4 *e;

    base = *arg0;
    if (base == 0) {
        return 0;
    }
    e = (E2a4 *)((s32)UiGetWidgetSprite_28fe10(base, pd1, 0));
    if (e == NULL) {
        return 0;
    }
    e += arg2;
    e->x0 = (arg2 % 8) * 0x30 + 1;
    e->x2 = (arg2 / 8) * 0x38 + 1;
    e->x4 = 0;
    e->xC = 0;
    e->x6 = 0;
    e->xE = 0;
    return 1;
}
