#include "types.h"

extern f32 ScriptSlotGetFloat_2cc9a0(void *);
extern void ScriptSlotStoreFloatRef_2cc8e0(void *, f32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;
struct Obj2;
struct Obj3;

struct Obj0 {
    u8 pad000[0x4];
    struct Obj1 *m04;
    u8 pad008[0x4];
    struct Obj2 *m0C;
    u8 pad010[0x4];
    struct Obj3 *m14;
};

struct Obj1 {
    u8 pad000[0x4];
    f32 m04;
};

struct Obj2 {
    u8 pad000[0x4];
    f32 m04;
};

struct Obj3 {
    u8 pad000[0x4];
    f32 m04;
};

s32 AiCmdVecScale_2cc6a0(struct Obj0 *p0, s32 p1)
{
    f32 r0;
    struct Obj1 * t0;
    f32 t1;
    struct Obj2 * t2;
    f32 t3;
    struct Obj3 * t4;
    f32 t5;

    if (p1 != 4) {
        return 0;
    }
    r0 = ScriptSlotGetFloat_2cc9a0((struct Obj0 *)((u8 *)p0 + 0x18));
    t0 = p0->m04;
    t1 = p0->m04->m04;
    ScriptSlotStoreFloatRef_2cc8e0(p0, (t1 * r0));
    t2 = p0->m0C;
    t3 = p0->m0C->m04;
    ScriptSlotStoreFloatRef_2cc8e0((struct Obj0 *)((u8 *)p0 + 8), (t3 * r0));
    t4 = p0->m14;
    t5 = p0->m14->m04;
    ScriptSlotStoreFloatRef_2cc8e0((struct Obj0 *)((u8 *)p0 + 0x10), (t5 * r0));
    return 1;
}
