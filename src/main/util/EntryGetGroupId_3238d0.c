#include "types.h"

/* Read the s16 at +0x76. */

typedef struct Obj_FUN_003238d0 {
    u8 pad000[0x76];
    s16 field;         /* +0x76 */
} Obj_FUN_003238d0;

s16 EntryGetGroupId_3238d0(Obj_FUN_003238d0 *o)
{
    return o->field;
}
