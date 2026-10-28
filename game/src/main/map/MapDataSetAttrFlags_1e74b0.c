/* rgp:protos */
#define RGP_SELF_MapDataSetAttrFlags_1e74b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s32 at +0x28. */

typedef struct Obj_FUN_001e74b0 {
    u8 pad000[0x28];
    s32 field;         /* +0x28 */
} Obj_FUN_001e74b0;

void MapDataSetAttrFlags_1e74b0(Obj_FUN_001e74b0 *o, s32 value)
{
    o->field = value;
}
