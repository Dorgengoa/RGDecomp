#include "types.h"


extern void DrawWireCube_1cc1b0(s32 arg0, void *arg1, s32 arg2);
extern s32 TargetRefGetObj_2e7110(void *arg0);
extern void XformGetScaledMatrix_2e76b0(void *arg0, void *arg1, f32 arg2, f32 arg3, f32 arg4);
extern f32 D_0047F5E0;
extern f32 D_0047F5E4;
extern f32 D_0047F5E8;
extern f32 D_0047F5EC;

void EvTargetSetDrawBox_3365a0(void *arg0, s32 arg1)
{
    u8 sp40[0x40];
    f32 sp[4];

    if (TargetRefGetObj_2e7110((u8 *)arg0 + 0x30) != 0) {
        XformGetScaledMatrix_2e76b0((u8 *)arg0 + 0xC0, sp40, *(f32 *)((u8 *)arg0 + 0x10C),
                     *(f32 *)((u8 *)arg0 + 0x110), *(f32 *)((u8 *)arg0 + 0x108));
        sp[0] = D_0047F5E0;
        sp[1] = D_0047F5E4;
        sp[2] = D_0047F5E8;
        sp[3] = D_0047F5EC;
        DrawWireCube_1cc1b0(arg1, sp40, (s32)&sp[0]);
    }
}
