#include "types.h"

extern s32 StrSizeWithNul_1cac60(void *);
extern void * StrArenaAlloc_23fd40(s32);
extern s32 strcpy(void *, void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 m00;
};

struct Obj1 {
    s8 m00;
};

struct Obj0 *StrDupArena_23fc40(struct Obj1 *p0)
{
    s32 r0;
    struct Obj0 *r1;
    s8 t0;
    s32 rv3;
    s32 r2;

    r0 = StrSizeWithNul_1cac60(p0);
    r1 = StrArenaAlloc_23fd40(r0);
    if (r1 == 0) {
        return (struct Obj0 *)0;
    }
    r1->m00 = 0;
    if (p0 != 0) {
        t0 = p0->m00;
        rv3 = 0;
        if (t0 != 0) {
            r2 = strcpy(r1, p0);
            rv3 = r2;
        }
    }
    return r1;
}
