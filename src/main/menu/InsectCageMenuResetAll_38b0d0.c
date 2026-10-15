#include "types.h"

extern void MemStackReset_14d830(void *);
extern void NameTableFreeGroup_158ac0(s32, s32);
extern s32 GetDrawCtxNameTable_15de40(void);
extern void MapMgrAuxAreaUnload_1e2d50(s32, s32);
extern s32 GetMapMgr_201a90(void);
extern void InsectCageSeStopLoops_384540(void *);
extern void InsectCageMsgListReset_384820(void *);
extern void MenuObjSetReset_384c80(s32);
extern void InsectCageItemIconReset_386070(void *);
extern void MenuObjTeardown_387d60(s32);
extern void MenuObjReset_387dc0(s32);
extern u8 D_004832A0;
extern u8 *D_004832A8;
extern s32 D_004832AC;
extern u8 D_004832D0;
extern s32 D_004832D8;
extern u8 D_004E9380[0x400];
extern u8 D_004E94A0[0x400];
extern u8 D_004E9510[0x400];
extern u8 D_004E9530[0x400];

void InsectCageMenuResetAll_38b0d0(void) {
    s32 temp_17;
    s32 temp_17_2;
    s32 temp_2;
    s32 temp_3;
    s32 var_16;
    s32 var_16_2;

    InsectCageSeStopLoops_384540(&D_004832A0);
    temp_2 = GetMapMgr_201a90();
    if (temp_2 != 0) {
        MapMgrAuxAreaUnload_1e2d50(temp_2, 1);
    }
    MemStackReset_14d830(&(*(u8 *)D_004E9380));
    var_16 = 0;
    do {
        MemStackReset_14d830(D_004832A8 + (var_16 * 0x58));
        temp_17 = var_16 * 0x9D0;
        MenuObjTeardown_387d60(D_004832AC + temp_17);
        MenuObjReset_387dc0(D_004832AC + temp_17);
        temp_3 = var_16 * 4;
        var_16 += 1;
        *(s32 *)((u8 *)&(*(s32 *)D_004E94A0) + temp_3) = 0;
    } while (var_16 < 5);
    temp_17_2 = GetDrawCtxNameTable_15de40();
    var_16_2 = 0x263;
    do {
        NameTableFreeGroup_158ac0(temp_17_2, var_16_2);
        var_16_2 += 1;
    } while (var_16_2 <= 0x268);
    InsectCageItemIconReset_386070(&(*(u8 *)D_004E9510));
    InsectCageItemIconReset_386070(&(*(u8 *)D_004E9530));
    InsectCageMsgListReset_384820(&D_004832D0);
    MenuObjSetReset_384c80(D_004832D8);
}
