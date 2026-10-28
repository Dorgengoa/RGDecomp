/* rgp:protos */
#define RGP_SELF_normal_BtlChgPageStop_505fd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00505FD0 -- store 1 at 0x43E, then one call, then return 1.
 * The `sh` rides the jal delay slot; the `addiu $2,1` above the sd is the
 * scheduler hoisting the shared return value. */
/*rgp*/

s32 normal_BtlChgPageStop_505fd0(void *p)
{
    *(s16 *)((u8 *)p + 0x43E) = 1;
    normal_BtlChgPageSetStateId_5061d0(p, -1);
    return 1;
}
