/* rgp:protos */
#define RGP_SELF_EvCmdCueStreamFadeOut_2412a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct E2412a0 { s32 a; s32 b; };
struct Ctx2412a0 { s32 f0; s32 f4; };
struct Arg2412a0 { s32 a; s32 b; s32 c; s32 d; };

extern struct Ctx2412a0 *gEventContext;
/*rgp*/
/*rgp*/

s32 EvCmdCueStreamFadeOut_2412a0(struct E2412a0 *p)
{
    struct Arg2412a0 s __attribute__((aligned(16)));
    s32 a;
    s32 b;

    a = ScriptGetInt_2490f0(p++);
    b = ScriptGetInt_2490f0(p);
    s.a = 0x8;
    s.b = a;
    s.c = 0;
    s.d = (s32)(f32)b;
    Vec4VectorPushBack_249120(gEventContext->f4, &s);
    return 1;
}
