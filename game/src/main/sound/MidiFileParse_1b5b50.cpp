#include "types.h"
#pragma divbyzerocheck on

struct Event {
    s16 delta;
    u8 status;
    u8 pad;
    s8 data[2];
};

struct Seq {
    u8 pad0[4];
    s16 tempo;
    s16 count;
    Event *events;
};

extern "C" {
s32 memcmp(const void *, const void *, u32);
void *memset(void *, s32, u32);
extern u8 D_0045AB70[];
extern u8 D_0045AB78[];
}

extern "C" s32 MidiFileParse_1b5b50(Seq *seq, u8 *data, s32 unused, Event *ev, u32 size) {
    s16 format;
    s16 ntracks;
    s16 division;
    s32 hdrlen;
    s32 trklen;
    u8 *dst5;
    u8 *dst4;
    u8 *dst3;
    u8 *dst2;
    u8 *dst1;
    u8 *src5;
    u8 *src4;
    u8 *src3;
    u8 *src2;
    u8 *src1;
    s32 i1;
    s32 i2;
    s32 i3;
    s32 i4;
    s32 i5;
    s32 i;
    u8 *trk;
    u8 *p;
    u32 max;
    s32 status;
    bool done;
    s32 acc;
    s32 d;
    u32 c;
    s32 b;
    s32 n;

    if (memcmp(data, D_0045AB70, 4) != 0) {
        return 0;
    }
    dst1 = (u8 *)&hdrlen + 3;
    src1 = data + 4;
    i1 = 0;
    do {
        i1++;
        *dst1 = *src1;
        src1++;
        dst1--;
    } while (i1 < 4);
    dst2 = (u8 *)&format + 1;
    src2 = data + 8;
    i2 = 0;
    trk = (u8 *)(hdrlen + (s32)data) + 8;
    do {
        i2++;
        *dst2 = *src2;
        src2++;
        dst2--;
    } while (i2 < 2);
    if (format != 0) {
        return 0;
    }
    dst3 = (u8 *)&ntracks + 1;
    src3 = data + 0xA;
    i3 = 0;
    do {
        i3++;
        *dst3 = *src3;
        src3++;
        dst3--;
    } while (i3 < 2);
    src4 = data + 0xC;
    dst4 = (u8 *)&division + 1;
    i4 = 0;
    do {
        i4++;
        *dst4 = *src4;
        src4++;
        dst4--;
    } while (i4 < 2);
    if (memcmp(trk, D_0045AB78, 4) != 0) {
        return 0;
    }
    dst5 = (u8 *)&trklen + 3;
    src5 = trk + 4;
    i5 = 0;
    do {
        i5++;
        *dst5 = *src5;
        src5++;
        dst5--;
    } while (i5 < 4);
    p = trk += 8;
    seq->events = ev;
    if (ev == 0) {
        return 0;
    }
    seq->count = 0;
    max = size / 6;
    status = -1;
    done = 0;
    while (1) {
        if (max == seq->count) {
            done = 1;
            break;
        }
        memset(ev, 0, 6);
        acc = 0;
        while (1) {
            c = *p++;
            d = acc + (c & 0x7F);
            if (!(c & 0x80)) {
                break;
            }
            acc = d << 7;
        }
        b = *p;
        p++;
        if (!(b & 0x80)) {
            b = status;
            p--;
        }
        if (b == 0xFF) {
            if (*(s8 *)p == 0x2F) {
                break;
            }
            n = p[1];
            p += 2;
            p += n;
        } else {
            n = 0;
            switch (b & 0xF0) {
            case 0x90:
            case 0x80:
            case 0xB0:
            case 0xE0:
                n = 2;
                break;
            case 0xC0:
            case 0xD0:
                n = 1;
                break;
            }
            if (n >= 0) {
                ev->delta = d;
                ev->status = b;
                for (i = 0; i < n; i++) {
                    ev->data[i] = *(s8 *)p;
                    p++;
                }
                ev++;
                seq->count++;
            }
        }
        status = b;
        if (p - trk > trklen) {
            break;
        }
    }
    if (done) {
        seq->count = 0;
        seq->events = 0;
        return 0;
    }
    ev->status = 0;
    seq->count = ev + 1 - seq->events;
    seq->tempo = division * 225 / 60;
    return seq->count * 6;
}
