#include "types.h"

/* Is bit 0x4 of the u16 at +0x1E set? */

typedef struct Obj_FUN_001d21b0 {
    u8 pad000[0x1E];
    u16 flags;         /* +0x1E */
} Obj_FUN_001d21b0;

u8 SoundSlotIsSkipVolume_1d21b0(Obj_FUN_001d21b0 *o)
{
    u8 set;

    set = (o->flags & 0x4) != 0;
    return set;
}
