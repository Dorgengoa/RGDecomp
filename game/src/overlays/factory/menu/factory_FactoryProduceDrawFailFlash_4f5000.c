/* rgp:protos */
#define RGP_SELF_factory_FactoryProduceDrawFailFlash_4f5000 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004F5000 -- 101 words, EXACT LENGTH, 3 bad.  PARKED.
 * Session 23, lane fz23a.
 *
 * RESIDUE 0x004F5114/0x004F5118/0x004F5120 -- a two-load ORDER swap:
 *   ours   C6020068 lwc1 $f2,0x68($16) / C601006C lwc1 $f1,0x6C($16)
 *          46011041 sub.s $f1,$f2,$f1
 *   retail C602006C lwc1 $f2,0x6C($16) / C6010068 lwc1 $f1,0x68($16)
 *          46020841 sub.s $f1,$f1,$f2
 * Both compute f68 - f6C and in both `fs` is the LEFT operand; mwcc numbers
 * the fp temps by BIRTH ($f2, then $f1, then $f0 for the gp `k`).  Retail's
 * FIRST-born load is o->f6C, ours is o->f68.  So the whole residue is "which
 * member is evaluated first"; `u = o->f6C` is a single-use local and mwcc
 * SINKS it into the expression, where it is evaluated second.
 *   MEASURED INERT (byte-identical to the baseline object):
 *     `u = o->f6C; t = o->f68; t = t - u;`  (mwcc folds the split back)
 *     `t = o->f68 - o->f6C;` with `u` deleted entirely
 *   LENGTH-BREAKING: `o->f68 -= o->f6C; ... if (o->f68 <= k)` costs +1 word
 *     (0x198 vs 0x194) -- mwcc RE-LOADS o->f68 for the compare instead of
 *     forwarding the register.  Reverted to the snapshot.
 *   NOT YET TRIED: any spelling that gives `u` a SECOND use without adding a
 *   word (the `o->f6C * -1.0f` body deliberately RE-LOADS f6C in retail, so
 *   feeding it `u` breaks the body instead).
 */

typedef struct A {
    u8  pad00[0x68];
    f32 f68;
    f32 f6C;
    u8  pad70[0x2];
    u8  f72;
} A;

extern f32 D_0047D288;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void factory_FactoryProduceDrawFailFlash_4f5000(A *o)
{
    void *a;
    void *b;
    f32   t;
    f32   k;

    if (o->f72 == 7) {
        a = GetDrawCtx_15de80();
        b = DrawListBeginPrim_141b00(a);
        GsPktSetAlphaBlend_13e500(b, 1);
        GsPktSetBlendMode_13e4f0(b, 1);
        GsPktEnableAlphaTest_13e4d0(b, 1);
        GsPktSetAlphaTestFunc_13e4c0(b, 1, 0);
        GsPktEnableZTest_13e460(b, 0);
        GsPktSetZWriteMask_13e430(b, 1);
        GsPktSetTexFilter_13e3d0(b, 0);
        GsPktSetTextured_13e400(b, 0);
        GsPktOpenPrim_13f730(b, 6);
        GsPktSetRGBAQ_13ee40(b, 0x80, 8, 8, (s32)(32.0f * o->f68));
        GsPktSetXYZPixel_13f110(b, 0, 0, 0);
        GsPktSetXYZPixel_13f110(b, 0x200, 0x1C0, 0);
        GsPktClose_13f5b0(b);
        DrawListEndPrim_141a20(a);
        t = *(volatile f32 *)&o->f6C;
        t = o->f68 - t;
        k = D_0047D288;
        o->f68 = t;
        if (t <= k) {
            o->f6C = o->f6C * -1.0f;
        }
        if (!(o->f68 < 1.0f)) {
            o->f6C = o->f6C * -1.0f;
        }
    }
}
