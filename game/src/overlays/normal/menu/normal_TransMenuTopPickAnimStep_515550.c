/* rgp:protos */
#define RGP_SELF_normal_TransMenuTopPickAnimStep_515550 1
#include "port/game_protos.h"
#line 1
/* === SESSION 68 (2026-09-20, SOLO): MATCH, MERGED.  181 bad -> 0 (the 2
 * residual "bad" words are the normal_jtbl_005266F0 lui/addiu pair, which
 * n_obytecheck cannot resolve because the table lives in this object's own
 * .rodata -- the merged normal_ShopMenuTopPickAnimStep_509e90 scores the same 2 for the same
 * reason.  n_olink.py relinks NORMAL.BIN BYTE-IDENTICAL with this unit
 * compiled, and the arming control (0x30 -> 0x31 in the func_290F60 call)
 * gives exactly 1 differing byte at vram 0x00515840.)
 *
 * The 181 bad were FOUR SOURCE DEFECTS, not a spelling problem.  s31's
 * automated DEFINING-STATEMENT MOVE deck had moved `D_004847A0 = 4;` out of
 * case 3 and into case 1, which is semantically wrong and cost most of them:
 *   1. `D_004847A0 = 4;` belongs at the END OF CASE 3 (retail 0x005156F8).
 *   2. `id = D_004847A4 + 0x754F;` was a statement stranded BEFORE the first
 *      case label (dead m2c artifact); case 1 and case 2 each assign it.
 *   3. case 5 carried a dead `v = D_004847A8 - D_0047D94C;` that belongs in
 *      case 6, which was READING `v` UNINITIALISED
 *      ([[levers.d/uninit-local-draft-screen]]).
 *   4. `1.9f` is NOT a literal -- it is MAIN's pool word at gp-0x7E14, so it
 *      must be `extern f32 D_0047D35C` ([[levers.d/mwcc-float-literal-pool]]).
 * Fixing 1-3 took sq 2 -> 1 and the frame 0x60 -> 0x40 in one step, i.e. the
 * s67 `sqscan.py` +1 row for this unit was a symptom of the dead `v` web.
 *
 * *** THE LAST 2 WORDS -- HOW THE INNER n==2/n==3 TEST IS SPELLED.  Retail
 * compares TWICE (`beq $3,$2(2)` / `addiu $2,$0,3` / `bne`); mwcc collapses
 * `n == 2 || n == 3` into a `sltiu` RANGE CHECK and is 2 words SHORT.  The
 * only shape measured that keeps two separate compares is the DE MORGAN
 * inversion:
 *      else if (!(n != 2 && n != 3))
 * Measured, exact length: a `switch (D_004847A4)` over cases 0/2/3 emits its
 * compare chain in DESCENDING order (3,2,0) and is +2; `case 2,3` first is
 * also +2; `default: break;` is +2; a nested `if (n==0) ... else switch(n)`
 * is +2; `n == 3 || n == 2` is the same range check at -2; `(u16)` casts on
 * the operands give -1.  Two `goto` forms also reach 255 w / 4 bad but produce
 * a DIFFERENT object from the de Morgan one -- de Morgan is the one that
 * matches.  Sweeps: build/wf-normal/s68/a1.py, a2.py, a3.py.
 */
#include "types.h"
/* normal 0x00515550 -- the 7-state (normal_jtbl_005266F0, cases 0..6, case 0 = exit)
 * fade driver for the transfer banner.  D_004847A0 is the s16 phase,
 * D_004847A8 the f32 ramp, D_004847A4 the s16 sub-index, D_004846E8 the
 * widget handle (reloaded before every call -- a gp pointer across a call).
 * D_0047D35C is MAIN's `.lit4` pool entry 0x0047D35C (confirmed by the merged
 * normal_FieldHudAllySuggestTimerUpdate_4eea90 / normal_MenuBattleEndExpBonusShowMaybe_4eb400); every other gp float here lives
 * ABOVE the pool (0x0047D9xx / 0x0047DAxx) and stays an extern -- 0x0047DA1C
 * and 0x0047DA28 BOTH hold 0.05f and are both referenced by this one
 * function, so they cannot both be literals in one TU.
 * Frame 0x40: locals are allocated DOWNWARD from the top, so the five
 * address-taken slots are declared 0x3C, 0x38, 0x34, 0x30, 0x2C in order. */

extern void *D_004846E8;          /* gp - 0xA88 */
extern s16   D_004847A0;          /* gp - 0x9D0 */
extern s16   D_004847A4;          /* gp - 0x9CC */
extern f32   D_004847A8;          /* gp - 0x9C8 */
extern f32   D_0047D35C;          /* gp - 0x7E14,  D_0047D35C  */
extern f32   D_0047D920;          /* gp - 0x7850,  0.4f  */
extern f32   D_0047D94C;          /* gp - 0x7824,  0.3f  */
extern f32   D_0047D9A8;          /* gp - 0x77C8,  0.15f */
extern f32   D_0047DA1C;          /* gp - 0x7754,  0.05f */
extern f32   D_0047DA20;          /* gp - 0x7750, -0.05f */
extern f32   D_0047DA24;          /* gp - 0x774C, -0.1f  */
extern f32   D_0047DA28;          /* gp - 0x7748,  0.05f */

