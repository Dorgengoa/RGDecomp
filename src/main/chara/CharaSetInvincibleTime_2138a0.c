#include "types.h"

/* Write the f32 at +0xAE0. */

typedef struct Obj_FUN_002138a0 {
    u8 pad000[0xAE0];
    f32 field;         /* +0xAE0 */
} Obj_FUN_002138a0;

void CharaSetInvincibleTime_2138a0(Obj_FUN_002138a0 *o, f32 value)
{
    o->field = value;
}
