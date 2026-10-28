/* rgp:protos */
#define RGP_SELF_AtkPrmHitsOpposingMaybe_3f8ca0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Is bit 0x10000000 of the s32 at +0x10 set? */

typedef struct Obj_FUN_003f8ca0 {
    u8 pad000[0x10];
    s32 flags;         /* +0x10 */
} Obj_FUN_003f8ca0;

u8 AtkPrmHitsOpposingMaybe_3f8ca0(Obj_FUN_003f8ca0 *o)
{
    u8 set;

    set = (o->flags & 0x10000000) != 0;
    return set;
}
