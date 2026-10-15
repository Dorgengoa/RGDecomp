#include "types.h"

/* The failure block (`b <epilogue>` + nop) sits BETWEEN the guards and the
   body, so this is `if (a==0||b==0||...) return;` - the first four disjuncts
   branch straight to the epilogue, the fifth inverts past the block and takes
   a duplicated copy of the body's first store into its delay slot (which is
   why `sw $5,0x0($4)` appears twice, the second copy unreachable).
   The m14 store is the SECOND source statement. */

struct Rec {
    s32 m00;
    s32 m04;
    s32 m08;
    s32 m0C;
    s32 m10;
    s8  m14;
};

void ActInfoLocusInit_22f9d0(struct Rec *p, s32 a, s32 b, s32 c, s32 d, s32 e)
{
    p->m00 = 0;
    p->m14 = -1;
    p->m04 = 0;
    p->m08 = 0;
    p->m0C = 0;
    p->m10 = 0;
    if (a == 0 || b == 0 || c == 0 || d == 0 || e == 0) {
        return;
    }
    p->m00 = a;
    p->m04 = b;
    p->m08 = c;
    p->m0C = d;
    p->m10 = e;
}
