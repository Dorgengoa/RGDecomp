/* rgp:protos */
#define RGP_SELF_FileSlotGetSize_180d50 1
#define RGP_SELF_Get180d50 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off

s32 sceLseek_11bd30(s32, s32, s32);
void SignalSema(s32);
void WaitSema(s32);
extern s32 D_0047E028;
extern s32 D_004811C4;
extern u8 D_0049B100[];
extern u8 D_0049B178[];

static inline u8 *Get180d50(s32 id)
{
    u8 *p;

    if (id < 0 || id >= 12) {
        return NULL;
    }
    p = D_0049B100 + id * 0x7C;
    if (*p == 0) {
        return NULL;
    }
    if (D_0049B178[id * 0x7C] != 0) {
        return NULL;
    }
    return p;
}

s32 FileSlotGetSize_180d50(s32 arg0, s32 *arg1, s32 *arg2)
{
    u8 *p;
    s32 r;
    s32 t;

    p = Get180d50(arg0);
    if (p == NULL) {
        return -1;
    }
    if (arg2 != NULL) {
        *arg2 = 0;
    }
    switch (p[1]) {
    case 0:
        if (D_0047E028 >= 0) {
            WaitSema(D_0047E028);
        }
        D_004811C4 += 1;
        r = sceLseek_11bd30(*(s32 *)(p + 4), 0, 2);
        t = *(s32 *)(p + 0x6C);
        sceLseek_11bd30(*(s32 *)(p + 4), t, 0);
        if (D_0047E028 >= 0) {
            SignalSema(D_0047E028);
        }
        D_004811C4 -= 1;
        *arg1 = r;
        break;
    case 2:
        r = *(s32 *)(p + 8);
        *arg1 = r;
        break;
    case 4:
    case 1:
        *arg1 = *(s32 *)(p + 0x18);
        r = *(s32 *)(p + 8);
        if (arg2 != NULL) {
            *arg2 = *(s32 *)(p + 0x14);
        }
        if (*(s32 *)(p + 0x14) == 0) {
            *arg1 = *(s32 *)(p + 8);
        }
        break;
    default:
        r = -1;
        break;
    }
    return r;
}
