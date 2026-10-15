/* MATCH -- byte-identical (session 19, lane r2d).  CLOSED by
 * [[mwcc-float-literal-pool]]: D_0047D288 / D_0047D248 / D_0047D354 are POOL
 * LITERALS 0.6f / 0.7f / 1.2f, not gp externs.  The recorded park -- "retail
 * interleaves the two gp float loads among the +0x388..+0x396 stores and keeps
 * the call's argument setup LAST" with an eight-statement-order ladder
 * bottoming out at 8 -- was that ladder swept with the EXTERN spelling held
 * fixed.  With the literals the loads hoist freely and the whole store/load
 * group falls into retail's order.  8 bad -> MATCH, no statement reordered.
 * Carries a `.lit4`; n_olink.py:375 retargets it.  Bare dv_osbuild reads 5 bad
 * -- the un-retargeted displacement, not a defect. */
#include "types.h"
/* normal 0x004F1030 -- one-shot build of the 0x55..0x59 gauge cluster.  Both
 * guards are INVERTED early returns: retail branches INTO the body and lets
 * the exit fall through (guard 1) / carries the result in a `bgtzl` delay slot
 * (guard 2).  `lui`+`ori` is mwcc materialising an UNSIGNED constant. */

typedef struct Obj {
    u8   pad000[0x378];
    s16  f378;
    u8   pad37A[0x384 - 0x37A];
    s8   f384;
    u8   pad385[1];
    s16  f386;
    s32  f388;
    f32  f38C;
    s32  f390;
    s16  f394;
    s16  f396;
} Obj;

extern void *D_00481BBC;          /* gp - 0x35B4 */

extern s32  func_28AA30(void *a, s32 id);
extern void func_28F510(Obj *p, s32 id, s32 c, s32 d);
extern void func_291110(Obj *p, s32 id, s32 c, s32 d);
extern void func_290F60(Obj *p, s32 id, s32 c, s32 d);
extern void func_2907A0(Obj *p, s32 id, f32 x);
extern void func_290850(Obj *p, s32 id, u32 rgba, s32 d, f32 x);
extern void func_290F50(Obj *p, s32 id, s32 c, s32 d, s32 e, f32 x);

s32 normal_FieldHudBtlEscOpen_4f1030(Obj *p, s8 mode)
{
    f32 a;
    f32 b;

    if (p->f378 == 0) {
        return 0;
    }
    if (p->f386 <= 0) {
        p->f386 = 1;
        p->f384 = mode;
        func_28F510(p, 0x56, func_28AA30(D_00481BBC, 0x4B), 0);
        func_28F510(p, 0x58, func_28AA30(D_00481BBC, 0x4C), 0);
        func_28F510(p, 0x59, func_28AA30(D_00481BBC, 0x4D), 0);
        func_291110(p, 0x55, 1, 1);
        func_290F60(p, 0x55, 0x200, 0xE2);
        func_2907A0(p, 0x55, 1.0f);
        func_2907A0(p, 0x57, 0.6f);
        /* The minimum of the eight-order ladder recorded at the top. */
        p->f388 = 0;
        p->f394 = 0;
        p->f396 = 0;
        a = 0.6f;
        p->f38C = a;
        b = 0.7f;
        p->f390 = 0;
        func_290850(p, 0x56, 0xFF606060, 0, b);
        func_290850(p, 0x58, 0xFF606060, 0, p->f38C);
        func_290850(p, 0x59, 0xFF606060, 0, p->f38C / 1.2f);
        func_290F50(p, 0x55, 0x13B, 0xE2, 0, 0.6f);
    }
    return 1;
}
