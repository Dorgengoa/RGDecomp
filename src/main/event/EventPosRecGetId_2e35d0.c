#include "types.h"

/* Read the s32 at +0x10. */

typedef struct Obj_FUN_002e35d0 {
    u8 pad000[0x10];
    s32 field;         /* +0x10 */
} Obj_FUN_002e35d0;

s32 EventPosRecGetId_2e35d0(Obj_FUN_002e35d0 *o)
{
    return o->field;
}
