/* PARKED: 1 round trip: mechanical conversion; length 0x11C vs retail 0x118. */
#include "types.h"

extern s32 StrNotEqual_1f5300(void *, void *);

s32 NodeRefListFind_318ed0(void *arg0, void *arg1)
{
    f32 temp_f22;
    f32 temp_f21;
    f32 temp_f20;
    void *var_17;
    s32 var_16;

    if (arg1 == NULL) {
        return -1;
    }
    temp_f20 = *(f32 *)((u8 *)arg1 + 0x28);
    var_17 = (u8 *)arg0 + 0x180;
    temp_f21 = *(f32 *)((u8 *)arg1 + 0x2C);
    temp_f22 = *(f32 *)((u8 *)arg1 + 0x30);
    var_16 = 0;
    while (var_16 < *(s16 *)((u8 *)arg0 + 0x680)) {
        if ((*(s16 *)((u8 *)arg1 + 0x0) == *(s16 *)((u8 *)var_17 + 0x0)) &&
            (*(s16 *)((u8 *)arg1 + 0x2) == *(s16 *)((u8 *)var_17 + 0x2)) &&
            (*(s16 *)((u8 *)arg1 + 0x4) == *(s16 *)((u8 *)var_17 + 0x4)) &&
            (*(s8 *)((u8 *)arg1 + 0x8) == *(s8 *)((u8 *)var_17 + 0x8)) &&
            (StrNotEqual_1f5300((u8 *)arg1 + 9, (u8 *)var_17 + 9) == 0)) {
            f32 x=*(f32 *)((u8 *)var_17+0x28),y=*(f32 *)((u8 *)var_17+0x2C),z=*(f32 *)((u8 *)var_17+0x30);
            if(temp_f20==x && temp_f21==y && temp_f22==z)
            return var_16;
        }
        var_16 += 1;
        var_17 = (u8 *)var_17 + 0x50;
    }
    return -1;
}
