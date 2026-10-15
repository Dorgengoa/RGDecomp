#include "types.h"

extern s32 NodeCtor_18c5b0(void *);
extern s32 NodeObjBasicInit_196880(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00470620[];

struct Obj0;

struct Obj0 {
    u8 pad000[0x68];
    void *m68;
};

struct Obj0 *NodeObjBasicCtor_18c570(struct Obj0 *p0)
{
    s32 r0;
    s32 r1;

    r0 = NodeCtor_18c5b0(p0);
    p0->m68 = D_00470620;
    r1 = NodeObjBasicInit_196880(p0);
    return p0;
}
