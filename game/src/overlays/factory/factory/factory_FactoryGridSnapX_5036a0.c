/* rgp:protos */
#define RGP_SELF_factory_FactoryGridSnapX_5036a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

float factory_FactoryGridSnapX_5036a0(void *p, float rgp_f0)
{
    return factory_FactoryGridCellCenterX_503760(p, factory_FactoryGridColFromX_503f60(p, (float)rgp_f0));
}
