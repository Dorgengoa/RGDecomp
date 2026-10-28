/* rgp:protos */
#define RGP_SELF_DamagePopupSetup_2d38d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

#pragma opt_optimizecontrolflow off


typedef struct S002d38d0 {
    u8 pad0[0x20];
    f32 unk20;
    u8 pad24[4];
    f32 unk28;
    s16 unk2C;
    s16 unk2E;
    s32 unk30;
    s32 unk34;
    s32 unk38;
    u8 unk3C : 1;
} S002d38d0;

/*rgp*/

void DamagePopupSetup_2d38d0(S002d38d0 *arg0, s32 arg1, void *arg2, void *arg3, s32 arg4, s16 arg5, f32 fparg0) {
    s32 temp_4;

    if (!(arg0->unk3C)) {
        arg0->unk28 = fparg0;
        arg0->unk30 = arg1;
        arg0->unk38 = arg4;
        arg0->unk2E = arg5;
        arg0->unk2C = 0;
        sceVu0CopyVector(arg0, arg2);
        if (arg3 != NULL) {
            sceVu0CopyVector((u8 *)arg0 + 0x10, arg3);
        }
        arg0->unk34 = 0;
        arg0->unk3C = 1;
        if (arg0->unk38 == 1) {
            arg0->unk20 = 1.0f;
        }
        temp_4 = arg0->unk38;
        if ((temp_4 == 2) || (temp_4 == 5) || (temp_4 == 6)) {
            arg0->unk20 = 0.5f;
        }
    }
}
