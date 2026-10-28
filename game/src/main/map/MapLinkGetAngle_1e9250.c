/* rgp:protos */
#define RGP_SELF_MapLinkGetAngle_1e9250 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the f32 at +0x14. */

typedef struct Obj_FUN_001e9250 {
    u8 pad000[0x14];
    f32 field;         /* +0x14 */
} Obj_FUN_001e9250;

f32 MapLinkGetAngle_1e9250(Obj_FUN_001e9250 *o)
{
    return o->field;
}
