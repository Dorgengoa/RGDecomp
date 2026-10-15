#include "types.h"

typedef struct { s32 a, b; } T_0032e960;
typedef struct { f32 x, y, z, w; } M_0032e960;

extern void *ScriptSlotGetInt_3348b0(T_0032e960 *);
extern void ScriptSlotsToVec4_334810(M_0032e960 *, T_0032e960 *);
extern f32 ScriptSlotGetFloat_334890(void *);
extern void *MovingLineGet_2d8df0(void *);
extern void MovingLinePushPoint_2d6330(void *, M_0032e960 *, f32);

s32 ScriptCmdMovingLinePushPoint_32e960(T_0032e960 *p, s32 mode)
{
    M_0032e960 m;
    void *r;
    void *s;
    f32 t;

    if (mode != 5) return 0;
    r = ScriptSlotGetInt_3348b0(p++);
    ScriptSlotsToVec4_334810(&m, p);
    t = ScriptSlotGetFloat_334890((void *)((s32)p + 0x18));
    s = MovingLineGet_2d8df0(r);
    if (s != 0) {
        MovingLinePushPoint_2d6330(s, &m, t);
    }
    return 1;
}
