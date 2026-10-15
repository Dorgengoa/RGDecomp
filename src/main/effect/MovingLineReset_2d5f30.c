#include "types.h"

/* Zero the s16 at +0x120. */

typedef struct Obj_FUN_002d5f30 {
    u8 pad000[0x120];
    s16 field;         /* +0x120 */
} Obj_FUN_002d5f30;

void MovingLineReset_2d5f30(Obj_FUN_002d5f30 *o)
{
    o->field = 0;
}
