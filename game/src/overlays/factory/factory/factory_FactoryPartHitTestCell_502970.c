/* rgp:protos */
#define RGP_SELF_factory_FactoryPartHitTestCell_502970 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s32 factory_FactoryPartHitTestCell_502970(s32 a, s32 b, s32 c, void *d, s32 e, s32 f)
{
    if (d != 0) {
        return factory_FactoryPartDefGridRectHitTest_4fe930(d, b, c, e, f);
    }
    return 0;
}
