/* rgp:protos */
#define RGP_SELF_EvScriptCmdPathRecAddMovePath_300a70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward a global address. */

extern u8 D_00462110[];

/*rgp*/

s32 EvScriptCmdPathRecAddMovePath_300a70(s32 a4, s32 a5)
{
    return EventPathTemplateAddPath_300b90(a4, a5, D_00462110);
}
