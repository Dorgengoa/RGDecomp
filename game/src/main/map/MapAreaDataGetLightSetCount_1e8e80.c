/* rgp:protos */
#define RGP_SELF_MapAreaDataGetLightSetCount_1e8e80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0x16B8. */

typedef struct Obj_FUN_001e8e80 {
    u8 pad000[0x16B8];
    s16 field;         /* +0x16B8 */
} Obj_FUN_001e8e80;

s16 MapAreaDataGetLightSetCount_1e8e80(Obj_FUN_001e8e80 *o)
{
    return o->field;
}
