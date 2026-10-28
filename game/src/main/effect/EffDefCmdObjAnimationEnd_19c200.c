/* rgp:protos */
#define RGP_SELF_EffDefCmdObjAnimationEnd_19c200 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

s32 EffDefCmdObjAnimationEnd_19c200(void *args, s32 n, void **ctx)
{
    u8 *o = (u8 *)ctx[0];

    if (*(void **)(o + 0x4C) != 0) {
        EffCurveFinishMaybe_197520();
        EffObjAddChannel_1a9ce0(*(void **)(o + 0x28), *(void **)(o + 0x20),
                     *(void **)(o + 0x4C));
    }
    *(s32 *)(o + 0x4C) = 0;
    return 1;
}
