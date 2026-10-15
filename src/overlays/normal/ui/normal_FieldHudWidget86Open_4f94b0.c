#include "types.h"
/* normal 0x004F94B0 -- one-shot open of widget 0x86.  Guard on the s16 at
 * +0x378 (the whole family shares it); latch s16 at +0x4A6. */

typedef struct Obj {
    u8  pad000[0x378];
    s16 f378;
    u8  pad37A[0x4A6 - 0x37A];
    s16 f4A6;
} Obj;

extern void *D_00481BBC;          /* gp - 0x35B4 */

extern const void *func_28AA30(void *a, s32 id);
extern void func_28F510(Obj *p, s32 id, const void *c, s32 d);
extern void func_291110(Obj *p, s32 id, s32 c, s32 d);
extern void func_290F60(Obj *p, s32 id, s32 c, s32 d);
extern void func_2907A0(Obj *p, s32 id, f32 x);

void normal_FieldHudWidget86Open_4f94b0(Obj *p)
{
    if (p->f378 != 0) {
        func_28F510(p, 0x86, func_28AA30(D_00481BBC, 0x5A), 0);
        func_291110(p, 0x86, 1, 1);
        func_290F60(p, 0x86, 0x14, 0x5A);
        func_2907A0(p, 0x86, 1.0f);
        p->f4A6 = 1;
    }
}
