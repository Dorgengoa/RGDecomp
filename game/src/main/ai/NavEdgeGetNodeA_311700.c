/* rgp:protos */
#define RGP_SELF_NavEdgeGetNodeA_311700 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0x0. */

typedef struct Obj_FUN_00311700 {
    s16 field;         /* +0x00 */
} Obj_FUN_00311700;

s16 NavEdgeGetNodeA_311700(Obj_FUN_00311700 *o)
{
    return o->field;
}
