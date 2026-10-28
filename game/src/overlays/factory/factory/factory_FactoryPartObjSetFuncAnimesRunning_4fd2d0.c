/* rgp:protos */
#define RGP_SELF_factory_FactoryPartObjSetFuncAnimesRunning_4fd2d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Sub { u8 pad00[0x138]; s32 f138; } Sub;
typedef struct S { u8 pad00[0x20]; Sub *f20; } S;

void factory_FactoryPartObjSetFuncAnimesRunning_4fd2d0(S *p, s32 a, s32 b)
{
    p->f20->f138 = (u8)!b;
}
