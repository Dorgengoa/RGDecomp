#include "types.h"

typedef struct {
    f32 unk0, unk4, unk8, unkC;
    f32 unk10, unk14, unk18, unk1C;
    f32 unk20, unk24, unk28, unk2C;
    f32 unk30, unk34;
    s32 unk38, unk3C;
    s32 unk40, unk44, unk48;
    u8 unk4C;
} Obj00308D10;

Obj00308D10 *GetCameraFollowParams_1f6d80();
extern const f32 D_0045B080[4];
extern const f32 __attribute__((section(".sdata"))) D_0047D404;
extern const f32 __attribute__((section(".sdata"))) D_0047D5D0;
extern const f32 __attribute__((section(".sdata"))) D_0047D84C;
extern const f32 __attribute__((section(".sdata"))) D_0047D85C;
extern const f32 __attribute__((section(".sdata"))) D_0047DB7C;
extern const f32 __attribute__((section(".sdata"))) D_0047DC30;
extern const f32 __attribute__((section(".sdata"))) D_0047DC34;
extern const f32 __attribute__((section(".sdata"))) D_0047DC38;

void CameraFollowParamsSetDefault_308d10(void) {
    f32 temp_f6;
    Obj00308D10 *temp_2;

    temp_2 = GetCameraFollowParams_1f6d80();
    temp_f6 = 5.0f * D_0045B080[0];
    temp_2->unk0 = D_0047D85C * temp_f6;
    temp_2->unk4 = temp_f6 * 5.0f;
    temp_2->unk8 = 8.0f * D_0045B080[0];
    temp_2->unkC = 20.0f * D_0045B080[0];
    temp_2->unk10 = D_0047D404;
    temp_2->unk14 = D_0047DC30;
    temp_2->unk18 = D_0047DC34;
    temp_2->unk1C = D_0047D84C;
    temp_2->unk20 = D_0047DC38;
    temp_2->unk24 = D_0047D5D0;
    temp_2->unk28 = D_0047D5D0;
    temp_2->unk2C = 0.5f;
    temp_2->unk30 = D_0047DB7C;
    temp_2->unk34 = 0.25f;
    temp_2->unk38 = 0;
    temp_2->unk3C = 0;
    temp_2->unk40 = 0;
    temp_2->unk44 = -1;
    temp_2->unk48 = -1;
    temp_2->unk4C = 1;
}
