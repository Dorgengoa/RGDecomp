/* rgp:protos */
#define RGP_SELF_normal_FieldHudPanelHealGlowUpdate_4f2d50 1
#include "port/game_protos.h"
#line 1
/* SESSION 46 (2026-09-07, SOLO): CLOSED, 124/124 words BYTE-IDENTICAL, on ONE
 * TOKEN -- the three tail accesses `w->f33C[(u32)i]` became `w->f33C[(s32)i]`.
 * `i` is ALREADY `s32`, so this is an IDENTITY cast, and it is not cosmetic:
 * it splits the address CSE.  With the SAME cast spelling in the head and the
 * tail mwcc computes `w + i*8` ONCE and keeps it in a SEVENTH callee-saved
 * register ($22) across both calls; retail uses only $16-$21 and
 * REMATERIALISES `sll $4,$18,3 / addu $4,$20,$4` after `func_2905B0` returns,
 * because that temp is caller-saved.  Writing a DIFFERENT (even identity)
 * cast on the two sides makes mwcc treat them as two expressions and it
 * rematerialises exactly like retail.  Extends
 * [[levers.d/mwcc-index-cast-defeats-cse]]: the lever is the DIFFERENCE
 * between the two spellings, not `(u32)` in particular.
 * Same phenomenon as normal_MenuBattleEndLevelUpLabelUpdate_4ea3f0's WIDGET macro (s45), reached from
 * the other side.
 * ⚠ MEASURED: `tail_i` (plain `i`), `head_i`, `ph_i_only`, `f_i_only` and
 * `all_i` are ALL one word SHORT (0x1ec vs 0x1f0) -- only `(s32)i` in the
 * TAIL is right; the head must keep `(u32)i`.
 * ⚠ The prologue tell that named the defect: ours saved SEVEN callee-saved
 * registers (sq s6..s0, frame 160) where retail saves SIX (frame 144).
 * COUNT THE `sq`s BEFORE READING THE BAD COUNT. */
/* SESSION 31 (combined six-deck sweep, 31,338 arms over 98 units).
 * Installed arm `D_i_at02_dec` from the whole-list declaration sweep (mkdeck31.py)
 *   before: 124 words, 116 bad   after: 124 words, 115 bad   (retail 124 words)
 * Every line BELOW this note predates that install -- read its numbers
 * as the state at the time it was written, not as the current score.
 * Re-score with build/wf-normal/s31/nscore.py, not dv_osbuild.py.
 * KEEP OUT OF config/ocunits/normal.txt. */
#include "types.h"
/* normal 0x004F2D50 -- per-slot flash/pulse pass on the formation panel.
 * For every live slot: re-place its 0x310-byte widget at the panel's current
 * anchor, feed the slot's own phase through func_128FD0, tint the sprite from
 * the two flag bits, then advance the phase by 1/60 and retire the slot when
 * it reaches 1.0.
 *
 * Shares normal_FieldHudReshowMaybe_4f7a00's Obj: `A8 f33C[]` at 0x33C, stride 8, and the
 * gp `T310 *D_00484414` widget table.  Here f33C[i].f0 is read with `lwc1`,
 * so it is an f32 phase, not the s32 that 004f7a00 declares.
 *
 * The 12-byte byte-clear at sp+0x78 that NULL-CHECKS its own address is
 * [[mwcc-array-initialiser-clear-loop]]: it is `f32 v[3] = {0};` in a BLOCK
 * opened after func_128FD0 returns, not a hand loop.  The frame confirms it --
 * the two function-scope s32 sit at 0x8C/0x88 and the block-scoped array lands
 * 16 bytes below them at 0x78, exactly the "function-scope locals first, at
 * the high addresses" layout that lever records.
 *
 * gp -0x7F74 / -0x7864 / -0x7FA0 are D_0047D1FC (pi), D_0047D90C (0.9) and
 * D_0047D1D0 (0.0166666675 = 1/60).  D_0047D1D0 is inside mwcc's .lit4 pool
 * (0x0047D1D0-0x0047D7FF) so the literal spelling is the other arm, but this
 * scorer has no .lit4 retarget and would read it as a bad word. */

typedef struct A8   { f32 f0; s16 f4; s16 f6; } A8;
typedef struct T310 { u8 pad000[0x310]; } T310;

typedef struct Obj {
    u8 pad000[0x33C];
    A8 f33C[1];
} Obj;

extern T310 *D_00484414;          /* gp - 0xD5C  */
extern f32   D_0047D1FC;          /* gp - 0x7F74 : 3.141592741 */
extern f32   D_0047D90C;          /* gp - 0x7864 : 0.8999999762 */
extern f32   D_0047D1D0;          /* gp - 0x7FA0 : 0.01666666754 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void normal_FieldHudPanelHealGlowUpdate_4f2d50(Obj *w)
{
    s32 n;
    u16 id;
    s32 i;
    f32 f;
    f32 t;
    s32 x;
    s32 y;
    s16 *fl;
    f32 *ph;

    if (GetGameData_1fede0() != 0) {
        n = normal_FieldHudPartyRowCount_4f9c50();
        for (i = 0; i < n; i++) {
            fl = &w->f33C[i].f4;
            if (w->f33C[i].f4 != 0) {
                id = i * 7 + 6;
                UiGetWidgetPos_2910a0(w, id, &x, &y);
                if (D_00484414 != 0) {
                    UiGlowSpriteListUpdate_33bb30(&D_00484414[i], x, y);
                }
                ph = &w->f33C[(u32)i].f0;
                f = Sinf_128fd0(D_0047D1FC * w->f33C[(u32)i].f0);
                {
                    f32 v[3] = {0};

                    if (*fl & 1) {
                        v[0] = 1.0f;
                        v[1] = D_0047D90C + f;
                        v[2] = 1.0f;
                    }
                    if (*fl & 2) {
                        v[0] = 1.0f;
                        v[1] = 1.0f;
                        v[2] = D_0047D90C + f;
                    }
                    if (*fl & 3) {
                        v[0] = D_0047D90C + f;
                        v[1] = v[0];
                        v[2] = v[0];
                    }
                    UiSetWidgetColor_2905b0(w, id, v[0], v[1], v[2], -1.0f);
                }
                t = w->f33C[(s32)i].f0 + D_0047D1D0;
                w->f33C[(s32)i].f0 = t;
                if (t >= 1.0f) {
                    w->f33C[(s32)i].f6 = -1;
                    *fl = 0;
                    *ph = 0.0f;
                }
            }
        }
    }
}
