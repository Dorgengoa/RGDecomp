/* rgp:protos */
#define RGP_SELF_MapSetSlot2AreaId_1e4120 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s16 at +0x6. */

typedef struct Obj_FUN_001e4120 {
    u8 pad000[0x6];
    s16 field;         /* +0x6 */
} Obj_FUN_001e4120;

void MapSetSlot2AreaId_1e4120(Obj_FUN_001e4120 *o, s16 value)
{
    o->field = value;
}
