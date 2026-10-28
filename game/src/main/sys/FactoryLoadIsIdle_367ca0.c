/* rgp:protos */
#define RGP_SELF_FactoryLoadIsIdle_367ca0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/*rgp*/
/*rgp*/

s32 FactoryLoadIsIdle_367ca0(void)
{
    void *p;

    p = GetFactoryObj_367f30();
    if (p != 0) {
        return func_504840(p);
    }
    return 0;
}
