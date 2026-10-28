/* rgp:protos */
#define RGP_SELF_StreamChanIsMuted_1d71d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Is bit 0x40000 of the s32 at +0x94 set? */

typedef struct Obj_FUN_001d71d0 {
    u8 pad000[0x94];
    s32 flags;         /* +0x94 */
} Obj_FUN_001d71d0;

u8 StreamChanIsMuted_1d71d0(Obj_FUN_001d71d0 *o)
{
    u8 set;

    set = (o->flags & 0x40000) != 0;
    return set;
}
