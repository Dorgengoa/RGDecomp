/* rgp:protos */
#define RGP_SELF_EvTargetSetGetTargets_336940 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the sub-object at +0x60. */

typedef struct Obj_FUN_00336940 {
    u8 pad000[0x60];
    u8 sub[1];         /* +0x60 */
} Obj_FUN_00336940;

void *EvTargetSetGetTargets_336940(Obj_FUN_00336940 *o)
{
    return o->sub;
}
