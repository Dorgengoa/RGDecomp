#include "types.h"

/* Read the s32 at +0x16C0. */

typedef struct Obj_FUN_001e8bc0 {
    u8 pad000[0x16C0];
    s32 field;         /* +0x16C0 */
} Obj_FUN_001e8bc0;

s32 MapAreaDataGetTexGroupBase_1e8bc0(Obj_FUN_001e8bc0 *o)
{
    return o->field;
}
