/* rgp:protos */
#define RGP_SELF_ItemWeaponGetTopAttr_3d3390 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s32 ItemWeaponGetTopAttr_3d3390(void *arg0, s32 *arg1)
{
    u8 temp_3;
    s32 var_6;
    s32 var_5;
    s32 var_4;
    s32 temp_2;

    temp_2 = ItemDefGetWeaponData_40e110(*(s32 *)((u8 *)arg0 + 0x10));
    if (temp_2 == 0) {
        return -1;
    }
    var_6 = -1;
    var_5 = 0;
    var_4 = 0;
    do {
        temp_3 = *(u8 *)((u8 *)(temp_2 + (var_4 * 2)) + 0x18);
        if (var_5 < (s32)temp_3) {
            var_5 = (s32)temp_3;
            var_6 = var_4;
        }
        var_4 += 1;
    } while (var_4 < 5);
    if (arg1 != NULL) {
        *arg1 = var_5;
    }
    return var_6;
    return -1;
}
