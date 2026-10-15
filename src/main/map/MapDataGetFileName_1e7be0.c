#include "types.h"

/* Read the s32 at +0x10. */

typedef struct Obj_FUN_001e7be0 {
    u8 pad000[0x10];
    s32 field;         /* +0x10 */
} Obj_FUN_001e7be0;

s32 MapDataGetFileName_1e7be0(Obj_FUN_001e7be0 *o)
{
    return o->field;
}
