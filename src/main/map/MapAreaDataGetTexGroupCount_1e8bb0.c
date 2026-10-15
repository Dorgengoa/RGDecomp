#include "types.h"

/* Read the s32 at +0x16C4. */

typedef struct Obj_FUN_001e8bb0 {
    u8 pad000[0x16C4];
    s32 field;         /* +0x16C4 */
} Obj_FUN_001e8bb0;

s32 MapAreaDataGetTexGroupCount_1e8bb0(Obj_FUN_001e8bb0 *o)
{
    return o->field;
}
