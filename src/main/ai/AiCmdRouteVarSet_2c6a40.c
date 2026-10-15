#pragma opt_propagation off
#include "types.h"

typedef struct Arg { s32 a, b; } Arg;
typedef struct Elem { s32 x0; s32 x4; union { s32 i; f32 f; } x8; } Elem;
typedef struct Big { u8 pad[0xD0]; Elem e[1]; } Big;

extern s32 ScriptSlotGetInt_2cc9c0(Arg *arg0);
extern Big *D_004DB930[];

s32 AiCmdRouteVarSet_2c6a40(Arg *arg0)
{
    s32 idx;
    s32 v;
    f32 f;
    Big *b;

    if (D_004DB930[0] == NULL) {
        return 0;
    }
    idx = ScriptSlotGetInt_2cc9c0(arg0++);
    switch (arg0->a) {
    case 0:
        v = ScriptSlotGetInt_2cc9c0(arg0);
        b = D_004DB930[0];
        b->e[idx].x0 = 0;
        b->e[idx].x8.i = v;
        b->e[idx].x4 = 0;
        break;
    case 1:
        f = ScriptSlotGetInt_2cc9c0(arg0);
        b = D_004DB930[0];
        b->e[idx].x0 = 1;
        b->e[idx].x8.f = f;
        b->e[idx].x4 = 0;
        break;
    }
    return 1;
}
