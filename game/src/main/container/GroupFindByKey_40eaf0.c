/* rgp:protos */
#define RGP_SELF_GroupFindByKey_40eaf0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

void *GroupFindByKey_40eaf0(void *arg0, s16 arg1)
{
    u8 *p;
    s32 i;
    s32 t;

    if (*(s32 *)((u8 *)arg0 + 0xC) == 0) {
        return NULL;
    }
    p = *(u8 **)((u8 *)arg0 + 0x14);
    for (i = 0; i < 2; i++, p += 0x98) {
        t = *(s32 *)(p + 0x94);
        if (t != 0 && GroupEntryMatchesKey_3f41b0(t, arg1) != 0) {
            return p;
        }
    }
    return NULL;
}
