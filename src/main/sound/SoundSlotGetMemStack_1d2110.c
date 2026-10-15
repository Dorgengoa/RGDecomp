#include "types.h"

/* Address of the sub-object at +0x30. */

typedef struct Obj_FUN_001d2110 {
    u8 pad000[0x30];
    u8 sub[1];         /* +0x30 */
} Obj_FUN_001d2110;

void *SoundSlotGetMemStack_1d2110(Obj_FUN_001d2110 *o)
{
    return o->sub;
}
