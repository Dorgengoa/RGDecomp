#include "types.h"

/* Read the s32 at +0x4. */

typedef struct Obj_FUN_002310c0 {
    u8 pad000[0x4];
    s32 field;         /* +0x4 */
} Obj_FUN_002310c0;

s32 ActInfoCallGetFlags_2310c0(Obj_FUN_002310c0 *o)
{
    return o->field;
}
