#include "types.h"

/* factory.bin overlay, 0x004EDDA0 -- set the scissor rect, clipped or full.
 *
 * ⚠ The guard tests `$8`, the FIFTH integer parameter, and `$5`/`$6`/`$7` are
 * never read: this is the unused-parameter shape recorded in
 * `levers.d/factory-unused-first-parameter.md` seen from the middle of the
 * list.  The arity is fixed by the register the guard reads, not by the body.
 * ⚠ m2c gives `func_13EC80` seven arguments because `$7`..`$10` still hold the
 * rect's own intermediates at the call; the else arm marshals only `$4`/`$5`/
 * `$6`, so the real arity is three.
 *
 * ★ `dsll32 rX, rY, 0` + `dsra32 rX, rX, 0` is the s32 -> s64 sign extension,
 * so the third argument is a 64-bit value assembled with shifts and `|` in the
 * source -- not a by-value struct built on the stack.
 *
 * ⚠⚠ PARKED -- RIGHT LENGTH, ONE BAD WORD, deliberately NOT in
 * `config/ocunits/factory.txt`.  The residue is 0x004EDE58: retail
 * `or $6, $3, $2` against our `or $6, $2, $3` -- the same two registers, the
 * final `|`'s operands swapped.  Eleven groupings measured (both associations
 * of the four terms, four term orders, the balanced 2+2 form -- which is 22
 * words, so grouping DOES reach the code -- a named `s64` local for the high
 * term, and `(s64)(y1 << 16) << 32`, which is one word SHORT).  The floor is 1.
 * This is the commutative-canonicalisation class from [[subsystem-decomp-track]]
 * met on an integer `or`; do not spend more spellings.
 */

typedef struct View {
    u8    pad00[0x40];
    void *f40;
    u8    pad44[0x1C];
    s32   f60;
    s32   f64;
    s32   f68;
    s32   f6C;
} View;

extern View *D_00484A58;                        /* _gp - 0x718 */

extern void func_13F730(void *g, s32 a);
extern void func_290FC0(void *w, s32 id, s32 *x, s32 *y);
extern void func_13EC80(void *g, s32 a, s64 rect);
extern void func_13F5B0(void *g);
extern s32  func_15DE80(void);
extern s32  func_1451E0(s32 h);
extern s32  func_1451D0(s32 h);

s32 factory_FactoryMaterialGridScissorCb_4edda0(void *g, s32 b, s32 c, s32 d, s32 clip)
{
    s32 sx;
    s32 sy;
    s32 x0;
    s32 y0;
    s32 x1;
    s32 y1;
    s32 h;
    s32 w;
    s32 ht;
    s64 lo;

    if (clip != 0) {
        func_13F730(g, 6);
        func_290FC0(D_00484A58->f40, 0x5D, &sx, &sy);
        x0 = D_00484A58->f60 - 0x11 + sx;
        y0 = D_00484A58->f64 - 0x14 + sy;
        x1 = x0 + (D_00484A58->f68 + 1);
        y1 = y0 + (D_00484A58->f6C + 1);
        lo = ((s64)y0 << 32) | ((s64)x0 | ((s64)x1 << 16));
        func_13EC80(g, 0x40, lo | ((s64)y1 << 48));
        func_13F5B0(g);
    } else {
        h = func_15DE80();
        w = func_1451E0(h);
        ht = func_1451D0(h);
        func_13F730(g, 6);
        func_13EC80(g, 0x40, (s64)0 | ((s64)(w - 1) << 16) | ((s64)0 << 32) | ((s64)(ht - 1) << 48));
        func_13F5B0(g);
    }
    return 1;
}
