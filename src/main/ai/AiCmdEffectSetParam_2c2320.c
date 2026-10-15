#include "types.h"

typedef struct E8_FUN_002c2320 {
    s32 a;
    s32 b;
} E8_FUN_002c2320;

extern void *GetEffectMgr_2d9040(void);
extern void *ScriptSlotGetInt_2cc9c0(E8_FUN_002c2320 *p);
extern f32 ScriptSlotGetFloat_2cc9a0(E8_FUN_002c2320 *p);
extern void EffectSetParamIntById_2e04a0(void *a, void *b, void *c, void *d);
extern void EffectSetParamFloatById_2e0570(void *a, void *b, void *c, f32 v);

s32 AiCmdEffectSetParam_2c2320(E8_FUN_002c2320 *q, s32 mode)
{
    void *a;
    void *b;
    void *c;
    s32 t;

    if (mode != 3) return 0;
    a = GetEffectMgr_2d9040();
    b = ScriptSlotGetInt_2cc9c0(q++);
    c = ScriptSlotGetInt_2cc9c0(q++);
    t = q->a;
    switch (t) {
    case 0:
        EffectSetParamIntById_2e04a0(a, b, c, ScriptSlotGetInt_2cc9c0(q));
        break;
    case 1:
        EffectSetParamFloatById_2e0570(a, b, c, ScriptSlotGetFloat_2cc9a0(q));
        break;
    }
    return 1;
}
