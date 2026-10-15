#include "types.h"

/* Write the s16 at +0x4E. */

typedef struct Obj_FUN_001dded0 {
    u8 pad000[0x4E];
    s16 field;         /* +0x4E */
} Obj_FUN_001dded0;

void MapBoxSetBlockId_1dded0(Obj_FUN_001dded0 *o, s16 value)
{
    o->field = value;
}
