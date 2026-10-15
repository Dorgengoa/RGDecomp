#include "types.h"

typedef struct { s32 a, b; } T_0025da30;

extern f32 TaggedGetFloat_26a280(T_0025da30 *);
extern f32 Atan2f_1291a8(f32, f32);
extern void ScriptSetRefFloat_26a1c0(T_0025da30 *, f32);

s32 EvCmdAtan2_25da30(T_0025da30 *q)
{
    f32 a;
    f32 b;
    f32 c;

    a = TaggedGetFloat_26a280(q++);
    b = TaggedGetFloat_26a280(q++);
    c = Atan2f_1291a8(a, b);
    ScriptSetRefFloat_26a1c0(q, c);
    return 1;
}
