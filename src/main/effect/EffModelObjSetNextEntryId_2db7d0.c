#include "types.h"

/* Write the s16 at +0x9CA. */

typedef struct Obj_FUN_002db7d0 {
    u8 pad000[0x9CA];
    s16 field;         /* +0x9CA */
} Obj_FUN_002db7d0;

void EffModelObjSetNextEntryId_2db7d0(Obj_FUN_002db7d0 *o, s16 value)
{
    o->field = value;
}
