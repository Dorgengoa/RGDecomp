#include "types.h"

typedef struct { s32 a, b; } T_00246e70;
typedef struct { u8 pad[0xB55C]; f32 v; } CTX_00246e70;

extern struct { CTX_00246e70 *f0; } *gEventContext;
extern s32 ScriptGetInt_2490f0(T_00246e70 *);
extern f32 TaggedGetFloat_2490d0(T_00246e70 *);

s32 EvCmdSceneSetFocus_246e70(T_00246e70 *q)
{
    s32 r;
    f32 f;

    r = ScriptGetInt_2490f0(q++);
    if (r == 1) {
        f = TaggedGetFloat_2490d0(q);
        gEventContext->f0->v = f;
    } else {
        gEventContext->f0->v = -1.0f;
    }
    return 1;
}
