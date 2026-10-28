/* rgp:protos */
#define RGP_SELF_MinimapGetFadeDuration_32a160 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the f32 at +0xF4. */

typedef struct Obj_FUN_0032a160 {
    u8 pad000[0xF4];
    f32 field;         /* +0xF4 */
} Obj_FUN_0032a160;

f32 MinimapGetFadeDuration_32a160(Obj_FUN_0032a160 *o)
{
    return o->field;
}
