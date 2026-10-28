/* rgp:protos */
#define RGP_SELF_InsectCageMenuApplyItemToPair_38e470 1
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

extern s32 D_004832D8;
extern void *D_00483380;
extern void *D_00483384;
extern s8 D_00483388;
extern s8 D_00483389;
extern s8 D_0048338C;
extern s8 D_0048338D;
extern s8 D_00483390;
extern s8 D_00483391;
extern s8 D_00483394;
extern s8 D_00483395;
extern s32 D_004E9520[];

void InsectCageMenuApplyItemToPair_38e470(void) {
    s32 temp_10;
    s32 temp_17;
    s32 temp_16;

    MenuObjSetHideModels_385700(D_004832D8);
    D_00483388 = MenuObjInsectGetLevel_386b90(D_00483380, 0, 0, 0);
    D_00483389 = MenuObjInsectGetLevel_386b90(D_00483384, 0, 0, 0);
    D_0048338C = MenuObjInsectIsAdult_386c90(D_00483380, 0, 0, 0) != 0;
    D_0048338D = MenuObjInsectIsAdult_386c90(D_00483384, 0, 0, 0) != 0;
    D_00483390 = MenuObjInsectIsFullyGrown_386c40(D_00483380, 0, 0, 0);
    D_00483391 = MenuObjInsectIsFullyGrown_386c40(D_00483384, 0, 0, 0);
    D_00483394 = MenuObjInsectIsMaxLevel_386b60(D_00483380, 0, 0, 0);
    D_00483395 = MenuObjInsectIsMaxLevel_386b60(D_00483384, 0, 0, 0);
    temp_17 = *(s32 *)((u8 *)D_00483384 + 0x96C);
    temp_16 = *(s32 *)((u8 *)D_00483380 + 0x96C);
    temp_10 = InsectCageMenuGetCurCageItem_391030();
    InsectApplyItem_3cf310(temp_10, D_004E9520[0], temp_16, temp_17);
    MenuObjSetPlayStandMotion_3849e0(D_004832D8);
}
