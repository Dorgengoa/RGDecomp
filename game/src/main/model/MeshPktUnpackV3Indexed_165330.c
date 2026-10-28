/* rgp:protos */
#define RGP_SELF_MeshPktUnpackV3Indexed_165330 1
#include "port/game_protos.h"
#line 1
#include "types.h"

s32 MeshPktUnpackV3Indexed_165330(u32 *pkt, u32 addr, s32 num, u8 *src, s32 type, u16 *idx)
{
    u32 *p = pkt;
    s32 bytes;

    switch (type) {
    case 32: {
        f32 *d;
        *p++ = (addr | 0x8000 | (num << 16)) | 0x68000000;
        d = (f32 *)p;
        for (; num > 0; num--) {
            f32 *s = (f32 *)(src + *idx * 12);
            idx++;
            d[0] = s[0];
            d[1] = s[1];
            d[2] = s[2];
            d += 3;
        }
        p += (u32 *)d - p;
        break;
    }
    case 16: {
        u16 *d;
        s32 n;
        s32 words;
        *p++ = (addr | 0x8000 | (num << 16)) | 0x69000000;
        d = (u16 *)p;
        bytes = num * 6;
        words = bytes / 4;
        if (bytes % 4 != 0) {
            words++;
        }
        n = num;
        for (; n > 0; n--) {
            u16 *s = (u16 *)(src + *idx * 6);
            idx++;
            d[0] = s[0];
            d[1] = s[1];
            d[2] = s[2];
            d += 3;
        }
        p += words;
        break;
    }
    case 8: {
        u8 *d;
        s32 n;
        s32 words;
        *p++ = (addr | 0x8000 | (num << 16)) | 0x6A000000;
        d = (u8 *)p;
        bytes = num * 3;
        words = bytes / 4;
        if (bytes % 4 != 0) {
            words++;
        }
        n = num;
        for (; n > 0; n--) {
            u8 *s = src + *idx * 3;
            idx++;
            d[0] = s[0];
            d[1] = s[1];
            d[2] = s[2];
            d += 3;
        }
        p += words;
        break;
    }
    }
    return p - pkt;
}
