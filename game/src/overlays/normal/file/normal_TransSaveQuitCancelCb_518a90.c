/* rgp:protos */
#define RGP_SELF_normal_TransSaveQuitCancelCb_518a90 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00518A90 -- a once-only initialiser guarded by a gp `s8` latch.
 * The latch is set to 1 and 1 is also returned, so it is ONE `addiu` in `$2`
 * (the recorded "a constant stored and also returned" shape).
 * Guard polarity: retail's `beql` branches INTO the body and lets
 * `b <epilogue> / addiu $2,$0,1` fall through, so the source is the EARLY
 * RETURN on `!= 0`.  Written as `if (== 0) { body }` mwcc merges the exit into
 * the epilogue with `bnezl / ld $31` and the unit is one word short.
 * One of the 55 unnamed functions; see scripts/n_unnamed.py. */
extern s8   D_00484820;
extern void *D_004847D8;
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_TransSaveQuitCancelCb_518a90(void)
{
    if (D_00484820 != 0) {
        return 1;
    }
    normal_TransSaveShowMsg_519ff0(-1);
    normal_TransSavePanelFade_518700(2);
    UiEntryListSelectByTag_28ea90(D_004847D8, 2, 0);
    D_00484820 = 1;
    return 1;
}
