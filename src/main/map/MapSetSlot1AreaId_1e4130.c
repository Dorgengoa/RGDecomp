#include "types.h"

/* Write the s16 at +0x4. */

typedef struct Obj_FUN_001e4130 {
    u8 pad000[0x4];
    s16 field;         /* +0x4 */
} Obj_FUN_001e4130;

void MapSetSlot1AreaId_1e4130(Obj_FUN_001e4130 *o, s16 value)
{
    o->field = value;
}
