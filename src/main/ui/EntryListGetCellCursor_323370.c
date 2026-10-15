#include "types.h"

/* Read the s16 at +0x1E. */

typedef struct Obj_FUN_00323370 {
    u8 pad000[0x1E];
    s16 field;         /* +0x1E */
} Obj_FUN_00323370;

s16 EntryListGetCellCursor_323370(Obj_FUN_00323370 *o)
{
    return o->field;
}
