/* rgp:protos */
#define RGP_SELF_SoundSlotIsMuted_1d21d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Is bit 0x1 of the u16 at +0x1E set? */

typedef struct Obj_FUN_001d21d0 {
    u8 pad000[0x1E];
    u16 flags;         /* +0x1E */
} Obj_FUN_001d21d0;

u8 SoundSlotIsMuted_1d21d0(Obj_FUN_001d21d0 *o)
{
    u8 set;

    set = (o->flags & 0x1) != 0;
    return set;
}
