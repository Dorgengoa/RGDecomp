/* rgp:protos */
#define RGP_SELF_MapSetSlot0AreaId_1e4140 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s16 at +0x2. */

typedef struct Obj_FUN_001e4140 {
    u8 pad000[0x2];
    s16 field;         /* +0x2 */
} Obj_FUN_001e4140;

void MapSetSlot0AreaId_1e4140(Obj_FUN_001e4140 *o, s16 value)
{
    o->field = value;
}
