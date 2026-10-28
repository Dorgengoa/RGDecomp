/* rgp:protos */
#define RGP_SELF_MinimapSetFadeAlpha_32a1d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the f32 at +0xEC. */

typedef struct Obj_FUN_0032a1d0 {
    u8 pad000[0xEC];
    f32 field;         /* +0xEC */
} Obj_FUN_0032a1d0;

void MinimapSetFadeAlpha_32a1d0(Obj_FUN_0032a1d0 *o, f32 value)
{
    o->field = value;
}
