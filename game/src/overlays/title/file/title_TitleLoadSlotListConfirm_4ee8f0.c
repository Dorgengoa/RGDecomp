/* rgp:protos */
#define RGP_SELF_title_TitleLoadSlotListConfirm_4ee8f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004EE8F0 -- add two halfword fields, publish the sum to
 * a gp-relative global, then branch on a call result.
 *
 * `dsll32 $4, $2, 16` / `dsra32 $4, $4, 16` is a 16-bit sign extension of the
 * sum before it is passed on, i.e. the sum is an s16.
 *
 * ★ `return 1` belongs INSIDE both arms.  With one return after the join mwcc
 * hoists `ld $31` into each arm and materialises the 1 once; retail does the
 * opposite -- the 1 twice, the epilogue shared.
 */

typedef struct Obj_title_FUN_004ee8f0 {
    u8 pad000[0x12];
    s16 field012;      /* +0x12 */
    u8 pad014[0x2];
    s16 field016;      /* +0x16 */
} Obj_title_FUN_004ee8f0;

extern s16 D_004841F8;
extern void *D_004841E8;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 title_TitleLoadSlotListConfirm_4ee8f0(Obj_title_FUN_004ee8f0 *o)
{
    s16 sum;

    sum = o->field016 + o->field012;
    D_004841F8 = sum;
    SaveMgrSetSlot_37b9c0(sum);
    if (SaveSlotEntryIsValidAt_373440(title_TitleGetSaveCtx_4ef380(), D_004841F8) != 0) {
        PlayMenuSeThunk_289ef0(5);
        UiEntryListSelectByTag_28ea90(D_004841E8, 0x7535, 0);
        return 1;
    }
    PlayMenuSeThunk_289ef0(6);
    return 1;
}
