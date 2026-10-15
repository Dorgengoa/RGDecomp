#include "types.h"

/* Tail-call adapter: marshal and forward a global address. */

extern u8 D_00462108[];

extern s32 EventPathTemplateAddPath_300b90(s32, s32, void *);

s32 EvScriptCmdPathRecAddGoPath_300a60(s32 a4, s32 a5)
{
    return EventPathTemplateAddPath_300b90(a4, a5, D_00462108);
}
