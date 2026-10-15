#include "types.h"

extern f32 D_0045B080[4];
extern f32 D_0047F110;
extern f32 D_0047F114;
extern f32 D_0047F118;
extern f32 D_0047F11C;
extern void XformGetScaledMatrix_2e76b0(void *, f32 (*)[4], f32, f32, f32);
extern void XformGetMatrix_2e7750(void *, f32 (*)[4]);
extern void DrawWireCube_1cc1b0(s32, void *, s32);

void EvDoorObjDebugDraw_3038b0(u8 *arg0, s32 arg1)
{
    f32 mtx[4][4];
    f32 vec[4];
    f32 h;
    f32 k;
    f32 w;
    f32 d;

    if (*(s32 *)(arg0 + 0xD0) & 0x02000000) {
        h = *(f32 *)(arg0 + 0x174);
        w = *(f32 *)(arg0 + 0x170);
        d = *(f32 *)(arg0 + 0x178);
        if (d * (w * h) <= 0.0f) {
            XformGetMatrix_2e7750(arg0 + 0x10, mtx);
        } else {
            k = D_0045B080[0];
            XformGetScaledMatrix_2e76b0(arg0 + 0x10, mtx, w, 0.5f * (h + k), d);
            mtx[3][1] = mtx[3][1] + 0.5f * (*(f32 *)(arg0 + 0x174) - k);
        }
        vec[0] = D_0047F110;
        vec[1] = D_0047F114;
        vec[2] = D_0047F118;
        vec[3] = D_0047F11C;
        DrawWireCube_1cc1b0(arg1, mtx, (s32)vec);
    }
}
