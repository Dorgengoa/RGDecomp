/* rgp:protos */
#define RGP_SELF_MenuGetScrollStep_29f9a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the f32 at +0xF4. */

typedef struct Obj_FUN_0029f9a0 {
    u8 pad000[0xF4];
    f32 field;         /* +0xF4 */
} Obj_FUN_0029f9a0;

f32 MenuGetScrollStep_29f9a0(Obj_FUN_0029f9a0 *o)
{
    return o->field;
}
