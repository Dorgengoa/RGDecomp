#include "types.h"

typedef struct S00369280 {
    u64 unk0;
    u64 unk8;
    u8 pad10[0x20];
    u8 buf[0x40];
} S00369280;

extern void Md5Transform_3693c0(void *, void *);
extern void *memcpy(void *, const void *, u32);

void Md5Update_369280(S00369280 *arg0, u8 *arg1, u64 arg2)
{
    u64 idx;
    u64 part;
    if (arg2 != 0) {
        idx = arg0->unk0 & 0x3F;
        part = 0x40 - idx;
        arg0->unk0 = arg0->unk0 + arg2;
        arg0->unk0 = arg0->unk0 & 0xFFFFFFFF;
        if (arg0->unk0 < arg2) {
            arg0->unk8 = arg0->unk8 + 1;
        }
        if (idx != 0 && arg2 >= part) {
            memcpy(&arg0->buf[idx], arg1, part);
            Md5Transform_3693c0(arg0, arg0->buf);
            arg2 -= part;
            idx = 0;
            arg1 += part;
        }
        while (arg2 >= 0x40) {
            Md5Transform_3693c0(arg0, arg1);
            arg2 -= 0x40;
            arg1 += 0x40;
        }
        if (arg2 != 0) {
            memcpy(&arg0->buf[idx], arg1, arg2);
        }
    }
}
