#include "types.h"

/* Read the s16 at +0x8. */

typedef struct Obj_FUN_003121a0 {
    u8 pad000[0x8];
    s16 field;         /* +0x8 */
} Obj_FUN_003121a0;

s16 CharaRefGetCompCount_3121a0(Obj_FUN_003121a0 *o)
{
    return o->field;
}
