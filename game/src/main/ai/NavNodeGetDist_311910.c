/* rgp:protos */
#define RGP_SELF_NavNodeGetDist_311910 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the f32 at +0x20. */

typedef struct Obj_FUN_00311910 {
    u8 pad000[0x20];
    f32 field;         /* +0x20 */
} Obj_FUN_00311910;

f32 NavNodeGetDist_311910(Obj_FUN_00311910 *o)
{
    return o->field;
}
