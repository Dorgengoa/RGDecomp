/* rgp:protos */
#define RGP_SELF_MotionMixerCfgMotionCmd_24e210 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
extern void *D_00481F44;

s32 MotionMixerCfgMotionCmd_24e210(void *rgp_a0)
{
    s32 temp_2;
    s32 temp_3;
    u8 *p;

    if (D_00481F44 != NULL) {
        temp_2 = VariantGetInt_15f780((void *)rgp_a0);
        p = (u8 *)D_00481F44;
        temp_3 = *(s32 *)(p + 0x3FC);
        if (temp_3 < 0xFF) {
            *(s32 *)(p + (temp_3 * 4)) = temp_2;
            *(s32 *)(p + 0x3FC) = *(s32 *)(p + 0x3FC) + 1;
        }
    }
    return 1;
}
