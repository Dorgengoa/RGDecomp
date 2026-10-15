#include "types.h"

s32 MapMgrMinimapDraw_1e2820(u8 *, f32 *, f32);
s32 GetActionMgr_1fdb50();
u8 *GetGameData_1fede0();
u8 *GetMapMgr_201a90();
s32 ActionMgrFindById_233b50(s32, s16);
s32 CharaGetPos_2388a0(s32, f32 *);
s32 CharaGetRot_2388b0(s32, f32 *);
typedef struct V4 { f32 x, y, z, w; } V4;
extern V4 D_0047E590 __attribute__((section(".sdata")));
extern V4 D_0047E5A0 __attribute__((section(".sdata")));

void MinimapDraw_1ffbc0(void) {
    f32 sp40[4];
    f32 sp30[4];
    s32 temp_2;
    s32 temp_4;
    u8 *temp_16;
    u8 *temp_17;

    temp_16 = GetGameData_1fede0();
    temp_17 = GetMapMgr_201a90();
    if (*(u8 *)(*(u8 **)(temp_16 + 0x18) + 0x1A4) & 1) {
        return;
    }
    if (!(*(s32 *)(temp_17 + 0x60) & 4)) {
        if (*(s16 *)(*(u8 **)(temp_16 + 0xC) + 0x28) == 0) {
            return;
        }
    }
    temp_4 = GetActionMgr_1fdb50();
    *(V4 *)sp40 = D_0047E590;
    *(V4 *)sp30 = D_0047E5A0;
    temp_2 = ActionMgrFindById_233b50(temp_4, *(s16 *)(*(u8 **)(temp_16 + 0x18) + 0x18E));
    if (temp_2 != 0) {
        CharaGetPos_2388a0(temp_2, sp40);
        CharaGetRot_2388b0(temp_2, sp30);
    }
    MapMgrMinimapDraw_1e2820(temp_17, sp40, sp30[1]);
}
