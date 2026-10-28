/* rgp:protos */
#define RGP_SELF_MapLinkSetAngle_1e91f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the f32 at +0x14. */

typedef struct Obj_FUN_001e91f0 {
    u8 pad000[0x14];
    f32 field;         /* +0x14 */
} Obj_FUN_001e91f0;

void MapLinkSetAngle_1e91f0(Obj_FUN_001e91f0 *o, f32 value)
{
    o->field = value;
}
