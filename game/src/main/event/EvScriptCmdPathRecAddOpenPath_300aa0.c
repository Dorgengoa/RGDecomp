/* rgp:protos */
#define RGP_SELF_EvScriptCmdPathRecAddOpenPath_300aa0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward a global address. */

extern u8 D_00462128[];

/*rgp*/

s32 EvScriptCmdPathRecAddOpenPath_300aa0(s32 a4, s32 a5)
{
    return EventPathTemplateAddPath_300b90(a4, a5, D_00462128);
}
