#include "types.h"

extern void *GetGameData_1fede0(void);
extern void *PartyFindMember_3c2130(s32, s32, s32, s32, s32, s32 *, s32);

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
