/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsLoadSlotCursorBob_4f6810 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004F6810 (184 bytes, 46 instructions) -- the caption placer for a
 * caller-supplied screen handle.  Structurally the twin of the already-matched
 * insmenu_InsectVsLoadPortCursorBob_4f68d0, minus the show/hide guard: bump the shared eased
 * counter, measure the widget, then either SET (func_290F60) or FADE IN
 * (func_290F50 at full alpha) the caption at id 0x890D.
 *
 * ★ The 6.0f multiply feeds cvt.w.s DIRECTLY (mul.s $f0,$f1,$f0 then
 *   cvt.w.s $f0,$f0), so unlike 004f68d0 the product is NOT named in a local
 *   -- 004f68d0 keeps it in the callee-saved $f20 precisely because it is
 *   reused after the measure call, and this one is not.
 * ★ `mtc1 $2,$f12` off `lui 0x3F80` is the literal 1.0f.
 * ★ Both arms converge on `addiu $2,$0,1`, so the single `return 1` is at the
 *   end of the function, not inside the arms.
 * !! MERGE PRECONDITION -- LINK PLUMBING, NOT MATCHING.
 * This unit writes a FLOAT LITERAL (0.0785398163f), so mwcc emits a `.lit4`
 * section with an `@N` symbol and a GPREL16 relocation into it.  The four
 * bytes already exist in MAIN at 0x0047D3B8, and the overlay cannot reach its
 * own data through main's $gp, so the reference must be pre-relocated to the
 * retail pool address and the relocation neutralised -- exactly what
 * scripts/t_lit4.py does for TITLE and what scripts/t_olink.py calls at
 * line 397.  scripts/i_olink.py HAS NO SUCH CALL (grep: zero hits for lit4).
 *
 * Measured, this run, from a cold build/obj-im06:
 *   build/dv_oslit_im06.py (lit4-aware)  ->  MATCH   lit4:ok/1
 *   build/dv_osbuild.py    (plain)       ->  1 bad   "defined in this
 *                                                     object's .lit4"
 * So this source is BYTE-IDENTICAL, but admitting it to
 * config/ocunits/insmenu.txt BEFORE i_olink.py gets t_olink.py's lit4 call
 * would put one wrong word into INSMENU.BIN.  Port the call first.
 *
 * The extern spelling (`extern f32 D_0047D3B8;`) links today and is TWO bad
 * words -- the gp `lwc1` schedules after the callee-saved `sq` instead of
 * before it.  That residue survived 7 local-naming arms, 25 pragmas, the
 * const-qualification arm, the float-first argument order and the local
 * declaration order (all measured, this session); the literal spelling is the
 * only thing that moved it.
 */

extern f32 D_0048434C;          /* gp - 0xE24 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 insmenu_InsectVsLoadSlotCursorBob_4f6810(void *obj, const void *scr, s32 place)
{
    s32 x;
    s32 y;

    PhaseAdvanceWrapPi_28b630(&D_0048434C, 0.0785398163f);
    GetGridCellPosOffset_28ecd0(obj, &x, &y, (s32)(6.0f * Sinf_128fd0(D_0048434C)), 0);
    if (place) {
        UiSetWidgetPos_290f60(scr, 0x890D, x, y);
    } else {
        UiMoveWidgetUniform_290f50(scr, 0x890D, x, y, 1.0f, 0);
    }
    return 1;
}
