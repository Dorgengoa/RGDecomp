#include "types.h"

/* Write the s32 at +0x30. */

typedef struct Obj_FUN_00323900 {
    u8 pad000[0x30];
    s32 field;         /* +0x30 */
} Obj_FUN_00323900;

void EntrySetExploredOffset_323900(Obj_FUN_00323900 *o, s32 value)
{
    o->field = value;
}
