/* rgp:protos */
#define RGP_SELF_MenuObjSlotsReleaseByKey_3857b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/                                /* extern */
/*rgp*/                                /* extern */
/*rgp*/                         /* extern */
/*rgp*/                              /* extern */

void MenuObjSlotsReleaseByKey_3857b0(s32 arg0, s32 arg1) {
    s32 temp_19;
    s32 temp_19_2;
    s32 var_16;
    s32 var_16_2;

    if (arg1 != 0) {
        var_16 = 0;
        do {
            temp_19 = arg0 + (var_16 * 0xC) + 0x1390;
            if ((((unsigned char)MenuObjSlotIsActive_3849d0(temp_19)) != 0) && (MenuObjSlotMatchesKey_3849a0(temp_19, arg1) != 0)) {
                MenuObjSlotClearFull_384960(temp_19);
            }
            var_16 += 1;
        } while (var_16 < 2);
        var_16_2 = 0;
        do {
            temp_19_2 = arg0 + (var_16_2 * 0x7A0) + 0x13B0;
            if ((((unsigned char)MenuObjSlotIsActive_3849d0(temp_19_2)) != 0) && (MenuObjSlotMatchesKey_3849a0(temp_19_2, arg1) != 0)) {
                MenuObjSlotModelReset_3848f0(temp_19_2);
            }
            var_16_2 += 1;
        } while (var_16_2 < 2);
    }
}
