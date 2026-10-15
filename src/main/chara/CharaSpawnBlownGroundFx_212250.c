#include "types.h"

typedef struct {
    s32 x0;
    f32 x4;
    s32 x8;
    s32 xC;
} Pos;

extern f32 RandFloat_13c010(void);
extern s32 CharaGetNthAttachPointPos_238580(void *arg0, s32 arg1, s32 arg2, Pos *arg3);
extern void CharaGetPos_2388a0(void *arg0, Pos *arg1);
extern s32 GetEffectMgr_2d9040(void);
extern void EffectSetId_2e0100(s32 arg0, void *arg1, s16 arg2);
extern void EffectSetRotXyz_2e0910(s32 arg0, void *arg1, f32 arg2, f32 arg3, f32 arg4);
extern void EffectSetPos_2e0bb0(s32 arg0, void *arg1, Pos *arg2);
extern void EffectCreateByName_2e1020(void *arg0, s32 arg1, s8 *arg2, s32 arg3);
extern void strcpy(s8 *dst, void *src);
extern u8 D_0045CA18[0x400];
extern u8 D_0045CA20[0x400];
extern f32 D_0047DB00;

void CharaSpawnBlownGroundFx_212250(void *arg0, s32 arg1)
{
    s32 temp_16 = GetEffectMgr_2d9040();
    s8 sp70[0x20] = {0};
    Pos sp60;
    u8 sp40[0x20];
    u8 *base;

    base = (u8 *)arg0;
    switch (arg1) {
    case 14:
    case 17:
        strcpy(sp70, D_0045CA18);
        break;
    case 2:
    case 16:
    case 1:
        strcpy(sp70, D_0045CA20);
        break;
    }
    if (sp70[0] == 0) {
        return;
    }
    if (CharaGetNthAttachPointPos_238580(arg0, 0, 0, &sp60) == 0) {
        CharaGetPos_2388a0(arg0, &sp60);
    }
    sp60.x4 = *(f32 *)(base + 0x74);
    EffectCreateByName_2e1020(sp40, temp_16, sp70, -1);
    EffectSetId_2e0100(temp_16, sp40, *(s16 *)(base + 0x424));
    EffectSetPos_2e0bb0(temp_16, sp40, &sp60);
    EffectSetRotXyz_2e0910(temp_16, sp40, 0.0f, D_0047DB00 * (RandFloat_13c010() - 0.5f), 0.0f);
}
