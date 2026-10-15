#include "types.h"

/* Write the s16 at +0x76. */

typedef struct Obj_FUN_003238e0 {
    u8 pad000[0x76];
    s16 field;         /* +0x76 */
} Obj_FUN_003238e0;

void EntrySetGroupId_3238e0(Obj_FUN_003238e0 *o, s16 value)
{
    o->field = value;
}
