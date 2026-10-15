#include "types.h"

/* Read the s32 at +0x408. */

typedef struct Obj_FUN_00238550 {
    u8 pad000[0x408];
    s32 field;         /* +0x408 */
} Obj_FUN_00238550;

s32 CharaGetMotionPlayFlags_238550(Obj_FUN_00238550 *o)
{
    return o->field;
}
