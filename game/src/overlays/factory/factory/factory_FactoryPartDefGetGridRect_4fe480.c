/* rgp:protos */
#define RGP_SELF_factory_FactoryPartDefGetGridRect_4fe480 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S { u8 pad00[0x38]; s32 f38; s32 f3C; } S;

/*rgp*/


int factory_FactoryPartDefGetGridRect_4fe480(S *p, s32 a, s32 b, s32 c, s32 d)
{
    return factory_FactoryGridRectAt_4fe600(p, a, p->f38, p->f3C, b, c, d);
}
