/* rgp:protos */
#define RGP_SELF_AnimBlendBufAccumulate_1533f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 AnimBlendBufAccumulate_1533f0(void *arg0, s32 arg1, f32 fparg0, f32 fparg1)
{
    u16 temp_4;
    u16 temp_4_2;
    void *var_16;
    void *var_16_2;

    var_16 = AnimResGetFrameKeyList_14bf10(arg1);
    while (var_16 != NULL) {
        temp_4 = *(u16 *)((u8 *)var_16 + 0x4);
        if ((s32) temp_4 < *(s32 *)((u8 *)arg0 + 0x0)) {
            if ((s32) temp_4 >= 0) {
                AnimKeyBlendFrame_155bf0(*(s32 *)((u8 *)arg0 + 0x4) + (temp_4 * 0x60), fparg0, fparg1, var_16);
            }
            var_16 = *(void **)((u8 *)var_16 + 0x0);
            continue;
        }
        break;
    }
    var_16_2 = AnimResGetMaterialKeyList_14bef0(arg1);
    while (var_16_2 != NULL) {
        temp_4_2 = *(u16 *)((u8 *)var_16_2 + 0x4);
        if ((s32) temp_4_2 < *(s32 *)((u8 *)arg0 + 0x8)) {
            if ((s32) temp_4_2 >= 0) {
                AnimKeyBlendMaterial_1559e0(*(s32 *)((u8 *)arg0 + 0xC) + (temp_4_2 * 0x30), fparg0, fparg1, var_16_2);
            }
            var_16_2 = *(void **)((u8 *)var_16_2 + 0x0);
            continue;
        }
        break;
    }
    return 1;
}
