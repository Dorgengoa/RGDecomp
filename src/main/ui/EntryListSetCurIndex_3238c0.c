#include "types.h"

/* Write the s16 at +0x1A. */

typedef struct Obj_FUN_003238c0 {
    u8 pad000[0x1A];
    s16 field;         /* +0x1A */
} Obj_FUN_003238c0;

void EntryListSetCurIndex_3238c0(Obj_FUN_003238c0 *o, s16 value)
{
    o->field = value;
}
