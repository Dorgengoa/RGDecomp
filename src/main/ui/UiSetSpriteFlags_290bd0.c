#include "types.h"

u8 *UiFindWidget_290460(void);
typedef struct { u8 pad[0x1C]; u16 x1c; u16 x1e; } S;



s32 UiSetSpriteFlags_290bd0(s32 pdA, s32 pdB, s64 arg2, s32 arg3, s32 arg4, s32 arg5) {
    u8 *p;
    u8 *t;
    s32 i;

    t = UiFindWidget_290460();
    if (t == NULL) {
        return 0;
    }
    p = *(u8 **)(t + 0x20);
    if (p == NULL) {
        return 0;
    }
    if (arg5 != 0) {
        for (i = 0; i < arg5; i++) {
            if (arg3 == 1) {
                *(u16 *)(p + 0x1C) = *(u16 *)(p + 0x1C) | (u16)(arg2 & 0xFFFF);
            } else if (arg3 == 0) {
                *(u16 *)(p + 0x1C) = arg2 & 0xFFFF;
            } else if (arg3 == -1) {
                *(u16 *)(p + 0x1C) &= (u16)~(s16)arg2;
            }
            p += 0x20;
        }
    } else {
        if (arg3 == 1) {
            *(u16 *)((arg4 << 5) + (s32)p + 0x1C) |= (u16)arg2;
        } else if (arg3 == 0) {
            *(u16 *)((arg4 << 5) + (s32)p + 0x1C) = arg2;
        } else if (arg3 == -1) {
            *(u16 *)((arg4 << 5) + (s32)p + 0x1C) &= (u16)~(s16)arg2;
        }
    }
    return 1;
}
