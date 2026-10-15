#include "types.h"
/* normal 0x005117E0 -- one-shot open of the 0x21/0x22 panel pair; the u8 phase
 * at +0x14 gates it and is then latched to 3.  Retail branches INTO the body
 * on `< 3` and lets `b <epilogue> / addiu $2,1` fall through, so the source is
 * the INVERTED early return.  0xBE800000 is -0.25f. */

typedef struct Obj {
    u8   pad000[0x14];
    u8   f014;
    u8   pad015[0x64 - 0x15];
    s32  f064;
} Obj;

extern f32 D_0047D7D0;            /* gp - 0x79A0 */
extern f32 D_0047D7D8;            /* gp - 0x7998 */

extern void func_1B9520(s32 a, s32 b, s32 c, f32 x);
extern void func_2907A0(Obj *p, s32 id, f32 x);
extern void func_290690(Obj *p, s32 id, f32 x, f32 y, f32 z);
extern void func_290F60(Obj *p, s32 id, s32 c, s32 d);
extern void func_290F50(Obj *p, s32 id, s32 c, s32 d, s32 e, f32 x);

s32 normal_SpaceMenuCancel_5117e0(Obj *p)
{
    if (p->f014 >= 3) {
        return 1;
    }
    func_1B9520(p->f064, 6, 0, 1.0f);
    p->f014 = 3;
    func_2907A0(p, 2, 1.0f);
    func_2907A0(p, 1, 1.0f);
    func_290690(p, 2, 0.0f, D_0047D7D0, -1.0f);
    func_2907A0(p, 0x27, 1.0f);
    func_290690(p, 0x27, 0.0f, -0.25f, -1.0f);
    func_290F60(p, 0x21, -0xA, 0x31);
    func_290F50(p, 0x21, -0x12C, 0x31, 0, D_0047D7D8);
    func_290F60(p, 0x22, 0xF5, 0x156);
    func_290F50(p, 0x22, 0x214, 0x156, 0, D_0047D7D8);
    return 0;
}
