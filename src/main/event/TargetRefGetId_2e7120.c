#include "types.h"

/* Read the s16 at +0x2. */

typedef struct Obj_FUN_002e7120 {
    u8 pad000[0x2];
    s16 field;         /* +0x2 */
} Obj_FUN_002e7120;

s16 TargetRefGetId_2e7120(Obj_FUN_002e7120 *o)
{
    return o->field;
}
