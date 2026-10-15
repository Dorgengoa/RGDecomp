#include "types.h"

extern void *D_0047FFE0;
extern void *D_0047FFE8;
extern s32 ZoneDataSelectNameMaybe_3eff20(void *, void *);
extern s32 Sprintf_1343b8(void *, void *, s32, s32);
extern void *strcat(void *, void *);

s32 NpcTalkTextCfgPath_41df70(void *a, void *b, void *c, void *d)
{
    s32 r;
    if (b == 0) goto zero;
    if (c != 0) goto ok;
zero:
    return 0;
ok:
    r = ZoneDataSelectNameMaybe_3eff20(d, c);
    if (r == 0) return 0;
    Sprintf_1343b8(b, D_0047FFE8, r, r);
    strcat(b, D_0047FFE0);
    return 1;
}
