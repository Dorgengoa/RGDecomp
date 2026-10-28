/* rgp:protos */
#define RGP_SELF_MovieStreamReadSectors_1d3430 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s8 D_0044B330[];

s32 MovieStreamReadSectors_1d3430(s32 *arg0, s32 arg1, s32 arg2)
{
    s32 sp7C;
    s32 sp78;
    s8 buf[0x28] __attribute__((aligned(16)));
    s32 r;
    s32 obj;
    s32 h;
    s32 n;
    u8 key;
    u8 k;
    s8 c;
    s8 *src;
    s8 *dst;

    r = 0;
    arg2 = (arg2 / 2048) * 2048;
    src = D_0044B330;
    dst = buf;
    key = 0x3E;
    while ((c = *src) != 0) {
        k = key;
        src++;
        *dst++ = (u8)c ^ k;
        key = k * 13 + 1;
    }
    *dst = 0;
    h = ((s32)GetSoundStreamTable_1bf7c0());
    sp78 = *arg0;
    SoundStreamHandleResolve_1bfa50(&sp7C, h, &sp78);
    if (sp7C != 0) {
        obj = ((s32)SoundStreamLockAcquire_1bfb40(&sp7C));
        r = RingBufRead_1c1890(obj + 4, arg1, arg2);
        SoundStreamQueueFill_1bfdf0(obj);
    }
    SoundStreamLockDtor_1bfab0(&sp7C, -1);
    if (r >= 0) {
        MovieSectorsDescramble_1d3560(arg1, arg2 / 2048, buf);
    }
    return r;
}
