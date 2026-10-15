#include "types.h"

/* Plain initialiser.  The bitfield insert at 0x1C (lbu / and -2 / or (v&1) / sb)
   is a one-bit field assigned 0 -- the `andi $5,$0,1` masking a literal zero is
   the tell.  The duplicated `sh -1, 0xA` is TWO source statements: retail
   stores 0xA twice, so the source does too. */

typedef struct {
    s32 m00;
    s32 m04;
    s16 m08;
    s16 m0A;
    s16 m0C;
    s16 m0E;
    s32 m10;
    s32 m14;
    s32 m18;
    u32 b0 : 1;
} S40A0;

void HandleEntryInit_3f40a0(S40A0 *p)
{
    p->m00 = 0;
    p->m0A = -1;
    p->m0A = -1;
    p->m08 = 0;
    p->m0C = -1;
    p->m10 = -1;
    p->m14 = 0;
    p->m18 = 0;
    p->b0 = 0;
}
