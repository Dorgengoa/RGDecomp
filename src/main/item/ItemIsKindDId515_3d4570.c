#include "types.h"

typedef struct Q4570 {
    u8 pad000[0x2];
    s8 m2;
    u8 pad003[0x1];
    s16 m4;
} Q4570;

typedef struct P4570 {
    u8 pad000[0x10];
    Q4570 *m10;
} P4570;

s32 ItemIsKindDId515_3d4570(P4570 *p)
{
    Q4570 *q;
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
        if (v == 0x515) {
            r = 1;
        } else {
            r = 0;
        }
    } else {
        r = 0;
    }
    return r;
}
