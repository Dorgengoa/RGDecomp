/* rgp:protos */
#define RGP_SELF_EvCmdEffectSetParamVec_25c930 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Arg {
    s32 type;
    s32 val;
} Arg;

typedef struct Vi {
    s32 x, y, z, w;
} Vi;

typedef struct Vf {
    f32 x, y, z;
    s32 w;
} Vf;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdEffectSetParamVec_25c930(Arg *p, s32 argc)
{
    void *a;
    s32 b;
    s32 c;
    Vi vi __attribute__((aligned(16)));
    Vf vf __attribute__((aligned(16)));

    if (argc != 6) {
        return 0;
    }
    a = GetEffectMgr_2d9040();
    b = ScriptGetInt_26a2a0(p++);
    c = ScriptGetInt_26a2a0(p++);
    switch (p->type) {
    case 0:
        vi.x = ScriptGetInt_26a2a0(p++);
        vi.y = ScriptGetInt_26a2a0(p++);
        vi.z = ScriptGetInt_26a2a0(p++);
        vi.w = 0;
        EffectSetParamIntVecById_2e0280(a, b, c, &vi);
        break;
    case 1:
        vf.x = TaggedGetFloat_26a280(p++);
        vf.y = TaggedGetFloat_26a280(p++);
        vf.z = TaggedGetFloat_26a280(p++);
        vf.w = 0;
        EffectSetParamFloatVecById_2e0350(a, b, c, &vf);
        break;
    }
    return 1;
}
