#include "types.h"
#include "vec.h"
#pragma peephole off
extern void MtxMulVec4_10a8c0(void *, void *, f32 *);
extern void *ObjRecGetLiveObject_1c4a90(s32, s16);
extern s32 GetStaticScene_1c6c70(void);
extern void GetCharaResMgr_1fdb60(void);
extern void *GetGameData_1fede0(void);
extern void sceVu0Normalize(void *, void *);
extern void sceVu0RotMatrixY(void *, void *, f32);
extern void sceVu0UnitMatrix(void *);
extern f32 D_0047F2D0;
extern f32 D_0047F2D4;
extern f32 D_0047F2D8;
extern f32 D_0047F2DC;

void TargetMngSyncLeaderPose_320850(u8 *arg0) {
    f32 sp70[4];
    u8 sp30[0x40];
    s32 id;
    u8 *p;

    id = GetStaticScene_1c6c70();
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
