#pragma divbyzerocheck on
#include "types.h"

typedef struct {
    s32 state;
    u8 pad4[0x30 - 0x4];
    s32 base;
    s32 pos;
    s32 rem;
    s32 size;
    u8 pad40[0x44 - 0x40];
    s32 unk44;
    s32 unk48;
    s32 unk4C;
    u8 pad50[0x54 - 0x50];
    s32 unk54;
} Strm;

extern u32 SoundSendCmd_1b6cc0(s32, s32, s32, s32, s32, s32, s32, s32);
extern s32 AudioDecSendToIop2Area_1d2ca0(s32, s32, s32, s32, s32, s32, s32, s32);
extern void AudioDecIopGetArea_1d2df0(s32 *, s32 *, s32 *, s32 *, Strm *, s32);

s32 AudioDecSendToIop_1d2e90(Strm *arg0)
{
    s32 dst;
    s32 x;
    s32 len;
    s32 y;
    s32 n;
    s32 src;
    s32 bytes;
    s32 a;
    s32 b;

    n = 0;
    switch (arg0->state) {
    case 0:
        return 0;
    case 1:
        dst = arg0->unk44 + arg0->unk54 % arg0->unk48;
        len = arg0->unk48 - arg0->unk54;
        y = 0;
        x = 0;
        break;
    case 2:
        AudioDecIopGetArea_1d2df0(&dst, &len, &x, &y, arg0, (SoundSendCmd_1b6cc0(0x26, 6, 0x8100, 0, 0, 0, 0, 0) & 0xFFFFFF) - arg0->unk44);
        break;
    case 3:
        return 0;
    }
    src = arg0->base + (arg0->size + (arg0->pos - arg0->rem)) % arg0->size;
    bytes = (arg0->rem / 0x400) << 10;
    a = (arg0->base + arg0->size) - src;
    a = (bytes < a) ? bytes : a;
    b = bytes - a;
    if (len + y >= 0x400 && a + b >= 0x400) {
        n = AudioDecSendToIop2Area_1d2ca0(dst, len, x, y, src, a, arg0->base, b);
    }
    arg0->rem -= n;
    arg0->unk54 += n;
    arg0->unk4C = (arg0->unk4C + n) % arg0->unk48;
    return n;
}
