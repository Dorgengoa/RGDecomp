#include "types.h"

struct B334160 { u8 d[0x30]; };

extern void ScriptSlotsToVec4_334810(f32 *v, void *p);
extern f32 Vu0InnerProduct_13bd60(f32 *a, f32 *b);
extern void ScriptSlotStoreFloatRef_3347d0(void *p, f32 x);

s32 ScriptCmdVecDot_334160(struct B334160 *p, s32 kind)
{
    f32 a[3];
    f32 b[3];

    if (kind != 7) {
        return 0;
    }
    ScriptSlotsToVec4_334810(a, p);
    ScriptSlotsToVec4_334810(b, (u8 *)p + 0x18);
    p = (struct B334160 *)((u8 *)p + 0x30);
    ScriptSlotStoreFloatRef_3347d0(p, Vu0InnerProduct_13bd60(a, b));
    return 1;
}
