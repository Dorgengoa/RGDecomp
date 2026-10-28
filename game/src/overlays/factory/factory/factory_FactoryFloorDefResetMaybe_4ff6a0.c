/* rgp:protos */
#define RGP_SELF_factory_FactoryFloorDefResetMaybe_4ff6a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct A {
    s16 f00;
    s8  f02;
    s8  f03;
    s16 f04;
    s16 f06;
    s32 f08;
    s32 f0C;
    s32 f10;
    s32 f14;
} A;

void factory_FactoryFloorDefResetMaybe_4ff6a0(A *p)
{
    p->f00 = -1;
    p->f02 = 0;
    p->f03 = 0;
    p->f04 = 0;
    p->f06 = 0;
    p->f08 = 0;
    p->f0C = 0;
    p->f10 = 0;
    p->f14 = 0;
}
