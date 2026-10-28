/* rgp:protos */
#define RGP_SELF_NavNodeResetDist_311820 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S318 {
    u8  pad000[0x1E];
    s16 f1E;
    f32 f20;
} S318;

extern f32 D_0045B080[];

void NavNodeResetDist_311820(S318 *p)
{
    p->f1E = -1;
    p->f20 = (f32)1000000 * D_0045B080[0];
}
