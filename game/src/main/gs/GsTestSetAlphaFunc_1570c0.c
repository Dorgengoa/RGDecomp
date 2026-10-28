/* rgp:protos */
#define RGP_SELF_GsTestSetAlphaFunc_1570c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S001570C0 {
    u8 pad0[0x20];
    __extension__ unsigned short b0 : 1;               /* +0x20 */
    unsigned short b1 : 3;
    unsigned short b4 : 8;
    unsigned short b12 : 4;
} __attribute__((aligned(2))) S001570C0;

void GsTestSetAlphaFunc_1570c0(S001570C0 *p, s32 a, s32 b)
{
    p->b1 = a;
    p->b4 = b;
}
