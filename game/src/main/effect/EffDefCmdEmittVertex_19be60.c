/* rgp:protos */
#define RGP_SELF_EffDefCmdEmittVertex_19be60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Retail falls through into the `return 0`, so the guard is written
   `if (o->m2C == 0) return 0;`. */

/*rgp*/
/*rgp*/

s32 EffDefCmdEmittVertex_19be60(void *args, s32 n, void **ctx)
{
    u8 *o = (u8 *)ctx[0];

    if (*(void **)(o + 0x2C) == 0) {
        return 0;
    }
    EffObjSetVertexSelectMode_1a9750(*(void **)(o + 0x2C), SlotGetInt_15f720(args));
    return 1;
}
