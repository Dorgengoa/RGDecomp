/* rgp:protos */
#define RGP_SELF_MenuTabCycleWrap_2b15a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
extern void *D_00482374;
extern u8 D_004823CC;
extern u8 D_004B2570[];

s32 MenuTabCycleWrap_2b15a0(s32 *arg0, s32 arg1)
{
    u8 *buf;
    s32 ret;
    s32 max;
    s32 v;

    buf = D_004B2570;
    ret = 0;
    max = arg1 - 1;
    if (D_004823CC != 0 || (*(s8 *)((u8 *)D_00482374 + 0x1C) != 0 && ((unsigned char)MenuItemGetOpenModeMaybe_2a4ec0(D_00482374)) != 2)) {
        max = arg1 - 2;
    }
    if (PadIsTriggered_1839f0(buf, 4) != 0) {
        v = *arg0;
        if (v > 0) {
            *arg0 = v - 1;
            ret = 1;
        } else if (PadIsRepeatTriggered_183dd0(buf, 4) == 0) {
            *arg0 = max;
            ret = 1;
        }
    } else if (PadIsTriggered_1839f0(buf, 8) != 0) {
        v = *arg0;
        if (v < max) {
            *arg0 = v + 1;
            ret = 1;
        } else if (PadIsRepeatTriggered_183dd0(buf, 8) == 0) {
            *arg0 = 0;
            ret = 1;
        }
    }
    return ret;
}
