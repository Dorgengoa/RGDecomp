#include "types.h"

extern void AttackChainStateInit_382ed0(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x8];
    s16 m08;
};

void AttackChainStateInitIdle_382f90(struct Obj0 *p0)
{
    AttackChainStateInit_382ed0(p0);
    p0->m08 = 0;
}
