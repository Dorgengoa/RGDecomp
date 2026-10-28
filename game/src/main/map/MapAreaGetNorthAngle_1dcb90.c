/* rgp:protos */
#define RGP_SELF_MapAreaGetNorthAngle_1dcb90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the f32 at +0xF8. */

typedef struct Obj_FUN_001dcb90 {
    u8 pad000[0xF8];
    f32 field;         /* +0xF8 */
} Obj_FUN_001dcb90;

f32 MapAreaGetNorthAngle_1dcb90(Obj_FUN_001dcb90 *o)
{
    return o->field;
}
