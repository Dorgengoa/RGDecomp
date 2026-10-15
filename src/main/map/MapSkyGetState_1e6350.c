#include "types.h"

/* Read the s16 at +0x17C4. */

typedef struct Obj_FUN_001e6350 {
    u8 pad000[0x17C4];
    s16 field;         /* +0x17C4 */
} Obj_FUN_001e6350;

s16 MapSkyGetState_1e6350(Obj_FUN_001e6350 *o)
{
    return o->field;
}
