/* rgp:protos */
#define RGP_SELF_SunFlareSetAlpha_1cf500 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the f32 at +0x59D0. */

typedef struct Obj_FUN_001cf500 {
    u8 pad000[0x59D0];
    f32 field;         /* +0x59D0 */
} Obj_FUN_001cf500;

void SunFlareSetAlpha_1cf500(Obj_FUN_001cf500 *o, f32 value)
{
    o->field = value;
}
