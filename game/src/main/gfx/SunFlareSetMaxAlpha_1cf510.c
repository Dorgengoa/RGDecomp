/* rgp:protos */
#define RGP_SELF_SunFlareSetMaxAlpha_1cf510 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the f32 at +0x59D4. */

typedef struct Obj_FUN_001cf510 {
    u8 pad000[0x59D4];
    f32 field;         /* +0x59D4 */
} Obj_FUN_001cf510;

void SunFlareSetMaxAlpha_1cf510(Obj_FUN_001cf510 *o, f32 value)
{
    o->field = value;
}
