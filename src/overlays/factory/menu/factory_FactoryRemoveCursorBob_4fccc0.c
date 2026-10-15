#pragma optimization_level 3

#include "types.h"

/* factory.bin overlay, 0x004FCCC0 -- 272 bytes / 68 words, 5 branches,
 * 4 calls.  Advance the parts-dialog swing angle by one step and re-place the
 * cursor sprite at the swung position.
 *
 * * Same `Dlg` container as `factory_FactoryRemoveDialogOpen_4fcee0` (`f60` the `f32` angle,
 *   `f64` the `u8` state, `f6C` the widget handle).
 * ** #pragma optimization_level 3 IS THE KEY, and it is the `||` lever
 *    ([[factory board]], and factory_FactoryRemoveSelChanged_4fcdd0 in this same lane).  At -O4
 *    mwcc range-folds `(st==1)||(st==2)||(st==3)` into `addiu ..,-1 / sltiu`;
 *    at -O3 the short-circuit chain survives -- `beq 1` / `beql 2` INTO the
 *    body, `bnel != 3` PAST it -- which is the only shape whose LAST test is
 *    inverted.  Every `switch` spelling (ascending cases, descending cases,
 *    body outside via `case 1: break; default: return;`) branches INTO the
 *    last arm instead and is TWO WORDS long.  `lwc1 $f2, 0x60($17)` duplicated
 *    into the `beql` delay slot and again at the join label is the tell that
 *    the three tests share one body.
 * * `-0x7DA0($28)` and `-0x7D84($28)` are 0x0047D3D0 and 0x0047D3EC inside
 *   mwcc's `.lit4` POOL; the overlay has no literal-pool reloc retarget, so
 *   they must be `extern f32` gp objects, not written-out literals
 *   ([[mwcc-float-literal-pool]], and factory_FactoryRemoveDialogOpen_4fcee0's own residue).
 * * `mul.s $f20` into a CALLEE-SAVED float register is the named-PRODUCT
 *   lever ([[normal-named-product-local]]): naming `6.0f * func_128FD0(..)`
 *   is what keeps the value live across `func_28EA40`, kills the `madd.s`
 *   contraction and gives the bare `cvt.w.s` instead of the IEEE fptosi
 *   sequence.
 * * `mult` and `mult1` are the two EE multiply pipes taking the two
 *   independent products; `addu $4,$5,$6` puts the plain term FIRST.
 * * `func_290F50`'s `f32` rides `$f12` from the separate FP argument file, so
 *   `$8` still carries the SIXTH argument -- the spelling
 *   `factory_FactoryRemoveWaitRequest_4fcc50` records for `func_1B9520`.
 */

typedef struct Pad {
    u8  pad00[0x4];
    s16 f04;
    s16 f06;
    s16 f08;
    s16 f0A;
    u8  pad0C[0x8];
    s16 f14;
    s16 f16;
} Pad;

typedef struct Dlg {
    u8    pad00[0x60];
    f32   f60;
    u8    f64;
    u8    pad65[0x7];
    void *f6C;
} Dlg;

extern f32   D_0047D3D0;                        /* _gp - 0x7DA0 */
extern f32   D_0047D3EC;                        /* _gp - 0x7D84 */
extern void *D_004807EC;                        /* _gp - 0x4984 */

extern f32   func_128FD0(f32 a);
extern Pad  *func_28EA40(void *w, s32 id);
extern void  func_290F60(void *w, s32 id, s32 x, s32 y);
extern void  func_290F50(void *w, s32 id, s32 x, s32 y, f32 g, s32 a);

void factory_FactoryRemoveCursorBob_4fccc0(Dlg *o, s32 flag)
{
    Pad *w;
    f32  a;
    f32  prod;
    s32  x;
    s32  y;

    if ((o->f64 == 1) || (o->f64 == 2) || (o->f64 == 3)) {
    } else {
        return;
    }
    a = o->f60 + D_0047D3D0;
    o->f60 = a;
    if (a > 0.0f) {
        o->f60 = D_0047D3EC;
    }
    prod = 6.0f * func_128FD0(o->f60);
    w = func_28EA40(o->f6C, 0x8912);
    x = (s32)(prod + (f32)(w->f04 + w->f14 * w->f08));
    y = w->f06 + w->f16 * w->f0A;
    if (flag != 0) {
        func_290F60(D_004807EC, 0x97, x, y);
    } else {
        func_290F50(D_004807EC, 0x97, x, y, 0.5f, 0);
    }
}
