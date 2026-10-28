/* rgp:protos */
#define RGP_SELF_TargetMngSyncLeaderPose_320850 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"
#pragma peephole off
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047F2D0;
extern f32 D_0047F2D4;
extern f32 D_0047F2D8;
extern f32 D_0047F2DC;

void TargetMngSyncLeaderPose_320850(u8 *arg0) {
    f32 sp70[4] __attribute__((aligned(16)));
    u8 sp30[0x40] __attribute__((aligned(16)));
    s32 id;
    u8 *p;

    id = ((s32)GetStaticScene_1c6c70());
    GetCharaResMgr_1fdb60();
    p = ObjRecGetLiveObject_1c4a90(id, *(s16 *)(*(u8 **)((u8 *)GetGameData_1fede0() + 0x18) + 0x18E));
    sp70[0] = D_0047F2D0;
    sp70[1] = D_0047F2D4;
    sp70[2] = D_0047F2D8;
    sp70[3] = D_0047F2DC;
    if (p != NULL) {
        *(u128 *)(arg0 + 0x90) = *(u128 *)(p + 0x180);
        *(u128 *)(arg0 + 0xA0) = *(u128 *)(p + 0x190);
        sceVu0UnitMatrix(sp30);
        sceVu0RotMatrixY(sp30, sp30, *(f32 *)(arg0 + 0xA4));
        MtxMulVec4_10a8c0(arg0 + 0xB0, sp30, sp70);
        sceVu0Normalize(arg0 + 0xB0, arg0 + 0xB0);
    }
}
