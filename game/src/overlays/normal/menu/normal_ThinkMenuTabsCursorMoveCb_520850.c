/* rgp:protos */
#define RGP_SELF_normal_ThinkMenuTabsCursorMoveCb_520850 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00520850 -- the left/right cursor step on the shop page.  Both
 * halves are the same shape: the repeat test (func_1839F0) picks the
 * direction, the in-range case steps the cursor, and the edge case only wraps
 * when the EDGE test (func_183DD0) says the key is not being auto-repeated.
 * `chg` is the single "something moved" flag that gates the whole tail. */

typedef struct Sess { u8 pad00[0x10]; s8 f10; s8 f11; } Sess;

extern u8 D_004B2570;

extern Sess *D_00484934;          /* gp - 0x83C */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_ThinkMenuTabsCursorMoveCb_520850(void *a)
{
    const u8 *pad;
    s32 cur;
    s32 chg;
    s32 max;

    pad = &D_004B2570;
    chg = 0;
    cur = D_00484934->f11;
    max = D_00484934->f10;
    if (PadIsTriggered_1839f0(pad, 4) != 0) {
        if (cur > 0) {
            cur--;
            chg = 1;
        } else if (PadIsRepeatTriggered_183dd0(pad, 4) == 0) {
            cur = max - 1;
            chg = 1;
        }
    } else if (PadIsTriggered_1839f0(pad, 8) != 0) {
        if (cur < max - 1) {
            cur++;
            chg = 1;
        } else if (PadIsRepeatTriggered_183dd0(pad, 8) == 0) {
            cur = 0;
            chg = 1;
        }
    }
    if (chg != 0) {
        D_00484934->f11 = cur;
        normal_ThinkMenuTabsLayout_520500(0x7535, cur);
        MenuFillItemGrid_2a4b40(D_00484934, 0x7539);
        MenuFillItemCounts_2a3d90(D_00484934, 0x753A);
        normal_ThinkMenuGridCursorMoveCb_520a90(a);
        PlayMenuSe_289ef0(0xB);
    }
    return 1;
}
