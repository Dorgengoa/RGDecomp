#include "types.h"

/* Read the s16 at +0x1C. */

typedef struct Obj_FUN_003233a0 {
    u8 pad000[0x1C];
    s16 field;         /* +0x1C */
} Obj_FUN_003233a0;

s16 EntryListGetChildCursor_3233a0(Obj_FUN_003233a0 *o)
{
    return o->field;
}
