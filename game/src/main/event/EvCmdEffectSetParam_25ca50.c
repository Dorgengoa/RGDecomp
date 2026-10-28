/* rgp:protos */
#define RGP_SELF_EvCmdEffectSetParam_25ca50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E8_FUN_0025ca50 {
    s32 a;
    s32 b;
} E8_FUN_0025ca50;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdEffectSetParam_25ca50(E8_FUN_0025ca50 *q, s32 mode)
{
    void *a;
    void *b;
    void *c;
    s32 t;

    if (mode != 3) return 0;
    a = GetEffectMgr_2d9040();
    b = ScriptGetInt_26a2a0(q++);
    c = ScriptGetInt_26a2a0(q++);
    t = q->a;
    switch (t) {
    case 0:
        EffectSetParamIntById_2e04a0(a, b, c, ScriptGetInt_26a2a0(q));
        break;
    case 1:
        EffectSetParamFloatById_2e0570(a, b, c, TaggedGetFloat_26a280(q));
        break;
    }
    return 1;
}
