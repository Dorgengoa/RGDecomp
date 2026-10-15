#include "types.h"
/* insect 0x004F52A0 -- 388 bytes, 97 instructions, 16 calls, 5 conditional
 * branches, br/ins 0.052.  From x_band.py's branch-light band.
 *
 * `swc1 $f20, 0x0($29)` / `lwc1 $f20, 0x0($29)` around the whole body is the
 * callee-saved FP register mwcc takes when a float local is live across a
 * call; nothing in the source asks for it.
 *
 * The two byte-clear loops are written OUT, not memset: each is a null test on
 * a frame address that mwcc cannot fold away, then a `sb`/decrement/increment
 * do-while.  The two hazard `nop`s inside each loop are mwcc's, not source.
 *
 * `lui $2, 0x42C0` + `mtc1` (and not an `lwc1` from a pool) is how mwcc
 * materialises a float constant whose low half is zero, so the scale is the
 * literal 96.0f; `cvt.w.s` disassembles as a `.word` because the R5900's
 * conversion is not IEEE (subsystem-decomp-track).
 *
 * The counter is UNSIGNED.  `s32 n` with the same `while (n != 0)` gives
 * `bgtz` at both loop bottoms where retail has `bnez` -- mwcc proves a signed
 * countdown non-negative and takes the cheaper test.  `u32 n`, or a signed
 * `while (--n != 0)`, both give `bnez`; all three spellings are one object.
 *
 * `o->fC0` is REMATERIALISED at both its sites and `$16` holds the handle, so
 * the member stays inline and only the handle is a local.
 */

typedef struct Pt {
    s32 x;                          /* +0x00 */
    s32 y;                          /* +0x04 */
    s32 z;                          /* +0x08 */
    s32 w;                          /* +0x0C */
} Pt;

typedef struct Ins {
    u8    pad000[0xC0];
    s32   fC0;                      /* +0x00C0 */
    u8    pad0C4[0x880 - 0xC4];
    void *f880;                     /* +0x0880 */
    u8    pad884[0x5DA0 - 0x884];
    s32   f5DA0;                    /* +0x5DA0 */
    s32   f5DA4;                    /* +0x5DA4 */
} Ins;

extern void func_13E2F0(s32 c, s32 a);
extern void func_13E3B0(s32 c, s32 a);
extern void func_13E400(s32 c, s32 a);
extern void func_13E460(s32 c, s32 a);
extern void func_13E4C0(s32 c, s32 a, s32 b);
extern void func_13E4D0(s32 c, s32 a);
extern void func_13E4F0(s32 c, s32 a);
extern void func_13E500(s32 c, s32 a);
extern void func_13EE40(s32 c, s32 a, s32 b, s32 d, s32 e);
extern void func_13F110(s32 c, s32 a, s32 b, s32 d);
extern void func_13F5B0(s32 c);
extern void func_13F730(s32 c, s32 k);
extern void func_141A20(s32 k);
extern s32  func_141B00(s32 k);
extern f32  func_290770(void *h, s32 id);

void insect_InsectBattleDrawDimOverlay_4f52a0(Ins *o)
{
    Pt   a;
    Pt   b;
    u8  *p;
    u32  n;
    s32  c;
    f32  v;
    void *h;

    h = o->f880;
    if (h != 0) {
        v = func_290770(h, 0x75F8);
        c = func_141B00(o->fC0);
        func_13E500(c, 1);
        func_13E4F0(c, 1);
        func_13E4C0(c, 6, 0);
        func_13E4D0(c, 1);
        func_13E460(c, 0);
        func_13E2F0(c, 0);
        func_13E3B0(c, 1);
        func_13E400(c, 0);
        func_13F730(c, 6);
        p = (u8 *)&a;
        n = 0x10;
        if (p != 0) {
            do {
                *p = 0;
                n--;
                p++;
            } while (n != 0);
        }
        p = (u8 *)&b;
        n = 0x10;
        if (p != 0) {
            do {
                *p = 0;
                n--;
                p++;
            } while (n != 0);
        }
        b.x = o->f5DA0;
        b.y = o->f5DA4;
        func_13EE40(c, 0x10, 0x10, 0x10, (s32)(96.0f * v));
        func_13F110(c, a.x, a.y, 0);
        func_13F110(c, b.x, b.y, 0);
        func_13F5B0(c);
        func_141A20(o->fC0);
    }
}
