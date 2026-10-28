/* rgp:protos */
#define RGP_SELF_AreaBoxGetTopY_1e98a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the f32 at +0x44. */

typedef struct Obj_FUN_001e98a0 {
    u8 pad000[0x44];
    f32 field;         /* +0x44 */
} Obj_FUN_001e98a0;

f32 AreaBoxGetTopY_1e98a0(Obj_FUN_001e98a0 *o)
{
    return o->field;
}
