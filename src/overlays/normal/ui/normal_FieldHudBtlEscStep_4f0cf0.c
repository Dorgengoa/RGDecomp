/* PARKED (session gr11) at RIGHT LENGTH (171 words), 4 bad words.  NOT in
 * config/ocunits/normal.txt.
 * Two levers found and CLOSED here (record for the digest):
 *   - outer `f384` guard polarity is `if (f384 != 0) {A} else {B}`, not
 *     `if (f384 == 0)` -- m2c inverted it; the tell was the `beql` skipping
 *     TO the func_1839F0 dance, i.e. the dance is the ELSE arm.
 *   - `f384` is `u8` (retail: `lbu`), not `s8` (`lb`) despite only ever being
 *     compared `!= 0`.
 *   - the `func_1839F0(...,0x4000)` guard also had its polarity/nesting
 *     inverted: it must be `if (...!=0) {arm-B} else if (func_1839F0(
 *     ...,0x1000)!=0) {arm-A}` as an if/else-IF chain, not a nested
 *     `if(==0){ if(...) {A} } else {B}` -- the nesting shape changed which
 *     branch mwcc marked likely and cost ~64 words before the fix.
 * Residue after all of the above: ONE func_290850(...,0x58,...) call site
 * (the f394=1 arm) has retail's `lwc1` (loading 1.2f) SCHEDULED BEFORE
 * the `addiu $5,0,0x58` id constant; every spelling tried here (inline
 * division, named `f32 v` local computed just above the call) keeps the
 * `addiu` first.  4 build round trips spent; parking per the 3-trip rule
 * (started at 91 bad, one extra trip earned two closed levers). */
#include "types.h"
/* normal 0x004F0CF0 -- the 0x58/0x59 blink pair's per-frame driver + the 0x55
 * gauge's show/hide relay.  Reuses the Obj layout established by the
 * sibling drivers normal_FUN_004F0A60 / normal_FUN_004F0FA0 / normal_FUN_004F0B50. */

typedef struct Obj {
    u8  pad000[0x378];
    s16 f378;
    u8  pad37A[0x384 - 0x37A];
    u8  f384;
    u8  pad385[0x386 - 0x385];
    s16 f386;
    u8  pad388[0x38C - 0x388];
    f32 f38C;
    u8  pad390[0x394 - 0x390];
    s16 f394;
} Obj;

extern const u8 D_004B2570[];
extern void *D_00484410;      /* gp - 0xD60 */

extern s32   func_1839F0(const u8 *p, s32 mask);
extern void  func_1B9520(void *a, s32 b, s32 c, f32 x);
extern void  func_290850(void *p, u16 id, u32 rgba, s32 n, f32 v);
extern void  func_2910A0(void *p, s32 id, s32 *x, s32 *y);
extern void  func_291110(void *p, s32 id, s32 c, s32 d);
extern s32   normal_FieldHudBtlEscChoiceBlink_4f0a60(Obj *p);
extern void  normal_FieldHudBtlEscArrowBob_4f0b50(Obj *p, s32 b, s32 c);
extern void  normal_FieldHudBtlEscClose_4f0fa0(Obj *p);

s32 normal_FieldHudBtlEscStep_4f0cf0(Obj *arg0)
{
    s32 sx;
    s32 sy;

    if (arg0->f378 == 0) {
        return 0;
    }
    if (arg0->f386 != 0) {
        func_291110(arg0, 0x55, 1, 1);
        if (arg0->f386 == 1) {
            if (arg0->f384 != 0) {
                arg0->f394 = 0;
                func_290850(arg0, 0x58, 0xFF606060, 0, arg0->f38C);
                func_290850(arg0, 0x59, 0xFF606060, 0, arg0->f38C / 2.0f);
            } else {
                if (func_1839F0(D_004B2570, 0x4000) != 0) {
                    f32 v;
                    if (arg0->f394 == 0) {
                        func_1B9520(D_00484410, 4, 0, 1.0f);
                    }
                    arg0->f394 = 1;
                    v = arg0->f38C / 1.2f;
                    func_290850(arg0, 0x58, 0xFF606060, 0, v);
                    func_290850(arg0, 0x59, 0xFF606060, 0, arg0->f38C);
                } else if (func_1839F0(D_004B2570, 0x1000) != 0) {
                    if (arg0->f394 == 1) {
                        func_1B9520(D_00484410, 4, 0, 1.0f);
                    }
                    arg0->f394 = 0;
                    func_290850(arg0, 0x58, 0xFF606060, 0, arg0->f38C);
                    func_290850(arg0, 0x59, 0xFF606060, 0, arg0->f38C / 1.2f);
                }
            }
            if (func_1839F0(D_004B2570, 0x40) != 0) {
                func_1B9520(D_00484410, 5, 0, 1.0f);
                arg0->f386 = 2;
            }
        }
        if (normal_FieldHudBtlEscChoiceBlink_4f0a60(arg0) != 0) {
            normal_FieldHudBtlEscClose_4f0fa0(arg0);
        }
        func_2910A0(arg0, 0x55, &sx, &sy);
        normal_FieldHudBtlEscArrowBob_4f0b50(arg0, -0x19, 3);
        if (sx == 0x200 && sy == 0xE2 && arg0->f386 == 3) {
            func_291110(arg0, 0x55, 0, 1);
            arg0->f386 = -1;
        }
    }
    return 1;
}
