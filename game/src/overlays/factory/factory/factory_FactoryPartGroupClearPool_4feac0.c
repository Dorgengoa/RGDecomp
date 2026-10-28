/* rgp:protos */
#define RGP_SELF_factory_FactoryPartGroupClearPool_4feac0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S { u8 pad00[0xC]; s16 f0C; s16 f0E; s32 f10; } S;

void factory_FactoryPartGroupClearPool_4feac0(S *p)
{
    p->f0C = 0;
    p->f0E = 0;
    p->f10 = 0;
}
