#include "types.h"

typedef struct E8 { s32 a; s32 b; } E8;

extern f32 ScriptSlotGetFloat_334890(E8 *p);
extern f32 Acosf_129178(f32 x);
extern void ScriptSlotStoreFloatRef_3347d0(E8 *p, f32 x);

s32 ScriptCmdAcos_334290(E8 *a0, s32 mode)
{
    E8 *p;
    f32 v;

    p = a0;
    if (mode == 2) {
        goto body;
    }
    return 0;
body:
    v = ScriptSlotGetFloat_334890(p++);
    ScriptSlotStoreFloatRef_3347d0(p, Acosf_129178(v));
    return 1;
}
