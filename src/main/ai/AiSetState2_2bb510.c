#include "types.h"

/* Write the s16 at +0xB0. */

typedef struct Obj_FUN_002bb510 {
    u8 pad000[0xB0];
    s16 field;         /* +0xB0 */
} Obj_FUN_002bb510;

void AiSetState2_2bb510(Obj_FUN_002bb510 *o, s16 value)
{
    o->field = value;
}
