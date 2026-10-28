/* rgp:protos */
#define RGP_SELF_EffDefCmdEffectFrameEnd_19b870 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Three byte-identical copies of one handler live in the image
   (EffDefCmdEffectFrameEnd_19b870 / EffDefCmdEffectEmitterEnd_19bb10 / EffDefCmdEffectObjectEnd_19f090); this is the same source.
   The `beql` delay slot carries the FIRST statement after the if, which is
   why `m44 = 0` appears on both paths. */

/*rgp*/

s32 EffDefCmdEffectFrameEnd_19b870(void *args, s32 n, void **ctx)
{
    u8 *o = (u8 *)ctx[0];

    if (*(void **)(o + 0x28) != 0) {
        EffObjCalcWorkSlots_1a9c60(*(void **)(o + 0x28));
    }
    *(s32 *)(o + 0x44) = 0;
    *(s32 *)(o + 0x28) = 0;
    *(s32 *)(o + 0x2C) = 0;
    *(s32 *)(o + 0x30) = 0;
    *(s32 *)(o + 0x48) = 0;
    *(s32 *)(o + 0x4C) = 0;
    *(s32 *)(o + 0x34) = 0;
    *(s32 *)(o + 0x38) = 0;
    *(s32 *)(o + 0x50) = 0;
    *(s32 *)(o + 0x54) = 0;
    return 1;
}
