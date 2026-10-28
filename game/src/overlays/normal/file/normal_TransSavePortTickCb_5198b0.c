/* rgp:protos */
#define RGP_SELF_normal_TransSavePortTickCb_5198b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x005198B0 -- latch gate then a saturating decrement; the `lh 0x12`
 * is duplicated into the blezl delay slot by the scheduler, so it is ONE
 * source read after the if. */

typedef struct Obj {
    u8  pad000[0x12];
    s16 f12;
} Obj;

extern s8 D_00484804;   /* gp - 0x96C */
extern s8 D_00484808;   /* gp - 0x968 */

/*rgp*/

s32 normal_TransSavePortTickCb_5198b0(Obj *p)
{
    s8 v;

    if (D_00484804 != 0) {
        return 1;
    }
    v = D_00484808;
    if (v > 0) {
        D_00484808 = v - 1;
    }
    normal_TransSavePortCursorBob_5187c0(p->f12, 0, 1);
    return 1;
}
