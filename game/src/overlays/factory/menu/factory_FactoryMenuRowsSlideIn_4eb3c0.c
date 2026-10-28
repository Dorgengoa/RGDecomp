/* rgp:protos */
#define RGP_SELF_factory_FactoryMenuRowsSlideIn_4eb3c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004EB3C0 -- slide the eight menu rows out, staggering
 * each row's start time and nudging the selected one across.
 * 184 bytes, 46 instructions, 2 conditional branches, 17 calls.
 *
 * * TWIN of `factory_FactoryMenuRowsSlideOut_4eb320` at ratio 0.841 -- the slide-IN, which
 * swaps which of the two calls carries the nudge and turns the `msub.s` into
 * a `madd.s`.  This one also parks the whole panel first.
 *
 * * `andi $5, $2, 0xFFFF` at both call sites is the CALLEE's `u16` parameter,
 * not a source-level mask.
 *
 * * `adda.s $f0, $f1` + `madd.s $f12, $f3, $f2` is the contraction of
 * `base - step * (f32)i`, with `mtc1 $0, $f0` supplying `adda.s`'s second
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
extern f32    D_0047D248;                       /* _gp - 0x7F28 */
extern f32    D_0047D514;                       /* _gp - 0x7C5C */

/*rgp*/
/*rgp*/

void factory_FactoryMenuRowsSlideIn_4eb3c0(void)
{
    s32 i;
    s32 d;

    UiSetWidgetPos_290f60(D_00484A44->f64, 3, 0, 0);
    for (i = 0; i < 8; i++) {
        d = 0;
        if (D_00484A90 == i) {
            d = d + 0xF;
        }
        UiSetWidgetPos_290f60(D_00484A44->f64, i + 4, -0xAA, 0);
        UiMoveWidgetUniform_290f50(D_00484A44->f64, i + 4, d, 0, D_0047D248 - D_0047D514 * (f32)i, 0
);
    }
}
