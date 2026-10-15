#include "types.h"

extern s32 MenuObjInsectSatietyUnderCap_386bd0(s32);
extern s32 MenuObjInsectIsAdult_386c90(s32);
extern s32 ItemInsectUseClassMaybe_390b20(void);
extern s32 MenuObjOtherIdleExists_390ba0(s32);
extern s32 MenuObjHasBreedCandidate_390c10(s32);

s32 InsectCageMenuItemUseStatus_38fb50(s32 arg0, s32 arg1, s32 arg2)
{
    s32 temp_2;

    if (arg0 == 0) {
        return 1;
    }
    if (arg1 == 0) {
        return 1;
    }
    temp_2 = ItemInsectUseClassMaybe_390b20();
    if (temp_2 == -1) {
        return 1;
    }
    if (!(MenuObjInsectSatietyUnderCap_386bd0(arg1) & 0xFF)) {
        return 5;
    }
    if ((temp_2 == 2) && (MenuObjInsectIsAdult_386c90(arg1) == 0)) {
        return 2;
    }
    if ((temp_2 == 2) && (MenuObjHasBreedCandidate_390c10(arg1) == 0)) {
        return 3;
    }
    if ((temp_2 == 1) && (arg2 < 2) && (MenuObjOtherIdleExists_390ba0(arg1) == 0)) {
        return 4;
    }
    return 0;
}
