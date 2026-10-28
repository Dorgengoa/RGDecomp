/* rgp:protos */
#define RGP_SELF_insect_InsectBattleDrawDimOverlay_4f52a0 1
#include "port/game_protos.h"
#line 1
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

void insect_InsectBattleDrawDimOverlay_4f52a0(Ins *o)
{
    Pt   a __attribute__((aligned(16)));
    Pt   b __attribute__((aligned(16)));
    u8  *p;
    u32  n;
    s32  c;
    f32  v;
    void *h;

    h = o->f880;
    if (h != 0) {
        v = UiGetWidgetAlpha_290770(h, 0x75F8);
        c = ((s32)DrawListBeginPrim_141b00(o->fC0));
        GsPktSetAlphaBlend_13e500(c, 1);
        GsPktSetBlendMode_13e4f0(c, 1);
        GsPktSetAlphaTestFunc_13e4c0(c, 6, 0);
        GsPktEnableAlphaTest_13e4d0(c, 1);
        GsPktEnableZTest_13e460(c, 0);
        GsPktSetOriginMode_13e2f0(c, 0);
        GsPktSetGouraud_13e3b0(c, 1);
        GsPktSetTextured_13e400(c, 0);
        GsPktOpenPrim_13f730(c, 6);
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
        GsPktSetRGBAQ_13ee40(c, 0x10, 0x10, 0x10, (s32)(96.0f * v));
        GsPktSetXYZPixel_13f110(c, a.x, a.y, 0);
        GsPktSetXYZPixel_13f110(c, b.x, b.y, 0);
        GsPktClose_13f5b0(c);
        DrawListEndPrim_141a20(o->fC0);
    }
}
