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

extern void *GetEffectMgr_2d9040(void);
extern s32   ScriptSlotGetInt_2cc9c0(Arg *p);
extern f32   ScriptSlotGetFloat_2cc9a0(Arg *p);
extern void  EffectSetParamIntVecById_2e0280(void *a, s32 b, s32 c, Vi *v);
extern void  EffectSetParamFloatVecById_2e0350(void *a, s32 b, s32 c, Vf *v);

s32 AiCmdEffectSetParamVec_2c2200(Arg *p, s32 argc)
{
    void *a;
    s32 b;
    s32 c;
    Vi vi;
    Vf vf;

    if (argc != 6) {
        return 0;
    }
    a = GetEffectMgr_2d9040();
    b = ScriptSlotGetInt_2cc9c0(p++);
    c = ScriptSlotGetInt_2cc9c0(p++);
    switch (p->type) {
    case 0:
        vi.x = ScriptSlotGetInt_2cc9c0(p++);
        vi.y = ScriptSlotGetInt_2cc9c0(p++);
        vi.z = ScriptSlotGetInt_2cc9c0(p++);
        vi.w = 0;
        EffectSetParamIntVecById_2e0280(a, b, c, &vi);
        break;
    case 1:
        vf.x = ScriptSlotGetFloat_2cc9a0(p++);
        vf.y = ScriptSlotGetFloat_2cc9a0(p++);
        vf.z = ScriptSlotGetFloat_2cc9a0(p++);
        vf.w = 0;
        EffectSetParamFloatVecById_2e0350(a, b, c, &vf);
        break;
    }
    return 1;
}
