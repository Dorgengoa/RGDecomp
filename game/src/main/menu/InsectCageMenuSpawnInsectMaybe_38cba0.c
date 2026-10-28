/* rgp:protos */
#define RGP_SELF_InsectCageMenuSpawnInsectMaybe_38cba0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_004832A8;
extern u8 D_004832B8;
extern s32 D_004832DC;
extern s32 D_004832E4;
extern s16 D_004833D0;

s32 InsectCageMenuSpawnInsectMaybe_38cba0(int rgp_a0, int rgp_a1, int rgp_a2, int rgp_a3)
{
    u8 sp8C[4];
    s32 sp88;
    s32 sp84;
    u8 sp40[0x44] __attribute__((aligned(16)));
    s32 temp_16;
    s32 temp_17;
    s32 temp_18;
    s32 var_17;

    switch (D_004833D0) {
    case 0:
        MenuObjTeardown_387d60(InsectCageMenuGetCursorObjThunk_390f70());
        if (D_004832DC == 0) {
            InsectCageMenuSelectEntry_390d40(0x7531, 0);
            break;
        }
        D_004833D0 += 1;
        break;
    case 1:
        InsectCharaPathFormat_390de0(sp40, D_004832DC, (int)rgp_a2, (int)rgp_a3);
        LoadHandleInit_28b610(D_004832E4);
        LoadHandleRequestFile_28b550(D_004832E4, sp40, 1, 0);
        D_004833D0 += 1;
        break;
    case 2:
        if (LoadHandleGetStatus_28b2e0(D_004832E4) == 1) {
            temp_17 = LoadHandleGetData_28b270(D_004832E4, sp8C);
            sp88 = -1;
            temp_16 = MenuObjFindFree_390d80(&sp88);
            if (sp88 >= 0) {
                MenuObjReset_387dc0(temp_16);
                MenuObjLoadFromCfg_387930(temp_16, temp_17, sp88 + 0x263, D_004832A8 + sp88 * 0x58, D_004832DC);
                MenuObjBuildRandomRoute_3871a0(temp_16, &D_004832B8, 4);
                InsectPlaceAtRandomSpotMaybe_38acf0(temp_16, 0, 0, -1);
                temp_18 = InsectCageGetCollTris_389d70(&sp84);
                var_17 = 0;
                do {
                    MenuObjWalkUpdateMaybe_387390(temp_16, temp_18, sp84);
                    var_17 += 1;
                } while (var_17 < 4);
            }
            LoadHandleFree_28b230(D_004832E4);
            InsectCageMenuSelectEntry_390d40(0x7531, 0);
        }
        break;
    }
    return 0;
}
