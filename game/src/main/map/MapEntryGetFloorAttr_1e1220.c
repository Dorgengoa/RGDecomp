/* rgp:protos */
#define RGP_SELF_MapEntryGetFloorAttr_1e1220 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x79C. */

typedef struct Obj_FUN_001e1220 {
    u8 pad000[0x79C];
    s32 field;         /* +0x79C */
} Obj_FUN_001e1220;

s32 MapEntryGetFloorAttr_1e1220(Obj_FUN_001e1220 *o)
{
    return o->field;
}
