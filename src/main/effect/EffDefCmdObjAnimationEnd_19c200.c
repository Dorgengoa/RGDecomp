#include "types.h"

extern void EffCurveFinishMaybe_197520(void *);
extern void EffObjAddChannel_1a9ce0(void *, void *, void *);

s32 EffDefCmdObjAnimationEnd_19c200(void *args, s32 n, void **ctx)
{
    u8 *o = (u8 *)ctx[0];

    if (*(void **)(o + 0x4C) != 0) {
        EffCurveFinishMaybe_197520(*(void **)(o + 0x4C));
        EffObjAddChannel_1a9ce0(*(void **)(o + 0x28), *(void **)(o + 0x20),
                     *(void **)(o + 0x4C));
    }
    *(s32 *)(o + 0x4C) = 0;
    return 1;
}
