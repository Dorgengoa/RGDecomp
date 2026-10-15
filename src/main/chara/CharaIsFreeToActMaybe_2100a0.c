#include "types.h"

f32 CharaGetHeightAboveGround_238380(u8 *);                           /* extern */
extern u8 D_0045B080[0x400];

s32 CharaIsFreeToActMaybe_2100a0(u8 *arg0) {
    s16 temp_3;
    s32 temp_3_2;
    s32 var_2;

    if ((*(s16 *)((u8 *)arg0 + 0xA38)) != 0) {
        return 0;
    }
    var_2 = (*(u8 *)((u8 *)arg0 + 0x860)) != 0;
    if (var_2 != 0) {
        var_2 = (*(s32 *)((u8 *)arg0 + 0x858)) > 0;
    }
    if (var_2 != 0) {
        return 0;
    } else {
        temp_3_2 = (*(s16 *)((u8 *)arg0 + 0xA32));
        switch (temp_3_2) {
        case 0:
        case 1:
        case 2:
        case 3:
            return 1;
        case 4:
            if (!(CharaGetHeightAboveGround_238380(arg0) <= (3.0f * (*(f32 *)D_0045B080)))) {
                return 0;
            }
            temp_3 = (*(s16 *)((u8 *)arg0 + 0xA34));
            if (temp_3 == 2) {
                return 0;
            }
            return temp_3 != 3;
        default:
            return 0;
        }
    }
}
