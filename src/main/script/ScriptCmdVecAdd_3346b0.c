#include "types.h"

struct Node {
    u8 pad00[0x4];
    f32 m04;
};

struct Obj {
    u8 pad00[0x4];
    struct Node *m04;
    u8 pad08[0x4];
    struct Node *m0C;
    u8 pad10[0x4];
    struct Node *m14;
};

extern void ScriptSlotsToVec4_334810(f32 *out, void *src);
extern void ScriptSlotStoreFloatRef_3347d0(void *a, f32 v);

s32 ScriptCmdVecAdd_3346b0(struct Obj *o, s32 mode)
{
    f32 v[3];

    if (mode != 6) {
        return 0;
    }
    ScriptSlotsToVec4_334810(v, (u8 *)o + 0x18);
    ScriptSlotStoreFloatRef_3347d0(o, o->m04->m04 + v[0]);
    ScriptSlotStoreFloatRef_3347d0((u8 *)o + 8, o->m0C->m04 + v[1]);
    ScriptSlotStoreFloatRef_3347d0((u8 *)o + 0x10, o->m14->m04 + v[2]);
    return 1;
}
