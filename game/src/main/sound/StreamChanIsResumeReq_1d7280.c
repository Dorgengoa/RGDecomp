/* rgp:protos */
#define RGP_SELF_StreamChanIsResumeReq_1d7280 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Is bit 0x2 of the s32 at +0x94 set? */

typedef struct Obj_FUN_001d7280 {
    u8 pad000[0x94];
    s32 flags;         /* +0x94 */
} Obj_FUN_001d7280;

u8 StreamChanIsResumeReq_1d7280(Obj_FUN_001d7280 *o)
{
    u8 set;

    set = (o->flags & 0x2) != 0;
    return set;
}
