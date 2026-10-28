/* rgp:protos */
#define RGP_SELF_MapBlockGetLocationId_1e0070 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0x6C. */

typedef struct Obj_FUN_001e0070 {
    u8 pad000[0x6C];
    s16 field;         /* +0x6C */
} Obj_FUN_001e0070;

s16 MapBlockGetLocationId_1e0070(Obj_FUN_001e0070 *o)
{
    return o->field;
}
