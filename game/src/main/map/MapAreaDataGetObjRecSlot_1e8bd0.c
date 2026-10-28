/* rgp:protos */
#define RGP_SELF_MapAreaDataGetObjRecSlot_1e8bd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0x16C8. */

typedef struct Obj_FUN_001e8bd0 {
    u8 pad000[0x16C8];
    s16 field;         /* +0x16C8 */
} Obj_FUN_001e8bd0;

s16 MapAreaDataGetObjRecSlot_1e8bd0(Obj_FUN_001e8bd0 *o)
{
    return o->field;
}
