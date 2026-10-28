/* rgp:protos */
#define RGP_SELF_EvCmdCueVolumeFadeOut_241140 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct E241140 { s32 a; s32 b; };
struct Ctx241140 { s32 f0; s32 f4; };
struct Arg241140 { s32 a; s32 b; s32 c; s32 d; };

extern struct Ctx241140 *gEventContext;
/*rgp*/
/*rgp*/

s32 EvCmdCueVolumeFadeOut_241140(struct E241140 *p)
{
    struct Arg241140 s __attribute__((aligned(16)));
    s32 a;
    s32 b;

    a = ScriptGetInt_2490f0(p++);
    b = ScriptGetInt_2490f0(p);
    s.a = 0xA;
    s.b = a;
    s.c = 0;
    s.d = (s32)(f32)b;
    Vec4VectorPushBack_249120(gEventContext->f4, &s);
    return 1;
}
