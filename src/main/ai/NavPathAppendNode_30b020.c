#include "types.h"
#pragma opt_common_subs off

typedef struct { u8 pad0[0x10]; s32 unk10; s32 unk14; f32 unk18; u8 pad1c[4]; } E30;
typedef struct { E30 e[4]; s32 unk80[4]; s8 unk90; } T30;
extern void NavXformPointToWorld_310d10(s32 arg0, void *arg1, void *arg2);
extern f32 NavNodeGetDist_311910(s32 arg0);
extern void Vec3ToVec4W1_311970(s32 arg0, void *arg1);
extern s32 NavNodeGetFlags_3119a0(s32 arg0);
extern s32 NavNodeGetId_3119c0(s32 arg0);

void NavPathAppendNode_30b020(s32 pd0, s32 arg1, T30 *arg2, s32 arg3, s32 arg4, f32 fparg0)
{
    u8 sp60[0x10];

    Vec3ToVec4W1_311970(arg3, sp60);
    NavXformPointToWorld_310d10(arg1, &arg2->e[arg2->unk90], sp60);
    arg2->e[arg2->unk90].unk10 = NavNodeGetFlags_3119a0(arg3);
    arg2->e[arg2->unk90].unk14 = NavNodeGetId_3119c0(arg3);
    arg2->e[arg2->unk90].unk18 = fparg0 + NavNodeGetDist_311910(arg3);
    arg2->unk80[arg2->unk90] = arg4;
    arg2->unk90++;
}
