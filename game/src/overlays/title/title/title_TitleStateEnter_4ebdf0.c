/* rgp:protos */
#define RGP_SELF_title_TitleStateEnter_4ebdf0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004EBDF0 -- (re)enter the title screen.
 *
 * Rebuilds the widget set through title_TitleMenuWidgetsSetup_4ece80, clears the whole title
 * state block, then hands title_TitleMoviePlay_4f0600 one of three menu descriptors
 * chosen by the pending-screen id D_0048417C, and finally re-selects the saved
 * cursor row.  The first parameter is unused -- this is a table entry whose
 * signature is set by its slot, not by its body.
 *
 * ★★★ THREE LEVERS, ALL THREE MEASURED AGAINST RETAIL'S 144 WORDS:
 *  1. The gp array `D_004803D0` must be DECLARED SMALLER THAN IT IS.  Indices
 *     0, 1 and 3 are used, but `[4]` (16 bytes) is over mwcc's small-data
 *     threshold and comes out `lui`/`%lo` ABSOLUTE -- 0x254 against 0x240.
 *     `[1]` and `[2]` both give `addiu $2, $28, %gp_rel` and 0x248.  ⇒ the
 *     declared size is a RELOCATION control, not a bound; write the size the
 *     small-data threshold needs and say so.  (8 bytes is the cut here.)
 *  2. The three-way dispatch is NOT a switch and NOT an if/else-if.  Every
 *     switch spelling measured 0x248 or worse (case order 3,d,1 / 1,3,d /
 *     d,3,1 / 3,1,d / 1,d,3) and the if/else-if chain 0x244, because retail
 *     puts the `== 1` body PHYSICALLY LAST and reaches it by a forward branch.
 *     It is the cold-block `goto`: test 1 and jump away, test 3 and fall
 *     through, default in the middle, case 1 at the tail.
 *  3. The two-way dispatch at the end IS a plain if/else-if in SOURCE order
 *     0 then 1 -- the reversed-case-order rule does not apply because it is
 *     not a switch, and the tell is the `bnel` delay slot carrying the NEXT
 *     GUARD'S CONSTANT rather than a case body's store.
 *
 * ⚠ Reading it as a two-case switch (source order 1,0, per the reversed rule)
 * lays the `== 0` body out last and costs an extra `b`/`ld` pair.
 *
 */

typedef struct Widget {
    u8 pad0[0x16];
    s16 f16;
} Widget;

extern f32 D_0047D248;
extern f32 D_0047D56C;
extern s16 D_004803AC;
extern f32 D_004803B0;
extern f32 D_004803B4;
extern f32 D_004803B8;
extern void *D_004803D0[2];
extern void *D_00484154;
extern void *D_00484158;
extern void *D_0048415C;
extern void *D_00484160;
extern s32 D_00484164;
extern s16 D_0048416C;
extern void *D_00484170;
extern s16 D_00484178;
extern s16 D_0048417C;
extern s16 D_00484188;
extern s16 D_0048418C;
extern s32 D_00484190;
extern s16 D_00484194;
extern s16 D_00484198;
extern s16 D_0048419C;
extern u8 D_004841A8;
extern void *const title_D_004F1510;
extern void *const title_D_004F1520;
extern void *const title_D_004F1540;

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

s32 title_TitleStateEnter_4ebdf0(void *unused, s32 enter)
{
    Widget *w;
    s16 t;
    s32 q;

    if (enter != 0) {
        title_TitleMenuWidgetsSetup_4ece80(D_00484160, D_00484170);
        t = D_0048417C;
        D_00484188 = 0;
        D_0048418C = 0;
        D_004803B4 = D_0047D56C;
        D_00484178 = 0;
        D_004803B0 = 1.0f;
        D_004803B8 = 1.0f;
        D_00484194 = 0;
        D_00484198 = 0;
        D_00484164 = 0;
        D_00484190 = 0;
        D_004841A8 = 0;
        if (t == 1) {
            goto one;
        }
        if (t != 3) {
            goto other;
        }
        title_TitleMoviePlay_4f0600((void *)&title_D_004F1540, D_00484154, 1, D_004803D0[t]);
        goto done;
    other:
        D_0048417C = 0;
        title_TitleMoviePlay_4f0600((void *)&title_D_004F1510, D_00484154, 1, D_004803D0[0]);
        goto done;
    one:
        title_TitleMoviePlay_4f0600((void *)&title_D_004F1520, D_00484154, 1, D_004803D0[t]);
    done:
        D_0048416C = 0;
        StateMachineSetState_28ede0(D_00484158, 5, 1);
        ScreenFadeIn_1cf740(GetCurrentScene_1f5be0(), 0xA);
        UiSetWidgetColor_2905b0(D_00484170, 2, D_004803B0, D_004803B0, D_004803B0, D_004803B0);
        UiEntryListSelectByTag_28ea90(D_0048415C, 0x7531, 0);
        w = ((Widget *)UiEntryListFindByTag_28ea40(D_0048415C, 0x7531));
        q = 0;
        if (IsTgsDemoBuild_207f20() == 0) {
            q = (s8)((signed char)TitleCursorRowGet_206b00());
            if (q < 0) {
                q = 0;
            }
        }
        w->f16 = q;
        UiSetWidgetPos_290f60(D_00484170, 2, 0xB4, w->f16 * (0x18 - D_0048419C * 4) + 0x136);
        UiSetWidgetAlpha_2907a0(D_00484170, 3, D_0047D248);
        UiSetWidgetAlpha_2907a0(D_00484170, 4, D_0047D248);
        UiSetWidgetAlpha_2907a0(D_00484170, 0x66, D_0047D248);
        UiSetWidgetAlpha_2907a0(D_00484170, 5, D_0047D248);
        if (w->f16 == 0) {
            D_004803AC = 1;
            UiSetWidgetAlpha_2907a0(D_00484170, 3, 1.0f);
        } else if (w->f16 == 1) {
            D_004803AC = 2;
            UiSetWidgetAlpha_2907a0(D_00484170, 4, 1.0f);
        }
    }
    return 1;
}
