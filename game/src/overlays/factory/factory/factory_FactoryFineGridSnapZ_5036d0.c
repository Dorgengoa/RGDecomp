/* rgp:protos */
#define RGP_SELF_factory_FactoryFineGridSnapZ_5036d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S { u8 pad00[0x4]; } S;

/*rgp*/
/*rgp*/

float factory_FactoryFineGridSnapZ_5036d0(S *p, float rgp_f0)
{
    return factory_FactoryFineGridCellCenterZ_503790(p, factory_FactoryFineGridRowFromZ_503fc0(p, (float)rgp_f0));
}
