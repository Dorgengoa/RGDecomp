#include "types.h"

s32 MeshPktUnpackV2Indexed_165150(u32 *pkt, u32 addr, s32 num, u8 *src, s32 type, u16 *idx)
{
    u32 *p = pkt;
    s32 bytes;

    switch (type) {
    case 32: {
        f32 *d;
        *p++ = (addr | 0xC000 | (num << 16)) | 0x64000000;
        d = (f32 *)p;
        for (; num > 0; num--) {
            f32 *s = (f32 *)(src + *idx * 8);
            idx++;
            d[0] = s[0];
            d[1] = s[1];
            d += 2;
        }
        p += (u32 *)d - p;
        break;
    }
    case 16: {
        u32 *d;
        s32 n;
        s32 words;
        *p++ = (addr | 0xC000 | (num << 16)) | 0x65000000;
        d = p;
        bytes = num * 4;
        words = bytes / 4;
        if (bytes % 4 != 0) {
            words++;
        }
        n = num;
        for (; n > 0; n--) {
            *d = *(u32 *)(src + *idx * 4);
            idx++;
            d++;
        }
        p += words;
        break;
    }
    case 8: {
        u16 *d;
        s32 n;
        s32 words;
        *p++ = (addr | 0xC000 | (num << 16)) | 0x66000000;
        d = (u16 *)p;
        bytes = num * 2;
        words = bytes / 4;
        if (bytes % 4 != 0) {
            words++;
        }
        n = num;
        for (; n > 0; n--) {
            *d = *(u16 *)(src + *idx * 2);
            idx++;
            d++;
        }
        p += words;
        break;
    }
    }
    return p - pkt;
}
