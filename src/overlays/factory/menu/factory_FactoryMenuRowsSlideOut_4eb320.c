#include "types.h"

/* factory.bin overlay, 0x004EB320 -- slide the eight menu rows in, staggering
 * each row's start time and nudging the selected one across.
 * 148 bytes, 37 instructions, 2 conditional branches, 16 calls.
 *
 * * TWIN of `factory_FactoryMenuRowsSlideIn_4eb3c0` at ratio 0.841 -- the slide-OUT, which
 * swaps which of the two calls carries the nudge and turns the `madd.s` into
 * an `msub.s`.
 *
 * * `andi $5, $2, 0xFFFF` at both call sites is the CALLEE's `u16` parameter,
 * not a source-level mask.
 *
 * * `adda.s $f0, $f1` + `madd.s $f12, $f3, $f2` is the contraction of
 * `base + step * (f32)i`, with `mtc1 $0, $f0` supplying `adda.s`'s second
 * operand.
 *
 * * `D_00484A90` is RE-READ every iteration: the `bnel`'s delay slot holds the
 * same `lw $2, -0x6E0($28)` that sits at the loop head, so it is the body's
 * first statement and not a named local.
 */

typedef struct Scene {
    u8    pad00[0x64];
    void *f64;
} Scene;

extern Scene *D_00484A44;                       /* _gp - 0x72C  */
extern s32    D_00484A90;                       /* _gp - 0x6E0  */
extern f32    D_0047D4F0;                       /* _gp - 0x7C80 */
extern f32    D_0047D514;                       /* _gp - 0x7C5C */

extern void func_290F50(void *w, u16 id, s32 a, s32 b, s32 c, f32 t);
extern void func_290F60(void *w, u16 id, s32 x, s32 y);

void factory_FactoryMenuRowsSlideOut_4eb320(void)
{
    s32 i;
    s32 d;

    for (i = 0; i < 8; i++) {
        d = 0;
        if (D_00484A90 == i) {
            d = d + 0xF;
        }
        func_290F60(D_00484A44->f64, i + 4, d, 0);
        func_290F50(D_00484A44->f64, i + 4, -0xAA, 0, 0,
                    D_0047D4F0 + D_0047D514 * (f32)i);
    }
}
