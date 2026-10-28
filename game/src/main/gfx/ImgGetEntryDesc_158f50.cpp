#include "types.h"

struct Data {
    char name[32];
    s32 f20;
    s32 f24;
    s32 f28;
    s32 f2C;
    s16 f30;
    s16 f32;
    s32 f34;
    s64 f38;
};

extern "C" {
s32 memcmp(const void *, const void *, s32);
void *memcpy(void *, const void *, s32);
void *memset(void *, s32, s32);
extern char D_00458B18[];
extern char D_00458B20[];
extern char D_00458B28[];
extern char D_00458B30[];
}

extern "C" Data ImgGetEntryDesc_158f50(u8 *src, s32 idx)
{
    Data d __attribute__((aligned(16)));
    s32 n;
    s32 stride;
    s32 i;
    s32 type;

    memset(&d, 0, 0x40);
    if (src == 0) {
        return d;
    }
    if (src == 0) {
        type = 0;
    } else if (memcmp(src, D_00458B20, 2) != 0) {
        type = 0;
    } else if (memcmp(src, D_00458B28, 3) == 0) {
        type = 1;
    } else if (memcmp(src, D_00458B30, 3) == 0) {
        type = 2;
    } else if (memcmp(src, D_00458B18, 3) == 0) {
        type = 3;
    } else {
        type = 0;
    }
    if (type == 0) {
        return d;
    }
    n = 0;
    stride = 0;
    if (type == 1 || type == 2) {
        n = *(s32 *)(src + 4);
        stride = 0x30;
        src += 0x10;
    }
    if (type == 3) {
        Data *recs = (Data *)(src + 0x10);
        s32 n3 = *(s32 *)(src + 8);
        if (idx < 0 || idx >= n3) {
            return d;
        }
        return recs[idx];
    }
    for (i = 0; i < n; i++) {
        if (idx == i) {
            switch (type) {
            case 2:
                d.f28 = 1;
            case 1:
                memcpy(&d, src, 0x20);
                d.f24 = *(s32 *)(src + 0x20);
                break;
            case 3:
                d = *(Data *)src;
                break;
            }
        }
        src += stride;
    }
    return d;
}
