/* rgp:protos */
#define RGP_SELF_PtalkTextCfgPath_41fa50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct C_0041fa50 {
    u8 pad0[0xC];
    s32 fC;
} C_0041fa50;

extern void *D_0047FFE0;
extern void *D_0047FFEC;
extern s32 Sprintf_1343b8(void *, void *, s32, s32);
extern void *strcat(void *, void *);

s32 PtalkTextCfgPath_41fa50(void *a, void *b, C_0041fa50 *c)
{
    s32 x;
    if (b == 0) goto zero;
    if (c != 0) goto g1;
zero:
    return 0;
g1:
    x = c->fC;
    if (x == 0) return 0;
    Sprintf_1343b8(b, D_0047FFEC, x, x);
    strcat(b, D_0047FFE0);
    return 1;
}
