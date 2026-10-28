/* rgp:protos */
#define RGP_SELF_ModelSetRootMatrix_1512e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

void ModelSetRootMatrix_1512e0(u8 *arg0, s32 arg1)
{
    s32 var_16;
    s32 var_16_2;
    s32 var_16_3;
    u8 *temp_2;
    u8 *temp_2_2;
    u8 *temp_2_3;

    *(u8 **)(arg0 + 0x4) = NULL;
    if ((*(s32 *)(arg0 + 0x110) != 0) && (*(s32 *)(arg0 + 0x0) != 0)) {
        var_16 = 0;
        while (var_16 < *(s32 *)(arg0 + 0x10C)) {
            temp_2 = ((u8 *)ArrayGetChecked_152fd0(*(s32 *)(arg0 + 0x104), *(s32 *)(*(u8 **)(arg0 + 0x110) + (var_16 * 4))));
            if ((temp_2 != NULL) && (*(s8 *)(temp_2 + 0x28) != 0)) {
                *(s32 *)(temp_2 + 0x4) = 0;
            }
            var_16 += 1;
        }
    }
    ModelFrameSetMatrix_14a190(arg0 + 0x10, arg1);
    *(s32 *)(arg0 + 0x100) = 0;
    *(u8 **)(arg0 + 0x4) = NULL;
    if ((*(s32 *)(arg0 + 0x110) != 0) && (*(s32 *)(arg0 + 0x0) != 0)) {
        var_16_2 = 0;
        while (var_16_2 < *(s32 *)(arg0 + 0x10C)) {
            temp_2_2 = ((u8 *)ArrayGetChecked_152fd0(*(s32 *)(arg0 + 0x104), *(s32 *)(*(u8 **)(arg0 + 0x110) + (var_16_2 * 4))));
            if ((temp_2_2 != NULL) && (*(s8 *)(temp_2_2 + 0x28) != 0)) {
                *(s32 *)(temp_2_2 + 0x4) = 0;
            }
            var_16_2 += 1;
        }
    }
    *(u8 **)(arg0 + 0x4) = arg0 + 0x10;
    if ((*(s32 *)(arg0 + 0x110) != 0) && (*(s32 *)(arg0 + 0x0) != 0)) {
        var_16_3 = 0;
        while (var_16_3 < *(s32 *)(arg0 + 0x10C)) {
            temp_2_3 = ((u8 *)ArrayGetChecked_152fd0(*(s32 *)(arg0 + 0x104), *(s32 *)(*(u8 **)(arg0 + 0x110) + (var_16_3 * 4))));
            if (temp_2_3 != NULL) {
                *(s8 *)(temp_2_3 + 0x28) = 1;
                *(u8 **)(temp_2_3 + 0x4) = arg0 + 0x10;
                FrameSetDirty_14a5e0(temp_2_3);
            }
            var_16_3 += 1;
        }
    }
    *(s32 *)(arg0 + 0x100) = 1;
}
