#include "types.h"

/* A CHAINED pool lookup: try list A, otherwise subtract its count and try
   list B.  The accessor's own `i >= 0 && i < p->m7C` test appears TWICE in
   the object (`bltz`/`slt` then `bltzl`/`slt` reusing the CSE'd count), so
   the ternary really is written out inside the taken arm.
   Strides read off this unit's OWN listing: sll 1, addu, sll 3 -> 24 for A,
   sll 5 -> 32 for B. */

typedef struct Pool {
    u8   pad000[0x7C];
    s16  m7C;
    u8   pad07E[0xE];
    u8  *m8C;
} Pool;

typedef struct Q413800 {
    u8    pad000[0x8];
    Pool *m8;
    Pool *mC;
} Q413800;

void *TwoTableViewGetAt_413800(Q413800 *q, s32 i)
{
    Pool *a;
    Pool *b;
    s32   n;
    s32   m;

    a = q->m8;
    if (a != 0) {
        n = a->m7C;
        if (i >= 0 && i < n) {
            return (i >= 0 && i < a->m7C) ? (void *)(a->m8C + i * 24)
                                          : (void *)0;
        }
        i -= n;
    }
    b = q->mC;
    /* mirror of the A arm: the payload is the THEN of `b != 0` and the single
       `return 0` sits after it, so mwcc threads the zero into the `beql`
       slot.  Spelling it `if (b == 0) return 0;` costs two words, and reading
       the count inline instead of into `m` costs a third. */
    if (b != 0) {
        m = b->m7C;
        if (i >= 0 && i < m) {
            return (i >= 0 && i < b->m7C) ? (void *)(b->m8C + i * 32)
                                          : (void *)0;
        }
    }
    return 0;
}
