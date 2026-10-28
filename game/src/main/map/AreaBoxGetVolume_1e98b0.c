/* rgp:protos */
#define RGP_SELF_AreaBoxGetVolume_1e98b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the f32 at +0x18. */

typedef struct Obj_FUN_001e98b0 {
    u8 pad000[0x18];
    f32 field;         /* +0x18 */
} Obj_FUN_001e98b0;

f32 AreaBoxGetVolume_1e98b0(Obj_FUN_001e98b0 *o)
{
    return o->field;
}
