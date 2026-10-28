/* rgp:protos */
#define RGP_SELF_NavNodeSetDist_311850 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the f32 at +0x20. */

typedef struct Obj_FUN_00311850 {
    u8 pad000[0x20];
    f32 field;         /* +0x20 */
} Obj_FUN_00311850;

void NavNodeSetDist_311850(Obj_FUN_00311850 *o, f32 value)
{
    o->field = value;
}
