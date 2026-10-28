/* rgp:protos */
#define RGP_SELF_factory_FactoryGridSpanZ_502810 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x00502810 -- turn a world Y coordinate and a part
 * height into the pair of grid rows the part occupies: round the centre row,
 * then report the far edge through `p` and the centre through `q`.
 * 172 bytes, 43 instructions, 2 conditional branches, 1 call.
 *
 * * TWIN of `factory_FactoryGridSpanX_5028c0` at ratio 1.000 -- the X axis, so the origin
 * field is `f2B8` instead of `f2C0`.
 *
 * * `adda.s $f0, $f1` + `msub.s $f12, $f3, $f4` is the CONTRACTION of
 * `q - 0.5f * (f32)(n - 1)`, and `mtc1 $0, $f0` is the 0.0f `adda.s` needs for
 * its second operand.  Naming the product would kill it
 * ([[normal-named-product-local]]); here the contraction is what retail has,
 * so the whole expression stays inline.
 *
 * * `cvt.w.s` + `mfc1` + `dsll32/dsra32 ..,16` is `(s16)` applied to the FLOAT
 * result, one cast and not two.
 *
 * * `n - 1` is computed TWICE -- once for the `cvt.s.w` and once after the
 * call -- because the call clobbers the register; that is rematerialisation,
 * not a second source expression.
 */

typedef struct Obj {
    u8  pad000[0x2A8];
    f32 f2A8;
    u8  pad2AC[0xC];
    f32 f2B8;
    u8  pad2BC[0x4];
    f32 f2C0;
} Obj;

/*rgp*/

void factory_FactoryGridSpanZ_502810(Obj *o, s16 *p, s16 *q, s32 n, f32 v)
{
    s32 r;
    s16 t;

    r = (s16)Floorf_128e30((v - o->f2C0) / o->f2A8 - 0.5f * (f32)(n - 1));
    t = r + (n - 1);
    if (p != 0) {
        *p = t;
    }
    if (q != 0) {
        *q = r;
    }
}
