/* rgp:protos */
#define RGP_SELF_NavEdgeGetFlags_311710 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x4. */

typedef struct Obj_FUN_00311710 {
    u8 pad000[0x4];
    s32 field;         /* +0x4 */
} Obj_FUN_00311710;

s32 NavEdgeGetFlags_311710(Obj_FUN_00311710 *o)
{
    return o->field;
}
