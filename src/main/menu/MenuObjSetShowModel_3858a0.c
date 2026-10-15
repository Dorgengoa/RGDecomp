#include "types.h"

extern void ModelSetPos_151110(s32 arg0, void *arg1);
extern void ModelObjPlayMotionByName_1867a0(s32 arg0, void *arg1, s32 arg2);
extern void InsectCageSePlay_3844b0(void *arg0, s32 arg1);
extern void MenuObjGetPosWithOffsetMaybe_385cf0(s32 arg0, void *arg1, s32 arg2);
extern u8 D_00463F18[0x400];
extern s32 D_004832A0;

typedef struct Sub003858a0 {
    u8 pad0[0x448];
    f32 unk448;
    u8 pad44C[0x790 - 0x44C];
} Sub003858a0;

typedef struct Obj003858a0 {
    u8 pad0[0x22F0];
    Sub003858a0 sub[2];
    u8 pad3210[0x4150 - 0x3210];
    f32 unk4150;
} Obj003858a0;

void MenuObjSetShowModel_3858a0(Obj003858a0 *arg0, s32 arg1, s32 arg2)
{
    u8 sp30[0x10];
    Sub003858a0 *temp_16;

    if (arg1 >= 0) {
        if (arg1 > 1) {
            return;
        }
    } else {
        return;
    }
    MenuObjGetPosWithOffsetMaybe_385cf0(arg2, sp30, 0);
    arg0->sub[arg1].unk448 = 1.0f;
    temp_16 = &arg0->sub[arg1];
    ModelSetPos_151110((s32)temp_16, sp30);
    ModelObjPlayMotionByName_1867a0((s32)temp_16, D_00463F18, 6);
    arg0->unk4150 = 1.0f;
    InsectCageSePlay_3844b0(&D_004832A0, 3);
}
