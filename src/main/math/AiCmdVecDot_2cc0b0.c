#include "types.h"

struct B2cc0b0 { u8 d[0x30]; };

extern void ScriptSlotsToVec4_2cc920(f32 *v, void *p);
extern f32 Vu0InnerProduct_13bd60(f32 *a, f32 *b);
extern void ScriptSlotStoreFloatRef_2cc8e0(void *p, f32 x);

s32 AiCmdVecDot_2cc0b0(struct B2cc0b0 *p, s32 kind)
{
    f32 a[3];
    f32 b[3];

    if (kind != 7) {
        return 0;
    }
    ScriptSlotsToVec4_2cc920(a, p);
    ScriptSlotsToVec4_2cc920(b, (u8 *)p + 0x18);
    p = (struct B2cc0b0 *)((u8 *)p + 0x30);
    ScriptSlotStoreFloatRef_2cc8e0(p, Vu0InnerProduct_13bd60(a, b));
    return 1;
}
