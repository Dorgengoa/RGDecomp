/* rgp:protos */
#define RGP_SELF_MenuResReleaseAll_204fe0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off
#pragma opt_propagation on

/*rgp*/                             /* extern */
/*rgp*/                                 /* extern */
/*rgp*/                                /* extern */
/*rgp*/                                /* extern */
/*rgp*/                                   /* extern */
/*rgp*/                                   /* extern */
/*rgp*/                                   /* extern */
/*rgp*/                                   /* extern */
/*rgp*/                                   /* extern */
/*rgp*/                                   /* extern */
/*rgp*/                                   /* extern */
/*rgp*/                                   /* extern */
/*rgp*/                                   /* extern */
/*rgp*/                                   /* extern */
/*rgp*/                                   /* extern */
/*rgp*/                                   /* extern */
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
