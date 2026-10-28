/* rgp:protos */
#define RGP_SELF_title_TitleLoadCardScanTickCb_4edec0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004EDEC0 -- the memory-card step of the boot sequence,
 * a two-state machine on D_0048421C.  The compare chain tests 1 then 0, which
 * by the reversed-case-order rule is source order `case 0: case 1:`, and the
 * two-case switch is what produces it.
 *
 * $at in `slti $1, $2, 0x3` says the loop condition was consumed straight by
 * the branch, so it is a plain `while`, not a materialised flag.
 *
 * +0x16 is `volatile` and that is load-bearing: the loop TEST and the loop
 * BODY each read it, and plain, mwcc propagates the test's value into the body
 * and sinks the decrement into the `beql` delay slot -- one word short.  Retail
 * re-loads at the top of the body (the duplicated `lh` IS the body's first
 * instruction, hoisted into the delay slot by the usual loop rotation).  Third
 * distinct anti-CSE use of `volatile` in this tree, after the const-extern
 * hoist and the across-a-call CSE in title_FUN_004EC700.
 */

typedef struct Obj_title_FUN_004edec0 {
    u8 pad000[0x16];
    volatile s16 field016;      /* +0x16 */
    u8 pad018[0x2];
    s16 field01A;      /* +0x1A */
} Obj_title_FUN_004edec0;

extern s8 D_0048421C;
extern void *D_004841E8;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 title_TitleLoadCardScanTickCb_4edec0(void)
{
    Obj_title_FUN_004edec0 *o;
    s32 n;
    s32 r;

    switch (D_0048421C) {
    case 0:
        if (((unsigned char)SaveModeChanged_37baa0()) == 0) {
            break;
        }
        if (SavePortCardIsReady_37b9b0(0) == 0) {
            title_TitleLoadShowError_4eeb70(8);
            return 1;
        }
        r = ((short)SaveGetResultStatus_37b970());
        if (r == 0) {
            SaveMgrSetMode_37b9e0(3);
            D_0048421C = D_0048421C + 1;
        } else if (r == 7) {
            title_TitleLoadShowError_4eeb70(7);
        } else {
            title_TitleLoadShowError_4eeb70(5);
        }
        break;
    case 1:
        if (((unsigned char)SaveModeChanged_37baa0()) == 0) {
            break;
        }
        r = ((short)SaveGetResultStatus_37b970());
        if (r == 0 || r == 7) {
            if (SaveCountUsedSlots_373340(title_TitleGetSaveCtx_4ef380()) <= 0) {
                title_TitleLoadShowError_4eeb70(0x10);
                break;
            }
            title_TitleLoadShowMsg_4eeb60(-1);
            o = ((Obj_title_FUN_004edec0 *)UiEntryListFindByTag_28ea40(D_004841E8, 0x7534));
            UiEntryListResetEntryRect_28eb40(D_004841E8, o);
            if (o != 0) {
                SaveFindLatestSlotMaybe_37ba50(&n);
                o->field016 = n;
                while (o->field016 >= 3) {
                    o->field016 = o->field016 - 1;
                    o->field01A = o->field01A + 1;
                }
            }
            UiEntryListSelectByTag_28ea90(D_004841E8, 0x7534, 0);
            title_TitleLoadFadeWidgets_4eda30(1);
            PlayMenuSeThunk_289ef0(0x23);
        } else {
            title_TitleLoadShowError_4eeb70(5);
        }
        break;
    }
    return 1;
}
