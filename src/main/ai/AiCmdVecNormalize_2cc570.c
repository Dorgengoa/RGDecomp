#include "types.h"

typedef struct Vec4 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4;

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

extern void VecNormalize_13bd90(Vec4 *d, Vec4 *s);
extern void ScriptSlotStoreVec3_2cc8a0(struct Obj *o, Vec4 *v);

s32 AiCmdVecNormalize_2cc570(struct Obj *o)
{
    Vec4 v;

    v.x = o->m04->m04;
    v.y = o->m0C->m04;
    v.z = o->m14->m04;
    v.w = 1.0f;
    VecNormalize_13bd90(&v, &v);
    ScriptSlotStoreVec3_2cc8a0(o, &v);
    return 1;
}
