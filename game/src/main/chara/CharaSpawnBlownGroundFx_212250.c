/* rgp:protos */
#define RGP_SELF_CharaSpawnBlownGroundFx_212250 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s32 x0;
    f32 x4;
    s32 x8;
    s32 xC;
} Pos;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void strcpy(s8 *dst, void *src);
extern u8 D_0045CA18[0x400];
extern u8 D_0045CA20[0x400];
extern f32 D_0047DB00;

void CharaSpawnBlownGroundFx_212250(void *arg0, s32 arg1)
{
    s32 temp_16 = ((s32)GetEffectMgr_2d9040());
    s8 sp70[0x20] __attribute__((aligned(16))) = {0};
    Pos sp60 __attribute__((aligned(16)));
    u8 sp40[0x20] __attribute__((aligned(16)));
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
