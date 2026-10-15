#include "types.h"

extern void CharaAddFlags_212460(s32, s32);
extern void CharaRemoveFlags_212480(s32, s32);
extern void CharaGetPos_2388a0(s32, void *);
extern u8 D_0045B080[0x400];

void CharaReqClimbOrFallByHeight_2bd140(s32 pad0, s32 arg1, void *arg2) {
    u8 sp30[0x10];
    f32 t;
    f32 temp_f1;

    if (arg1 != 0) {
        CharaGetPos_2388a0(arg1, sp30);
        t = *(f32 *)(sp30 + 4);
        temp_f1 = *(f32 *)((u8 *)arg2 + 4);
        if (!(temp_f1 < t)) {
            CharaAddFlags_212460(arg1, 0x20000);
            CharaRemoveFlags_212480(arg1, 3);
        } else {
            if (temp_f1 < (t - *(f32 *)D_0045B080)) {
                CharaAddFlags_212460(arg1, 0x40000);
                CharaRemoveFlags_212480(arg1, 3);
            }
        }
    }
}
