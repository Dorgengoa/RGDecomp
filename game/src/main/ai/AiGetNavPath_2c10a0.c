/* rgp:protos */
#define RGP_SELF_AiGetNavPath_2c10a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the sub-object at +0x1C0. */

typedef struct Obj_FUN_002c10a0 {
    u8 pad000[0x1C0];
    u8 sub[1];         /* +0x1C0 */
} Obj_FUN_002c10a0;

void *AiGetNavPath_2c10a0(Obj_FUN_002c10a0 *o)
{
    return o->sub;
}
