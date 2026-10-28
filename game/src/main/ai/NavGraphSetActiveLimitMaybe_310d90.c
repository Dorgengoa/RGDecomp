/* rgp:protos */
#define RGP_SELF_NavGraphSetActiveLimitMaybe_310d90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the f32 at +0x108. */

typedef struct Obj_FUN_00310d90 {
    u8 pad000[0x108];
    f32 field;         /* +0x108 */
} Obj_FUN_00310d90;

void NavGraphSetActiveLimitMaybe_310d90(Obj_FUN_00310d90 *o, f32 value)
{
    o->field = value;
}
