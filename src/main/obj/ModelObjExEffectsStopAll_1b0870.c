#include "types.h"

/* Tail-call adapter: marshal and forward a global address. */

extern s32 ModelObjExEffectsStop_1b0880(s32, s32, s32);

s32 ModelObjExEffectsStopAll_1b0870(s32 a4)
{
    return ModelObjExEffectsStop_1b0880(a4, 0, 1);
}
