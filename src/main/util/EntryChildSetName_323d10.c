#include "types.h"

extern s32 strlen(s32);
extern s32 MemStackNew_14e1b0(s32, s32);
extern void memset(s32, s32, s32);
extern s32 strcpy(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
};

s32 EntryChildSetName_323d10(struct Obj0 *p0, s32 p1, s32 p2)
{
    s32 r0;
    s32 r1;
    s32 t0;
    s32 r3;

    r0 = strlen(p2);
    r1 = MemStackNew_14e1b0(r0, p1);
    p0->m00 = r1;
    memset(r1, 0, r0);
    t0 = p0->m00;
    r3 = strcpy(t0, p2);
    return 1;
}
