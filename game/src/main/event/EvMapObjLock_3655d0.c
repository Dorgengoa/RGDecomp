/* rgp:protos */
#define RGP_SELF_EvMapObjLock_3655d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Retail materialises the boolean (`sltu $0,x` + `xori 1`) and then branches on
   it, which only happens when the `!` result is bound to a variable: written
   directly in the `if`, mwcc folds it to a single compare. */
void EvMapObjLock_3655d0(u8 *o)
{
    u32 flags;
    s32 t;

    flags = *(u32 *)(o + 0xD0);
    t = !(flags & 0x80000000);
    if (t) {
        if ((flags & 0x2000000) != 0) {
            EvObjLockNop_2f9a10();
        }
    }
}
