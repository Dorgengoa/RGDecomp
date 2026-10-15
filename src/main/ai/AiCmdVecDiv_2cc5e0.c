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

extern f32 ScriptSlotGetFloat_2cc9a0(void *a);
extern void ScriptSlotStoreFloatRef_2cc8e0(void *a, f32 v);

s32 AiCmdVecDiv_2cc5e0(struct Obj *o, s32 mode)
{
    f32 s;

    if (mode != 4) {
        return 0;
    }
    s = ScriptSlotGetFloat_2cc9a0((u8 *)o + 0x18);
    if (s == 0.0f) {
        return 0;
    }
    ScriptSlotStoreFloatRef_2cc8e0(o, o->m04->m04 / s);
    ScriptSlotStoreFloatRef_2cc8e0((u8 *)o + 8, o->m0C->m04 / s);
    ScriptSlotStoreFloatRef_2cc8e0((u8 *)o + 0x10, o->m14->m04 / s);
    return 1;
}
