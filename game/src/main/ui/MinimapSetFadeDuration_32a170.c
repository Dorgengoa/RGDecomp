/* rgp:protos */
#define RGP_SELF_MinimapSetFadeDuration_32a170 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the f32 at +0xF4. */

typedef struct Obj_FUN_0032a170 {
    u8 pad000[0xF4];
    f32 field;         /* +0xF4 */
} Obj_FUN_0032a170;

void MinimapSetFadeDuration_32a170(Obj_FUN_0032a170 *o, f32 value)
{
    o->field = value;
}
