#include "types.h"

typedef struct Q4530 {
    u8 pad000[0x2];
    s8 m2;
    u8 pad003[0x1];
    s16 m4;
} Q4530;

typedef struct P4530 {
    u8 pad000[0x10];
    Q4530 *m10;
} P4530;

s32 ItemIsKindDId514_3d4530(P4530 *p)
{
    Q4530 *q;
    s32 c;
    s32 v;
    s32 r;

    /* `bne` (NOT likely) with `lh $3,0x4($3)` in its slot: the halfword
       runs on BOTH paths, so it is read BEFORE the test, and it reuses
       q's own register because q is dead by then.
       The two guards have OPPOSITE polarity -- the outer failure is the
       ELSE (a tail block reached by `bne`), the inner failure is the THEN
       (the `bnel` likely slot). */
    q = p->m10;
    c = *(volatile s8 *)&q->m2;
    v = *(volatile s16 *)&q->m4;
    if (c == 0xD) {
        if (v == 0x514) {
            r = 1;
        } else {
            r = 0;
        }
    } else {
        r = 0;
    }
    return r;
}
