/* rgp:protos */
#define RGP_SELF_SoundStreamSlotRingWrite_1bde90 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma divbyzerocheck on

typedef struct T1bde90 {
    u8 pad0[0xF4];
    s32 size;
    u8 *buf[2];
    s32 wr;
    s32 rd;
    u8 full;
} T1bde90;

void *memcpy(void *, const void *, s32);

s32 SoundStreamSlotRingWrite_1bde90(T1bde90 *o, s32 ch, u8 *src, s32 len, s32 commit)
{
    s32 w;
    s32 size;
    u8 *b;
    s32 space;

    if (ch < 0 || ch >= 2) {
        return 0;
    }
    if (len <= 0) {
        return 0;
    }
    w = o->wr;
    size = *(volatile s32 *)((u8 *)o + 0xF4);
    b = *(u8 *volatile *)((u8 *)((ch << 2) + (u32)o) + 0xF8);
    if (w == o->rd && o->full == 0) {
        return 0;
    }
    if (w < o->rd) {
        memcpy(b + w, src, len);
    } else {
        space = size - w;
        if (space >= len) {
            memcpy(b + w, src, len);
        } else {
            memcpy(b + w, src, space);
            memcpy(b, src + space, len - space);
        }
    }
    if (commit != 0) {
        o->wr = (o->wr + len) % size;
        o->full = 0;
    }
    return len;
}
