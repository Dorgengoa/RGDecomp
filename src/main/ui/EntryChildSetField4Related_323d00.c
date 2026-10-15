#include "types.h"

/* Write the s32 at +0x4. */

typedef struct Obj_FUN_00323d00 {
    u8 pad000[0x4];
    s32 field;         /* +0x4 */
} Obj_FUN_00323d00;

void EntryChildSetField4Related_323d00(Obj_FUN_00323d00 *o, s32 value)
{
    o->field = value;
}
