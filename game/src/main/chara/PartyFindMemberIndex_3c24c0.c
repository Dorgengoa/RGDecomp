/* rgp:protos */
#define RGP_SELF_PartyFindMemberIndex_3c24c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Obj0 { u8 pad000[0x18C]; s16 m18C; };

s32 PartyFindMemberIndex_3c24c0(struct Obj0 *p0, s32 p1)
{
    s32 l0;
    s32 n;
    s16 e;

    n = p0->m18C;
    if (p1 < 0) {
        return -1;
    }
    l0 = 0;
    while (l0 < n) {
        e = *(s16 *)((u8 *)p0 + (l0 << 1) + 0x190);
        if (e == p1) {
            return l0;
        }
        l0 = (l0 + 1);
    }
    return -1;
}
