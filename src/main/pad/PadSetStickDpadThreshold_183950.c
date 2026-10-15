#include "types.h"

/* Write the s32 at +0x248. */

typedef struct Obj_FUN_00183950 {
    u8 pad000[0x248];
    s32 field;         /* +0x248 */
} Obj_FUN_00183950;

void PadSetStickDpadThreshold_183950(Obj_FUN_00183950 *o, s32 value)
{
    o->field = value;
}
