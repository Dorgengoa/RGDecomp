#include "types.h"

extern s32 GetMapMgr_201a90(void *arg0, void *arg1);
extern void MapMgrLoadAreaSlot3_1e30c0(s32 arg0, s16 *arg1, s32 arg2, s32 arg3);
extern void InsectBattleLoadStep_319780(void);
extern u8 D_00462398[0x400];
extern u8 D_004623A0[0x10];
extern u8 D_004623B0[0x10];
extern s16 D_004E8010[0x40];
extern s32 D_004E8018[0x40];
extern void *D_004E801C[0x40];
extern void *D_004E8020[0x40];
extern void *D_004E8024[0x40];
extern void *D_004E8028[0x40];
extern void *D_004E802C[0x40];

void InsectBattleLoadMap_31a1a0(void)
{
    D_004E8010[0] = 0x7D0;
    D_004E8018[0] = 0;
    D_004E801C[0] = D_00462398;
    D_004E8020[0] = D_004623A0;
    D_004E8024[0] = D_004623B0;
    D_004E8028[0] = D_00462398;
    D_004E802C[0] = D_00462398;
    MapMgrLoadAreaSlot3_1e30c0(GetMapMgr_201a90(D_004623A0, D_00462398), D_004E8010, 3, 0x8000);
    InsectBattleLoadStep_319780();
}
