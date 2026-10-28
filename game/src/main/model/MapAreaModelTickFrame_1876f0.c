/* rgp:protos */
#define RGP_SELF_MapAreaModelTickFrame_1876f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S1876 {
    u8  pad000[0x1674];
    f32 f1674;
    s32 f1678;
} S1876;

void MapAreaModelTickFrame_1876f0(S1876 *p)
{
    p->f1674 = p->f1674 + 1.0f;
    p->f1678 = (s32)p->f1674;
}
