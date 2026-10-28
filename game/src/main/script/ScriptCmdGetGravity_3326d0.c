/* rgp:protos */
#define RGP_SELF_ScriptCmdGetGravity_3326d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern f32 D_0045B078[2];
extern f32 D_0045B080[2];
extern f32 D_0045B088[2];

/*rgp*/

s32 ScriptCmdGetGravity_3326d0(void *rgp_a0)
{
    ScriptSlotStoreFloatRef_3347d0((void *)rgp_a0, 2.0f * (D_0045B088[0] * (D_0045B080[0] / (D_0045B078[0] * D_0045B078[0]))));
    return 1;
}
