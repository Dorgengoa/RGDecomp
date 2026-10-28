/* rgp:protos */
#define RGP_SELF_MapDataSetParentId_1e7480 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s16 at +0x1C. */

typedef struct Obj_FUN_001e7480 {
    u8 pad000[0x1C];
    s16 field;         /* +0x1C */
} Obj_FUN_001e7480;

void MapDataSetParentId_1e7480(Obj_FUN_001e7480 *o, s16 value)
{
    o->field = value;
}
