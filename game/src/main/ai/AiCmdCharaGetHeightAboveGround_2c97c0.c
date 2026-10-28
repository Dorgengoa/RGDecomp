/* rgp:protos */
#define RGP_SELF_AiCmdCharaGetHeightAboveGround_2c97c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern struct { void *p; s32 pad[3]; } D_004DB92C;
/*rgp*/
/*rgp*/

s32 AiCmdCharaGetHeightAboveGround_2c97c0(void *p)
{
    void *q;

    q = D_004DB92C.p;
    if ((*(s32 *)((s32)q + 0x3D8) & 4) != 0) {
        ScriptSlotStoreFloatRef_2cc8e0(p, CharaGetHeightAboveGround_238380(q));
    } else {
        ScriptSlotStoreFloatRef_2cc8e0(p, 0.0f);
    }
    return 1;
}