typedef struct Ent2 { u8 pad00[0x30]; s16 f30; } Ent2;
typedef struct Ent  { u8 pad00[0x18]; Ent2 *f18; } Ent;

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
/*rgp*/
/*rgp*/

s32 normal_TransMenuTopPickAnimStep_515550(void)
{
    s32  s3c;
    s32  s38;
    s32  s34;
    s32  s30;
    s32  s2c;
    Ent *ent;
    u16  id;
    s32  n;
    f32  v;
    void *ev;
    void *pl;

    ent = ((Ent *)GetGameData_1fede0());
    switch (D_004847A0) {
    case 1:
        id = D_004847A4 + 0x754F;
        v = D_004847A8 + D_0047D920;
        D_004847A8 = v;
        if (!(v < D_0047D35C)) {
            D_004847A8 = D_0047D35C;
            D_004847A0 = 2;
        }
        UiSetWidgetColor_2905b0(D_004846E8, id,
                    D_004847A8, D_004847A8, D_004847A8, -1.0f);
        break;
    case 2:
        v = D_004847A8 - D_0047D94C;
        id = D_004847A4 + 0x754F;
        D_004847A8 = v;
        if (v <= 1.0f) {
            D_004847A8 = 1.0f;
            UiFadeWidgetAlpha_290690(D_004846E8, id, 0.0f, D_0047DA20, -1.0f);
            D_004847A0 = 3;
        }
        UiSetWidgetColor_2905b0(D_004846E8, id, D_004847A8, D_004847A8, D_004847A8, -1.0f);
        UiGetWidgetAlpha_290770(D_004846E8, id);
        break;
    case 3:
        normal_TransMenuTopRowsSlideOut_515b20(0);
        UiGetWidgetPos_2910a0(D_004846E8, 0x753B, &s3c, &s38);
        UiSetWidgetPos_290f60(D_004846E8, 0x7544, 0, D_004847A4 * 0x27 + 0x50);
        UiMoveWidgetUniform_290f50(D_004846E8, 0x7544, 0, 0, D_0047D9A8, 0);
        UiFadeWidgetColor_2904e0(D_004846E8, 0x7544, 1.0f, 1.0f, 1.0f, 1.0f, D_0047D9A8);
        D_004847A0 = 4;
        break;
    case 4:
        UiGetWidgetPos_2910a0(D_004846E8, 0x7544, &s34, &s30);
        n = D_004847A4;
        if (n == 0) {
        UiSetWidgetsVisibleById_291110(D_004846E8, 0x7531, 1, 1);
        UiFadeWidgetAlpha_290690(D_004846E8, 0x7531, 1.0f, D_0047DA1C, -1.0f);
        UiFadeWidgetAlpha_290690(D_004846E8, 0x75D1, 0.0f, D_0047DA24, -1.0f);
        } else if (!(n != 2 && n != 3)) {
        ev = GetMapMgr_201a90();
        if (ev != NULL) {
            s2c = 0;
            MapSlotsFindBlockById_1e49b0(ev, ent->f18->f30, &s2c);
            if (s2c != 0) {
                if (MinimapFindForArea_1dcb50(s2c) != 0) {
                    pl = GetMinimapMgr_201a70();
                    if (pl != NULL) {
                        MinimapMgrFadeOutStart_321e60(pl, 15.0f);
                    }
                }
            }
        }
        UiFadeWidgetAlpha_290690(D_004846E8, 0x75D1, 0.0f, D_0047DA24, -1.0f);
        }
        if ((f32)s30 <= 0.0f) {
            normal_TransMenuPickIconCopy_515950(D_004847A4);
            UiSetWidgetPos_290f60(D_004846E8, 0x7553, 0x30, 0xF);
            UiSetWidgetColor_2905b0(D_004846E8, 0x7553, 0.0f, 0.0f, 0.0f, 0.0f);
            D_004847A8 = 0.0f;
            D_004847A0 = 7;
        }
        break;
    case 5:
        v = D_004847A8 + D_0047D94C;
        D_004847A8 = v;
        if (!(v < D_0047D35C)) {
            D_004847A8 = D_0047D35C;
            D_004847A0 = 6;
        }
        UiSetWidgetColor_2905b0(D_004846E8, 0x7553,
                    D_004847A8, D_004847A8, D_004847A8, 1.0f);
        UiFadeWidgetAlpha_290690(D_004846E8, 0x7553, 1.0f, D_0047DA28, -1.0f);
        break;
    case 6:
        v = D_004847A8 - D_0047D94C;
        D_004847A8 = v;
        if (v <= 1.0f) {
            D_004847A8 = 1.0f;
            D_004847A0 = 7;
        }
        UiSetWidgetColor_2905b0(D_004846E8, 0x7553,
                    D_004847A8, D_004847A8, D_004847A8, 1.0f);
        break;
    }
    return 0;
}
