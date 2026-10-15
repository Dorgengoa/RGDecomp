#include "types.h"

typedef struct S001570C0 {
    u8 pad0[0x20];
    u16 b0 : 1;               /* +0x20 */
    u16 b1 : 3;
    u16 b4 : 8;
    u16 b12 : 4;
} S001570C0;

void GsTestSetAlphaFunc_1570c0(S001570C0 *p, s32 a, s32 b)
{
    p->b1 = a;
    p->b4 = b;
}
