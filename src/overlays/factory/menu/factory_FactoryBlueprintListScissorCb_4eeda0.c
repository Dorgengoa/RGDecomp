#include "types.h"

/* factory.bin overlay, 0x004EEDA0 -- set the scissor rect, clipped or full.
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
 * * TWIN of the PARKED `factory_FactoryMaterialGridScissorCb_4edda0` at ratio 0.850: the same scissor
 * helper reading a DIFFERENT camera global (`_gp - 0x728`, fields 0xA8..0xB4)
 * with +0x3A/+0x39 origins, and with no `func_290FC0` scroll query, so it has
 * no stack locals and a 0x40 frame instead of 0x50.
 *
 * ***** THE FINAL `or`'s OPERAND ORDER IS BOUGHT BY A NAMED `s64` LOCAL FOR THE
 * LOW THREE TERMS.  Retail is `or $6, $3, $2` and every GROUPING of the four
 * terms gives `or $6, $2, $3` -- eight groupings, all 1 bad at the same word,
 * which is exactly the residue that has kept `004EDDA0` parked since session 6.
 * Splitting `lo = (y0<<32) | (x0 | x1<<16)` out into its own statement and
 * writing `lo | (y1<<48)` reaches it on the first try, and so does hoisting the
 * HIGH term instead, or writing the high term's arithmetic out inline.  A named
 * `s64` for the high term ALONE does NOT (still 1 bad): what matters is that the
 * accumulated low half exists as a value before the last `|` is written.
 */

typedef struct Cam {
    u8  pad000[0xA8];
    s32 fA8;
    s32 fAC;
    s32 fB0;
    s32 fB4;
} Cam;

extern Cam *D_00484A48;                         /* _gp - 0x728 */

extern void func_13F730(void *g, s32 a);
extern void func_13EC80(void *g, s32 a, s64 rect);
extern void func_13F5B0(void *g);
extern s32  func_15DE80(void);
extern s32  func_1451E0(s32 h);
extern s32  func_1451D0(s32 h);

s32 factory_FactoryBlueprintListScissorCb_4eeda0(void *g, s32 b, s32 c, s32 d, s32 clip)
{
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
        x0 = D_00484A48->fA8 + 0x3A;
        y0 = D_00484A48->fAC + 0x39;
        x1 = x0 + (D_00484A48->fB0 + 1);
        y1 = y0 + (D_00484A48->fB4 + 1);
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
