#include "types.h"

/* Known-positive sibling shape of AttackObjCtor_3175c0 (byte-identical, in cunits). */

extern s32 ModelObjExCtor_1c4920(void *, s32, s32, s32, f32);

extern u8 D_00470F50[];

struct Obj0;

struct Obj0 {
    u8 pad000[0x1B0];
    void *m1B0;
};

struct Obj0 *MapEntryCtor_1df710(struct Obj0 *p0, s32 p1, s32 p2, s32 p3, f32 fa0)
{
    s32 r0;

    r0 = ModelObjExCtor_1c4920(p0, p1, p2, p3, fa0);
    p0->m1B0 = D_00470F50;
    return p0;
}
