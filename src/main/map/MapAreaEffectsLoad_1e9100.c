#include "types.h"

typedef struct V1e9100 {
    s32 v[4];
} V1e9100;

typedef struct A1e9100 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
} A1e9100;

extern s32 GetEffectMgr_2d9040(void);
extern void EffectArchiveLoadByName_2e28a0(V1e9100 *, s32, s32, s32, s32, s32);

s32 MapAreaEffectsLoad_1e9100(A1e9100 *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    V1e9100 sp80;
    V1e9100 sp70;
    V1e9100 sp60;
    V1e9100 sp50;
    s32 h;

    if (arg3 == 0 || arg2 == 0) {
        return 0;
    }
    h = GetEffectMgr_2d9040();
    if (arg0->unk4 != 0) {
        EffectArchiveLoadByName_2e28a0(&sp80, h, arg2, arg0->unk4, arg3, arg0->unk0);
    }
    if (arg0->unk8 != 0) {
        EffectArchiveLoadByName_2e28a0(&sp70, h, arg2, arg0->unk8, arg3, arg0->unk0);
    }
    if (arg0->unkC != 0) {
        EffectArchiveLoadByName_2e28a0(&sp60, h, arg2, arg0->unkC, arg3, arg0->unk0);
    }
    if (arg0->unk10 != 0) {
        EffectArchiveLoadByName_2e28a0(&sp50, h, arg2, arg0->unk10, arg3, arg0->unk0);
    }
    return 0;
}
