/* rgp:protos */
#define RGP_SELF_NavNodeGetEdgeList_311940 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x14. */

typedef struct Obj_FUN_00311940 {
    u8 pad000[0x14];
    s32 field;         /* +0x14 */
} Obj_FUN_00311940;

s32 NavNodeGetEdgeList_311940(Obj_FUN_00311940 *o)
{
    return o->field;
}
