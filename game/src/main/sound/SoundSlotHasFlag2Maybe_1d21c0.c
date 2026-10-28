/* rgp:protos */
#define RGP_SELF_SoundSlotHasFlag2Maybe_1d21c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Is bit 0x2 of the u16 at +0x1E set? */

typedef struct Obj_FUN_001d21c0 {
    u8 pad000[0x1E];
    u16 flags;         /* +0x1E */
} Obj_FUN_001d21c0;

u8 SoundSlotHasFlag2Maybe_1d21c0(Obj_FUN_001d21c0 *o)
{
    u8 set;

    set = (o->flags & 0x2) != 0;
    return set;
}
