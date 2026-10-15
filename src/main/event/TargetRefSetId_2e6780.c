#include "types.h"

/* Write the s16 at +0x2. */

typedef struct Obj_FUN_002e6780 {
    u8 pad000[0x2];
    s16 field;         /* +0x2 */
} Obj_FUN_002e6780;

void TargetRefSetId_2e6780(Obj_FUN_002e6780 *o, s16 value)
{
    o->field = value;
}
