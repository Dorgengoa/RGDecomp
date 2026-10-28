/* rgp:protos */
#define RGP_SELF_MapDataSetName_1e7500 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s32 at +0xC. */

typedef struct Obj_FUN_001e7500 {
    u8 pad000[0xC];
    s32 field;         /* +0xC */
} Obj_FUN_001e7500;

void MapDataSetName_1e7500(Obj_FUN_001e7500 *o, s32 value)
{
    o->field = value;
}
