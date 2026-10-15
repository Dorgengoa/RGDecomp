#include "types.h"

/* Is bit 0x20 of the s32 at +0x94 set? */

typedef struct Obj_FUN_001d7240 {
    u8 pad000[0x94];
    s32 flags;         /* +0x94 */
} Obj_FUN_001d7240;

u8 StreamChanIsSaveResumeReq_1d7240(Obj_FUN_001d7240 *o)
{
    u8 set;

    set = (o->flags & 0x20) != 0;
    return set;
}
