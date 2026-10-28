/* rgp:protos */
#define RGP_SELF_CollMeshInit_16d3e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void memset(void *, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
    s32 m04;
    u8 pad008[0x38];
    s32 m40;
    s32 m44;
    s32 m48;
    s32 m4C;
    s32 m50;
    s32 m54;
    s32 m58;
};

void CollMeshInit_16d3e0(struct Obj0 *p0)
{
    p0->m00 = 0;
    p0->m04 = 0;
    memset((struct Obj0 *)((u8 *)p0 + 0x10), 0, 0x20);
    p0->m40 = 0;
    p0->m44 = 0;
    p0->m48 = 0;
    p0->m4C = 0;
    p0->m50 = 0;
    p0->m54 = 0;
    p0->m58 = 0;
}
