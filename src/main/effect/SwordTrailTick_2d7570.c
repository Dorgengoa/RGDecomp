#include "types.h"

typedef struct {
    s16 unk0;
    u8 pad2[0xA];
    f32 unkC;
    s32 unk10;
    u8 pad14[0x8];
    s32 unk1C;
    f32 unk20;
    f32 unk24;
} Obj002d7570;

void SwordTrailTick_2d7570(Obj002d7570 *arg0, f32 fparg0) {
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f1;
    s32 temp_6;

    if (arg0->unk0 != 0) {
        temp_f0 = arg0->unkC;
        if (temp_f0 > 0.0f) {
            temp_f0_2 = temp_f0 - fparg0;
            arg0->unkC = temp_f0_2;
            if (temp_f0_2 <= 0.0f) {
                arg0->unk0 = 2;
            }
        }
        if (arg0->unk0 == 2) {
            temp_6 = arg0->unk1C + 8;
            arg0->unk1C = temp_6;
            if (temp_6 >= (arg0->unk10 * 0xA)) {
                arg0->unk0 = 0;
            }
            arg0->unk20 -= arg0->unk24;
            if (arg0->unk20 <= 0.0f) {
                arg0->unk20 = 0.0f;
                arg0->unk0 = 0;
            }
        }
    }
}
