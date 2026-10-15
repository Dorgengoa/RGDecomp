#include "types.h"

extern s32 DListInit_42eae0(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00471548[];
extern u8 D_00471558[];
extern u8 D_00471568[];

struct Obj0;

struct Obj0 {
    u8 pad000[0xC];
    void *m0C;
};

struct Obj0 *EventPathRecListCtor_2d22d0(struct Obj0 *p0)
{
    s32 r0;
    s32 r1;
    s32 r2;
    s32 r3;

    r0 = DListInit_42eae0(p0);
    p0->m0C = D_00471548;
    r1 = DListInit_42eae0(p0);
    p0->m0C = D_00471558;
    r2 = DListInit_42eae0(p0);
    p0->m0C = D_00471568;
    r3 = DListInit_42eae0(p0);
    return p0;
}
