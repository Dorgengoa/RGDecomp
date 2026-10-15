#include "types.h"
/* normal 0x004F19E0 -- widget 0x25 setup.  The first three stores go through
 * the PARAMETER, before it is copied to the callee-saved register. */
typedef struct Obj {
    u8  pad000[0x383];
    s8  f383;
    u8  pad384[0x430 - 0x384];
    s8  f430;
    u8  pad431[0x4A8 - 0x431];
    s16 f4A8;
    u8  pad4AA[0x4F0 - 0x4AA];
    s32 f4F0;
    s32 f4F4;
} Obj;

extern f32  D_0047DB7C;
extern void func_2907A0(Obj *p, u16 id, f32 x);
extern void func_290F60(Obj *p, u16 id, s32 c, s32 d);
extern void func_290690(Obj *p, u16 id, f32 x, f32 y, f32 z);
extern void func_290010(Obj *p, u16 id, s32 c, s32 d);

void normal_FieldHudRadarShow_4f19e0(Obj *p)
{
    p->f4A8 = 1;
    p->f4F0 = -1;
    p->f4F4 = 0;
    func_2907A0(p, 0x25, 0.0f);
    func_290F60(p, 0x25, 0x160, 0x108);
    func_290690(p, 0x25, 1.0f, D_0047DB7C, -1.0f);
    func_290010(p, 0x25, 1, -1);
    p->f430 = 2;
    p->f383 = 1;
}
