#include "types.h"
#pragma opt_propagation off
#pragma opt_propagation on

s32 NameTableFreeGroup_158ac0(s32, s32);                             /* extern */
s32 GetDrawCtxNameTable_15de40();                                 /* extern */
s32 PadClearStickDpadThreshold_183940(u8 *);                                /* extern */
s32 PadClearRepeatAll_183960(u8 *);                                /* extern */
s32 MenuTransResRelease_2037e0();                                   /* extern */
s32 MenuTestResRelease_2038c0();                                   /* extern */
s32 MenuBattleEndLoaderRelease_2042b0();                                   /* extern */
s32 SpaceMenuResRelease_2046c0();                                   /* extern */
s32 MenuExitFreeGroupsMaybe_204970();                                   /* extern */
s32 MenuTranstempRelease_206230();                                   /* extern */
s32 MenuTransdataRelease_206260();                                   /* extern */
s32 MenuBattleEndStackRelease_206590();                                   /* extern */
s32 MenuBattleIconStackRelease_2066c0();                                   /* extern */
s32 MenuBattleStackRelease_2067d0();                                   /* extern */
s32 MenuCapStackRelease_2068e0();                                   /* extern */
s32 MenuMainStackRelease_206910();                                   /* extern */
extern s32 D_00481B8C;
extern u8 D_004B2570[0x400];

void MenuResReleaseAll_204fe0(void) {
    s32 arg_h1;

    s32 temp_2;

    temp_2 = GetDrawCtxNameTable_15de40();
    NameTableFreeGroup_158ac0(temp_2, 0x32B);
    NameTableFreeGroup_158ac0(temp_2, 0x32D);
    arg_h1 = 0x32F;
    NameTableFreeGroup_158ac0(temp_2, arg_h1);
    NameTableFreeGroup_158ac0(temp_2, 0x32E);
    NameTableFreeGroup_158ac0(temp_2, 0x32C);
    MenuMainStackRelease_206910();
    MenuCapStackRelease_2068e0();
    MenuBattleStackRelease_2067d0();
    MenuBattleIconStackRelease_2066c0();
    MenuBattleEndStackRelease_206590();
    MenuTransdataRelease_206260();
    MenuTranstempRelease_206230();
    SpaceMenuResRelease_2046c0();
    MenuBattleEndLoaderRelease_2042b0();
    MenuExitFreeGroupsMaybe_204970();
    MenuTransResRelease_2037e0();
    MenuTestResRelease_2038c0();
    if (D_00481B8C != 0) {
        D_00481B8C = 0;
    }
    PadClearRepeatAll_183960((u8 *)&(*(s32 *)D_004B2570));
    PadClearStickDpadThreshold_183940((u8 *)&(*(s32 *)D_004B2570));
}
