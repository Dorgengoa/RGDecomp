/* rgp:protos */
#define RGP_SELF_EventCastDataGroupIdAlloc_2503a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 D_00481F30;

s32 EventCastDataGroupIdAlloc_2503a0(void *arg0) {
    s32 n;
    s32 v;
    s32 base;
    volatile s32 spC;

    n = *(s32 *)((u8 *)arg0 + 0x5CF4);
    base = *(s32 *)((u8 *)arg0 + 0x5CF0);
    v = D_00481F30;
    spC = n;
    if (v < 0 || v >= n) {
        return -1;
    }
    D_00481F30 = v + 1;
    return base + v;
}
