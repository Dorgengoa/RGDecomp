/* rgp:protos */
#define RGP_SELF_EvCmdStreamChanFadeIn_245eb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
extern void *gEventContext;

s32 EvCmdStreamChanFadeIn_245eb0(s64 *arg0, s32 arg1)
{
    f32 f;
    s32 a;
    s32 b;
    s32 t16;

    t16 = *(s32 *)((u8 *)gEventContext + 4) + 0x420;
    a = ScriptGetInt_2490f0((s32)arg0++);
    b = ScriptGetInt_2490f0((s32)arg0++);
    f = 1.0f;
    if (arg1 >= 3) {
        f = TaggedGetFloat_2490d0((s32)arg0);
    }
    EventVoiceSetChanVolumeFade_24e7d0(t16, a, b, f);
    return 1;
}
