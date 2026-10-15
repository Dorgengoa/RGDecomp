#include "types.h"
/* normal 0x00502150 -- the whole body is gated on the gp object at 0x00484454.
 * `adda.s`/`madd.s` is plain `22.0f + v * (f32)r->f16` ([[ps2-float-accumulator]]);
 * the trailing `lwc1 $f12, -0x7EF8($28)` is the LITERAL 0.8f out of MAIN's
 * `.lit4` pool.  The two out-parameters sit at 0x3C and 0x38 of a 0x40 frame,
 * i.e. TOP-DOWN in declaration order. */
typedef struct Rec {
    u8  pad000[0x12];
    s16 f12;
    u8  pad014[0x2];
    s16 f16;
} Rec;

extern void *D_00484454;          /* gp - 0xD1C */
extern void *D_0048449C;          /* gp - 0xCD4 */

extern void normal_BtlChgPageGetCursorPos_505df0(void *p, s32 *x, s32 *y);
extern s32  normal_BtlChgMenuCursorBob_503750(Rec *r, s32 unused, s32 x, s32 y);
extern f32  normal_BtlChgPageGetScrollStep_505d70(void *p);
extern void normal_BtlChgMenuAbilityNamesRefresh_502e50(s32 a, s32 b, s32 c);
extern void normal_BtlChgMenuAbilityCostsRefresh_503080(void);
extern void normal_BtlChgPageAbilityScrollSettle_504d50(void *p);
extern void func_290F50(void *p, s32 id, s32 c, s32 d, s32 e, f32 x);
extern void func_290F60(void *p, s32 a, s32 b, s32 c);

s32 normal_BtlChgMenuAbilityListCursorBobCb_502150(Rec *r, s32 k)
{
    s32 x;
    s32 y;
    f32 v;

    if (D_00484454 != NULL) {
        normal_BtlChgPageGetCursorPos_505df0(D_00484454, &x, &y);
        normal_BtlChgMenuCursorBob_503750(r, k, x - 0x1F, y - 2);
        v = normal_BtlChgPageGetScrollStep_505d70(D_00484454);
        func_290F50(D_0048449C, 0x1A, 0x31,
                    (s32)(22.0f + v * (f32)r->f16), 0, 0.8f);
        func_290F60(D_0048449C, 4, -0x14, r->f12 * 26 + 0x18);
        normal_BtlChgMenuAbilityNamesRefresh_502e50(5, 3, 0);
        normal_BtlChgMenuAbilityCostsRefresh_503080();
        normal_BtlChgPageAbilityScrollSettle_504d50(D_00484454);
    }
    return 1;
}
