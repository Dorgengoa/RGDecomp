/* rgp:protos */
#define RGP_SELF_EvTargetSetGetId_336970 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0x114. */

typedef struct Obj_FUN_00336970 {
    u8 pad000[0x114];
    s16 field;         /* +0x114 */
} Obj_FUN_00336970;

s16 EvTargetSetGetId_336970(Obj_FUN_00336970 *o)
{
    return o->field;
}
