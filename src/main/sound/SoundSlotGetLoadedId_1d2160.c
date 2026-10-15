#include "types.h"

/* Read the s32 at +0x10. */

typedef struct Obj_FUN_001d2160 {
    u8 pad000[0x10];
    s32 field;         /* +0x10 */
} Obj_FUN_001d2160;

s32 SoundSlotGetLoadedId_1d2160(Obj_FUN_001d2160 *o)
{
    return o->field;
}
