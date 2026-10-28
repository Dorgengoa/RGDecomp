/* rgp:protos */
#define RGP_SELF_factory_FactoryGridSnapZ_503670 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S { u8 pad00[0x4]; } S;

/*rgp*/
/*rgp*/

float factory_FactoryGridSnapZ_503670(S *p, float rgp_f0)
{
    return factory_FactoryGridCellCenterZ_503730(p, factory_FactoryGridRowFromZ_503f00(p, (float)rgp_f0));
}
