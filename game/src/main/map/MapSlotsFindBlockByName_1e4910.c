/* rgp:protos */
#define RGP_SELF_MapSlotsFindBlockByName_1e4910 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Slot search over the four 0x1CC-stride sub-objects at +0x1928.
   Guard read off the listing: retail's bnel $19, $0 at the entry means the
   source rejects a zero key.  The orphaned `addiu $17,$4,0x1928` after the
   `b` is mwcc's branch-likely duplication, not a second statement. */

s32 MapSlotsFindBlockByName_1e4910(void *p0, s32 key, void **out)
{
    u8 *p;
    s32 i;
    s32 r;

    if (out != 0) {
        *out = 0;
    }
    if (key == 0) {
        return 0;
    }
    p = (u8 *)p0 + 0x1928;
    i = 0;
    while (i < 4) {
        r = MapAreaFindBlockByName_1dc700(p, key);
        if (r != 0) {
            if (out != 0) {
                *out = p;
            }
            return r;
        }
        i++;
        p += 0x1CC;
    }
    return 0;
}
