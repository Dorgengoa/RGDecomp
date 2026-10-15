#include "types.h"

typedef struct Ctx { u8 pad000[0x4]; void *m04; } Ctx;

extern Ctx *gEventContext;
extern s32 ScriptGetInt_2490f0(void);
extern void Vec4VectorPushBack_249120(void *o, s32 *m);

s32 EvCmdCueMesWinAdvance_245920(void)
{
    s32 m[4];
    void *o;

    o = gEventContext->m04;
    m[0] = 3;
    m[1] = ScriptGetInt_2490f0();
    Vec4VectorPushBack_249120(o, m);
    return 1;
}
