/* rgp:protos */
#define RGP_SELF_MapDataGetId_1e7bd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0x18. */

typedef struct Obj_FUN_001e7bd0 {
    u8 pad000[0x18];
    s16 field;         /* +0x18 */
} Obj_FUN_001e7bd0;

s16 MapDataGetId_1e7bd0(Obj_FUN_001e7bd0 *o)
{
    return o->field;
}
