#include "types.h"

typedef struct { s32 a, b; } T_00241240;
typedef struct { s32 a; s32 b; f32 c; } M_00241240;

extern s32 ScriptGetInt_2490f0(T_00241240 *);
extern f32 TaggedGetFloat_2490d0(T_00241240 *);
extern void Vec4VectorPushBack_249120(void *, M_00241240 *);
extern struct { s32 f0; void *f4; } *gEventContext;

s32 EvCmdCueVolumeSet_241240(T_00241240 *q)
{
    M_00241240 m;
    s32 r;
    f32 f;

    r = ScriptGetInt_2490f0(q++);
    f = TaggedGetFloat_2490d0(q);
    m.b = r;
    m.a = 9;
    m.c = f;
    Vec4VectorPushBack_249120(gEventContext->f4, &m);
    return 1;
}
