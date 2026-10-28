/* rgp:protos */
#define RGP_SELF_EventCastIdListContains_24c1f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Linear search of the array at +0x320 for `key`, over the count at +0x324.
   The count is hoisted out of the loop and the base pointer is not -- retail
   reloads 0x320($4) in the back-edge's delay slot every pass. */

typedef struct Obj0024c1f0 {
    u8 pad0[0x320];
    s32 *unk320;
    s32 unk324;
} Obj0024c1f0;

s32 EventCastIdListContains_24c1f0(Obj0024c1f0 *self, s32 key)
{
    s32 i;

    for (i = 0; i < self->unk324; i++) {
        if (self->unk320[i] == key) {
            return 1;
        }
    }
    return 0;
}
