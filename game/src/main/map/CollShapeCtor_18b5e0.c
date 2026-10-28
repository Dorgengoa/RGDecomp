/* rgp:protos */
#define RGP_SELF_CollShapeCtor_18b5e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004702C0[];

struct Obj0;

struct Obj0 {
    u8 pad000[0x30];
    void *m30;
};

struct Obj0 *CollShapeCtor_18b5e0(struct Obj0 *p0)
{
    s32 r0;

    p0->m30 = D_004702C0;
    r0 = ((s32)CollShapeInit_16d530(p0));
    return p0;
}
