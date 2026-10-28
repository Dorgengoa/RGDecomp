/* rgp:protos */
#define RGP_SELF_MotionEventCfgTexAnimeCmd_1b3f80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

s32 MotionEventCfgTexAnimeCmd_1b3f80(s32 arg0, s32 unused1, void **arg2)
{
    u8 *temp_16;

    temp_16 = *(u8 **)arg2;
    if (*(u8 **)(temp_16 + 0x4C) == NULL) {
        return 0;
    }
    *(s32 *)(*(u8 **)(temp_16 + 0x4C) + 0x28) = ((s32)MemStackStrDup_14cf10(SlotGetInt_15f720((void *)arg0), *(s32 *)(temp_16 + 0x30)));
    *(s32 *)(*(u8 **)(temp_16 + 0x4C) + 0x2C) = VariantGetInt_15f780(arg0 + 8);
    return 1;
}
