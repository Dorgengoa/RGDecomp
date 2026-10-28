/* rgp:protos */
#define RGP_SELF_MapDataSetId_1e74e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s16 at +0x18. */

typedef struct Obj_FUN_001e74e0 {
    u8 pad000[0x18];
    s16 field;         /* +0x18 */
} Obj_FUN_001e74e0;

void MapDataSetId_1e74e0(Obj_FUN_001e74e0 *o, s16 value)
{
    o->field = value;
}
