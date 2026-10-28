/* rgp:protos */
#define RGP_SELF_PartyCollectLiveMemberIds_2cd6e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

s32 PartyCollectLiveMemberIds_2cd6e0(s32 *out)
{
    void *obj;
    void *ent;
    s32 ok;
    s32 idx;
    s32 last;
    s32 n;

    obj = GetGameData_1fede0();
    n = 0;
    last = -1;
    for (;;) {
        idx = -1;
        ent = PartyFindMember_3c2130(*(s32 *)((u8 *)obj + 0x18), -1, 1, 0, last, &idx, 0);
        ok = !ent;
        if (ok) {
            break;
        }
        if (idx < 0) {
            break;
        }
        last = idx + 1;
        out[n] = *(s32 *)((u8 *)ent + 0xC);
        n++;
    }
    return n;
}
