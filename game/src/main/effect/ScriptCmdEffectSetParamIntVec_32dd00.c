/* rgp:protos */
#define RGP_SELF_ScriptCmdEffectSetParamIntVec_32dd00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { s32 a; s32 b; } Arg;
typedef struct { u8 d[0x20]; } Ctx;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

extern void *D_004826E0;

s32 ScriptCmdEffectSetParamIntVec_32dd00(Arg *p, s32 kind)
{
    s32 out[4] __attribute__((aligned(16)));
    Ctx ctx __attribute__((aligned(16)));
    u8 *q;
    u32 n;
    s32 id;
    s32 obj;

    if (kind < 4 || kind > 6) {
        return 0;
    }
    q = (u8 *)out;
    n = 0x10;
    if (q != 0) {
        do {
            *q = 0;
            n--;
            q++;
        } while (n != 0);
    }
    id = ScriptSlotGetInt_3348b0(p++);
    out[0] = ScriptSlotGetFloat_334890(p++);
    out[1] = ScriptSlotGetFloat_334890(p++);
    out[2] = ScriptSlotGetFloat_334890(p++);
    if (kind > 4) {
        out[3] = ScriptSlotGetFloat_334890(p);
    }
    if (D_004826E0 == 0) {
        return 0;
    }
    obj = ((s32)GetEffectMgr_2d9040());
    if (obj == 0) {
        return 0;
    }
    EffectCopyHandle_2dd3b0(&ctx, D_004826E0);
    EffectSetParamIntVec_2e0310(obj, &ctx, id, out);
    return 1;
}
