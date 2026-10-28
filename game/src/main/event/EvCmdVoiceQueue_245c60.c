/* rgp:protos */
#define RGP_SELF_EvCmdVoiceQueue_245c60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Ctx { u8 pad0[0x4]; u8 *f04; } Ctx;
typedef struct A A;

extern Ctx *gEventContext;
/*rgp*/
/*rgp*/

s32 EvCmdVoiceQueue_245c60(A *a)
{
    void *p = gEventContext->f04 + 0x420;
    EventVoicePendingPush_24e710(p, ScriptGetInt_2490f0(a));
    return 1;
}
