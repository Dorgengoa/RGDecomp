#include "types.h"

/* insmenu 0x004F6740 -- BYTE-IDENTICAL (lane L2, 2026-08-26), 29 words,
 * scored by build/dv_osbuild.py against retail/BIN/INSMENU.BIN.
 * No `.lit4`; safe to merge into config/ocunits/insmenu.txt as-is.
 *
 * Retail branches INTO the body and lets `b <epilogue> / daddu $2, $0, $0`
 * be the fall-through, so the source is the INVERTED EARLY RETURN.
 * `D_00484388 = 1;` written BEFORE the call fills that call's delay slot,
 * and the 1 it stores is the same 1 the call takes.
 *
 * * THE RESIDUE WAS THE `const`.  Parked at 3 words because mwcc HOISTED the
 * `lw %lo(D_004FA1BC)($2)` above BOTH frame saves; retail is
 *     lui $2,%hi / sd $31 / sq $16 / lw $2,%lo($2)
 * A `const` extern is a known-constant load with no alias hazard, so the
 * scheduler is free to lift it into the prologue -- the exact mirror of the
 * `.lit4` hoist that closed 004f8560 / 004eb190 / 004ee610 in the same batch,
 * read from the other side.  Declaring it NON-const, and larger than 8 bytes
 * so it stays OUT of small data and still gets %hi/%lo, pins the load at its
 * use.  3 -> 0.
 *
 * Measured negatives in the same sweep (build/vs_im02_f6740.py, 12 arms,
 * 6 INERT, 6 live): `const volatile` (inert), plain `volatile` (live, 0x70 vs
 * 0x74 -- one word SHORT), `const s32 [4]`, `const volatile s32 [4]`, a const
 * struct, the global read inline in the guard, `u32`, naming the object
 * parameter, and the non-inverted `if ((f & 1) == 0) { ... }` form (21 bad).
 * Every one of them is still 3 or worse.  `volatile` is NOT the lever here.
 */
typedef struct {
    u8 pad00[0x12];
    s16 field12;
} Widget;

extern s32 D_004FA1BC[4];
extern const u8 D_004FA1A0[];
extern u8 D_00484388;       /* gp - 0xDE8 */
extern void func_376B10(s32 a);
extern void insmenu_InsectVsSavePortSelectDraw_4f6bf0(s32 a);
extern void insmenu_InsectVsLoadPortCursorBob_4f68d0(s32 a, s32 b, s32 c);
extern void func_28EA90(const void *ctx, s32 id, s32 a);

s32 insmenu_InsectVsLoadPortConfirmCb_4f6740(Widget *o)
{
    s32 f;

    f = D_004FA1BC[0];
    if ((f & 1) != 0) {
        return 0;
    }
    D_00484388 = 1;
    func_376B10(1);
    insmenu_InsectVsSavePortSelectDraw_4f6bf0(o->field12);
    insmenu_InsectVsLoadPortCursorBob_4f68d0(o->field12, 0, 0);
    func_28EA90(D_004FA1A0, 0x88BA, 0);
    return 1;
}
