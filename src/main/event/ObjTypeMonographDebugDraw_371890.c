#include "types.h"


typedef struct {
    u8 pad0[0xD0];
    s32 unkD0;
    u8 pad0xD4[0xE0 - 0xD4];
    s32 unk118;
} Obj00337100;

extern void EventVolumeRecDebugDraw_2e49b0(s32, s32, void *, s32);
extern void XformGetMatrix_2e7750(void *, void *);
extern f32 D_0047F9E0;
extern f32 D_0047F9E4;
extern f32 D_0047F9E8;
extern f32 D_0047F9EC;

void ObjTypeMonographDebugDraw_371890(Obj00337100 *arg0, s32 arg1)
{
    u8 sp40[0x40];
    f32 sp[4];

    if (arg1 && (((arg0->unkD0 & 0x40000000)!=0)^1) && (arg0->unk118 != 0)) {
        XformGetMatrix_2e7750((u8 *)arg0 + 0x10, sp40);
        sp[0] = D_0047F9E0;
        sp[1] = D_0047F9E4;
        sp[2] = D_0047F9E8;
        sp[3] = D_0047F9EC;
        EventVolumeRecDebugDraw_2e49b0(arg0->unk118, arg1, sp40, (s32)&sp[0]);
    }
}
