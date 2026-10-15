#include "types.h"

typedef struct E8_FUN_0025ca50 {
    s32 a;
    s32 b;
} E8_FUN_0025ca50;

extern void *GetEffectMgr_2d9040(void);
extern void *ScriptGetInt_26a2a0(E8_FUN_0025ca50 *p);
extern f32 TaggedGetFloat_26a280(E8_FUN_0025ca50 *p);
extern void EffectSetParamIntById_2e04a0(void *a, void *b, void *c, void *d);
extern void EffectSetParamFloatById_2e0570(void *a, void *b, void *c, f32 v);

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
