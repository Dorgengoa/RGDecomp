/* rgp:protos */
#define RGP_SELF_InsectCageRecCfgCol_391130 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
extern s32 *D_00483444;

s32 InsectCageRecCfgCol_391130(s64 *arg0, s32 arg1)
{
    s32 arr[4] __attribute__((aligned(16)));
    s32 temp_3_2;
    s32 temp_4;
    s32 var_18;
    s32 var_16;
    s32 var_5;

    var_16 = 0;
    do {
        arr[var_16] = VariantGetInt_15f780(arg0++);
        var_16 += 1;
    } while (var_16 < 3);
    if (arg1 > 3) {
        arr[3] = VariantGetInt_15f780(arg0);
    } else {
        arr[3] = 0x80;
    }
    var_5 = 0;
    do {
        if (arr[var_5] < 0) {
            arr[var_5] = 0;
        }
        if (arr[var_5] > 0xff) {
            arr[var_5] = 0xFF;
        }
        var_5 += 1;
    } while (var_5 < 4);
    temp_3_2 = *D_00483444;
    if (temp_3_2 >= 3) {
        return 0;
    }
    D_00483444[temp_3_2 + 1] = (arr[3] << 0x18) | ((arr[2] << 0x10) | (arr[0] | (arr[1] << 8)));
    *D_00483444 += 1;
    return 1;
}
