/* rgp:protos */
#define RGP_SELF_EvTargetGetXform_352970 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the sub-object at +0x38. */

typedef struct Obj_FUN_00352970 {
    u8 pad000[0x38];
    u8 sub[1];         /* +0x38 */
} Obj_FUN_00352970;

void *EvTargetGetXform_352970(Obj_FUN_00352970 *o)
{
    return o->sub;
}
