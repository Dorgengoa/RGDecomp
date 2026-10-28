/* rgp:protos */
#define RGP_SELF_ListNodeNext_18c4f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x0. */

typedef struct Obj_FUN_0018c4f0 {
    s32 field;         /* +0x00 */
} Obj_FUN_0018c4f0;

s32 ListNodeNext_18c4f0(Obj_FUN_0018c4f0 *o)
{
    return o->field;
}
