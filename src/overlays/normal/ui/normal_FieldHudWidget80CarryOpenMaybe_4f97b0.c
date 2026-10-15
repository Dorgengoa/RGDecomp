#include "types.h"
/* normal 0x004F97B0 -- one-shot open of widget 0x80, latch +0x3D8 = 0xA. */

typedef struct Obj {
    u8  pad000[0x378];
    s16 f378;
    u8  pad37A[0x3D8 - 0x37A];
    s16 f3D8;
} Obj;

extern void *D_00481BBC;          /* gp - 0x35B4 */

extern const void *func_28AA30(void *a, s32 id);
extern void func_28F510(Obj *p, s32 id, const void *c, s32 d);
extern void func_291110(Obj *p, s32 id, s32 c, s32 d);
extern void func_290F60(Obj *p, s32 id, s32 c, s32 d);
extern void func_2907A0(Obj *p, s32 id, f32 x);

void normal_FieldHudWidget80CarryOpenMaybe_4f97b0(Obj *p)
{
    if (p->f378 != 0) {
        func_291110(p, 0x80, 1, 1);
        func_28F510(p, 0x80, func_28AA30(D_00481BBC, 0x5B), 0);
        func_290F60(p, 0x80, 0x33, 0x14A);
        func_2907A0(p, 0x80, 1.0f);
        p->f3D8 = 0xA;
    }
}
