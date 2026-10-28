/* rgp:protos */
#define RGP_SELF_factory_FactoryPartDefGetFineGridPoint_4fe4e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct A {
    u8  pad00[0x20];
    s32 f20;
    s32 f24;
} A;

/*rgp*/

int factory_FactoryPartDefGetFineGridPoint_4fe4e0(A *o, s32 b, s32 c, s32 d, s32 e)
{
    return factory_FactoryGridPointAt_4fe7c0(o, b, o->f20, o->f24, c, d, e);
}
