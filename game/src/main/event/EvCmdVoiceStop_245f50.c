/* rgp:protos */
#define RGP_SELF_EvCmdVoiceStop_245f50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { s32 a, b; } T_00245f50;

extern struct { s32 f0; void *f4; } *gEventContext;
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdVoiceStop_245f50(T_00245f50 *q)
{
    s32 r;
    void *a;
    f32 f;

    a = (void *)((s32)gEventContext->f4 + 0x420);
    r = ScriptGetInt_2490f0(q++);
    f = TaggedGetFloat_2490d0(q);
    EventVoiceStop_24e820(a, r, f);
    return 1;
}
