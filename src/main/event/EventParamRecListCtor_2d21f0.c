#include "types.h"

extern s32 DListInit_42eae0(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004715A8[];
extern u8 D_004715B8[];
extern u8 D_004715C8[];

struct Obj0;

struct Obj0 {
    u8 pad000[0xC];
    void *m0C;
};

struct Obj0 *EventParamRecListCtor_2d21f0(struct Obj0 *p0)
{
    s32 r0;
    s32 r1;
    s32 r2;
    s32 r3;

    r0 = DListInit_42eae0(p0);
    p0->m0C = D_004715A8;
    r1 = DListInit_42eae0(p0);
    p0->m0C = D_004715B8;
    r2 = DListInit_42eae0(p0);
    p0->m0C = D_004715C8;
    r3 = DListInit_42eae0(p0);
    return p0;
}
