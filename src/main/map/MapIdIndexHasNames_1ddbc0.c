#include "types.h"

/* Is the s32 at +0x4 non-zero? */

typedef struct Obj_FUN_001ddbc0 {
    u8 pad000[0x4];
    s32 field;         /* +0x4 */
} Obj_FUN_001ddbc0;

u8 MapIdIndexHasNames_1ddbc0(Obj_FUN_001ddbc0 *o)
{
    u8 set;

    set = o->field != 0;
    return set;
}
