#include "types.h"

/* insmenu 0x004F6E40 (132 bytes, 33 instructions) -- the unprefixed sibling of
 * insmenu_InsectVsLoadSlotCursorBob_4f6810: same bump/measure/place shape, but it drives its own
 * gp counter (gp - 0xDF4 = D_0048437C), an 8.0f lift instead of 6.0f, the
 * overlay's own screen D_004FA180, and it only ever takes the fade-in arm.
 *
 * The name carries no insmenu_ prefix because config/insmenu.symbols.txt
 * appends it (line 383) after the generated block; 0x004F6E40 is below the
 * header-declared text end 0x004F9780, so this is real .text, not a ctor thunk
 * living in .data.
 *
 * ★ D_004FA180 is an incomplete array so it stays OUT of small data and costs
 *   the %hi/%lo pair retail emits; D_0048437C is a 4-byte extern and therefore
 *   gp-relative.
 * ★ The product feeds cvt.w.s directly -- do not name it in a local.
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

extern const u8 D_004FA180[];
extern f32 D_0048437C;          /* gp - 0xDF4 */

extern void func_28B630(f32 *p, f32 v);
extern f32  func_128FD0(f32 x);
extern void func_28ECD0(void *a, s32 *b, s32 *c, s32 d, s32 e);
extern void func_290F50(const void *a, s32 a2, s32 x, s32 y, s32 e, f32 t);

s32 insmenu_InsectVsSaveConfirmBobCb_4f6e40(void *obj)
{
    s32 x;
    s32 y;

    func_28B630(&D_0048437C, 0.0785398163f);
    func_28ECD0(obj, &x, &y, (s32)(8.0f * func_128FD0(D_0048437C)), 0);
    func_290F50(D_004FA180, 0x62, x, y, 0, 1.0f);
    return 1;
}
