#include "types.h"

extern u8 *D_00482838;
extern s32 D_0048283C;

extern void SrtInit_1c74d0(void *);
extern void SrtSetPos_1c73b0(void *, f32, f32, f32);
extern void SrtSetRot_1c73d0(void *, f32, f32, f32);
extern void SrtSetScale_1c73f0(void *, f32, f32, f32);

s32 EventPathRecPointPush_3010a0(f32 a0, f32 a1, f32 a2, f32 a3, f32 a4, f32 a5, f32 a6,
                 f32 a7, f32 a8)
{
    u8 *e;

    if (D_00482838 == 0 || D_0048283C >= 0x40) {
        return 1;
    }
    e = D_00482838 + D_0048283C * 48;
    SrtInit_1c74d0(e);
    SrtSetPos_1c73b0(e, a0, a1, a2);
    SrtSetRot_1c73d0(e, a3, a4, a5);
    SrtSetScale_1c73f0(e, a6, a7, a8);
    D_0048283C = D_0048283C + 1;
    return 1;
}
