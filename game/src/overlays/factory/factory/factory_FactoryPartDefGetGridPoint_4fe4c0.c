/* rgp:protos */
#define RGP_SELF_factory_FactoryPartDefGetGridPoint_4fe4c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S { u8 pad00[0x28]; s32 f28; s32 f2C; } S;

/*rgp*/


int factory_FactoryPartDefGetGridPoint_4fe4c0(S *p, s32 a, s32 b, s32 c, s32 d)
{
    return factory_FactoryGridPointAt_4fe7c0(p, a, p->f28, p->f2C, b, c, d);
}
