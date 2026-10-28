/* rgp:protos */
#define RGP_SELF_MapFindAreaSlotById_1e4cb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* The compare is `bnel $18, $2` -- param in rs, call result in rt -- so the
   call is written INLINE in the condition; naming the result would flip the
   operands (pass-31 lever). */

void *MapFindAreaSlotById_1e4cb0(void *p0, s32 key)
{
    u8 *p;
    s32 i;

    if (key < 0) {
        return 0;
    }
    p = (u8 *)p0 + 0x1928;
    i = 0;
    while (i < 4) {
        if (key == ((short)MapDataGetId_1e7bd0(p))) {
            return p;
        }
        i++;
        p += 0x1CC;
    }
    return 0;
}
