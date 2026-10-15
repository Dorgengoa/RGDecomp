#include "types.h"

/* Write the s32 at +0x8. */

typedef struct Obj_FUN_003eddf0 {
    u8 pad000[0x8];
    s32 field;         /* +0x8 */
} Obj_FUN_003eddf0;

void GameDataSetWorld_3eddf0(Obj_FUN_003eddf0 *o, s32 value)
{
    o->field = value;
}
