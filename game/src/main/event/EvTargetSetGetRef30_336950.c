/* rgp:protos */
#define RGP_SELF_EvTargetSetGetRef30_336950 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the sub-object at +0x30. */

typedef struct Obj_FUN_00336950 {
    u8 pad000[0x30];
    u8 sub[1];         /* +0x30 */
} Obj_FUN_00336950;

void *EvTargetSetGetRef30_336950(Obj_FUN_00336950 *o)
{
    return o->sub;
}
