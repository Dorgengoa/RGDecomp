#include "types.h"

/* Zero the s32 at +0x248. */

typedef struct Obj_FUN_00183940 {
    u8 pad000[0x248];
    s32 field;         /* +0x248 */
} Obj_FUN_00183940;

void PadClearStickDpadThreshold_183940(Obj_FUN_00183940 *o)
{
    o->field = 0;
}
