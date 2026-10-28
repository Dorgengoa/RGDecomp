/* rgp:protos */
#define RGP_SELF_MapDataSetRotY_1e7400 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the f32 at +0x3C. */

typedef struct Obj_FUN_001e7400 {
    u8 pad000[0x3C];
    f32 field;         /* +0x3C */
} Obj_FUN_001e7400;

void MapDataSetRotY_1e7400(Obj_FUN_001e7400 *o, f32 value)
{
    o->field = value;
}
