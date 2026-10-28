/* rgp:protos */
#define RGP_SELF_TextReaderGetChar_15eb90 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    s32 m00;
    s32 m04;
    s32 m08;
};

struct Obj1 {
    s32 m00;
};

u8 TextReaderGetChar_15eb90(struct Obj0 *p0, struct Obj1 *p1)
{
    s32 t0;
    s32 t1;
    u8 t2;
    s32 t3;
    s32 t4;

    t0 = p0->m00;
    t1 = p0->m08;
    t2 = *(u8 *)((u8 *)t0 + t1);
    p1->m00 = t2;
    t3 = p0->m08;
    p0->m08 = (t3 + 1);
    t4 = p0->m04;
    return (t4 >= (t3 + 1));
}
