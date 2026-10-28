/* rgp:protos */
#define RGP_SELF_MeshPktUnpackBoneRefsMaybe_164ec0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s32 x;
    s32 y;
    s32 n;
} E164ec0;

s32 MeshPktUnpackBoneRefsMaybe_164ec0(s32 pkt, s32 addr, s32 cnt, E164ec0 *tbl, u16 *idx, s32 *out) {
    struct {s32 n;s32 end;} packed;

    s32 max;
    u16 *p;

    s32 w;
    s32 q;

    s32 v;
    E164ec0 *e;

    max = 0;
    p = idx;
    for (packed.n = cnt; packed.n > 0; packed.n--) {
        v = tbl[*idx].n;
        idx++;
        if (max < v) {
            max = v;
        }
    }
    if (max == 1) {
        s8 *d0;
        u8 *d1;
        w = cnt / 4;
        if (cnt % 4 != 0) {
            w++;
        }
        idx = p;
        w = w * 4;
        *(u32 *)(pkt + 0) = 0x01000102;
        *(u32 *)(pkt + 4) = addr | 0x8000 | (cnt << 16) | 0x62000000;
        q = w + pkt + 8;
        *(u32 *)q = (addr + 1) | 0xC000 | (cnt << 16) | 0x62000000;
        d0 = (s8 *)(pkt + 8);
        d1 = (u8 *)(q + 4);
        for (; cnt > 0; cnt--) {
            e = &tbl[*idx];
            idx++;
            *d0++ = *(s8 *)&e->x;
            *d1++ = *(u8 *)&e->y;
        }
        packed.end = w + q + 4;
    } else if (max < 3) {
        s16 *d0;
        s16 *d1;
        w = cnt / 2;
        if (cnt % 2 != 0) {
            w++;
        }
        w = w * 4;
        *(u32 *)(pkt + 0) = 0x01000102;
        *(u32 *)(pkt + 4) = addr | 0x8000 | (cnt << 16) | 0x66000000;
        q = w + pkt + 8;
        *(u32 *)q = (addr + 1) | 0xC000 | (cnt << 16) | 0x66000000;
        d0 = (s16 *)(pkt + 8);
        d1 = (s16 *)(q + 4);
        for (; cnt > 0; cnt--) {
            e = &tbl[*p];
            p++;
            *d0++ = *(s16 *)&e->x;
            *d1++ = *(s16 *)&e->y;
        }
        packed.end = w + q + 4;
    } else {
        s32 *d0;
        s32 *d1;
        *(u32 *)(pkt + 0) = 0x01000102;
        *(u32 *)(pkt + 4) = addr | 0x8000 | (cnt << 16) | 0x6E000000;
        d0 = (s32 *)(pkt + 8);
        q = (s32)(d0 + cnt);
        *(u32 *)q = (addr + 1) | 0xC000 | (cnt << 16) | 0x6E000000;
        d1 = (s32 *)(q + 4);
        for (; cnt > 0; cnt--) {
            e = &tbl[*p];
            p++;
            *d0++ = e->x;
            *d1++ = e->y;
            if (max < e->n) {
                max = e->n;
            }
        }
        packed.end = (s32)d1;
    }
    *out = max;
    return (packed.end - pkt) / 4;
}
