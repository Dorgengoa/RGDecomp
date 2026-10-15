#include "types.h"

/* Read the s16 at +0x1C8. */

typedef struct Obj_FUN_001dc350 {
    u8 pad000[0x1C8];
    s16 field;         /* +0x1C8 */
} Obj_FUN_001dc350;

s16 MapAreaGetActiveShareCount_1dc350(Obj_FUN_001dc350 *o)
{
    return o->field;
}
