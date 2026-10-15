#include "types.h"

extern s32 NpcObjInit_2fcd50(void *);
extern void * GetGameData_1fede0(void);
extern void * GroupGetRecordById_41c2a0(s32, s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;
struct Obj2;
struct Obj3;

struct Obj0 {
    u16 m00;
    u8 pad002[0xC4];
    s16 mC6;
};

struct Obj1 {
    u8 pad000[0x8];
    struct Obj2 *m08;
};

struct Obj2 {
    u8 pad000[0x6C];
    s32 m6C;
};

struct Obj3 {
    u8 pad000[0x4C];
    s32 m4C;
    s32 m50;
    s16 m54;
};

struct Obj3 *NpcObjBindMark_2fbaa0(struct Obj0 *p0, s32 p1)
{
    s32 r0;
    u16 t0;
    struct Obj1 *r1;
    struct Obj2 * t1;
    s16 t2;
    s32 t3;
    struct Obj3 *r2;
    s32 t4;
    s32 t5;

    r0 = NpcObjInit_2fcd50(p0);
    t0 = p0->m00;
    p0->m00 = (t0 | 1);
    p0->mC6 = p1;
    r1 = GetGameData_1fede0();
    t1 = r1->m08;
    t2 = p0->mC6;
    t3 = r1->m08->m6C;
    r2 = GroupGetRecordById_41c2a0(t3, t2, -1, 1);
    if (r2 != 0) {
        t4 = r2->m50;
        if (t4 == 0) {
            t5 = r2->m4C;
            r2->m50 = t5;
            r2->m54 = 0;
        }
    }
    return r2;
}
