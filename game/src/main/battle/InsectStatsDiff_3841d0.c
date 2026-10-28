/* rgp:protos */
#define RGP_SELF_InsectStatsDiff_3841d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

void InsectStatsDiff_3841d0(void *arg0, void *arg1, void *arg2)
{
    s32 sp[12] __attribute__((aligned(16)));
    s32 i;
    s32 fixed_diff;
    s32 *dst;
    s32 *src;
    s32 n;

    fixed_diff = *(s32 *)((u8 *)arg1 + 4) - *(s32 *)((u8 *)arg2 + 4);
    i = 0;
    do {
        sp[i] = fixed_diff;
        sp[2 + i] = *(s32 *)((u8 *)arg1 + i * 4 + 8) - *(s32 *)((u8 *)arg2 + i * 4 + 8);
        sp[4 + i] = *(s32 *)((u8 *)arg1 + i * 4 + 0x10) - *(s32 *)((u8 *)arg2 + i * 4 + 0x10);
        i += 1;
    } while (i < 2);

    i = 0;
    do {
        sp[6 + i] = *(s32 *)((u8 *)arg1 + i * 4 + 0x18) - *(s32 *)((u8 *)arg2 + i * 4 + 0x18);
        i += 1;
    } while (i < 6);

    src = sp;
    dst = (s32 *)arg0;
    n = 6;
    do {
        n -= 1;
        dst[0] = src[0];
        dst[1] = src[1];
        src += 2;
        dst += 2;
    } while (n > 0);
}
