/* rgp:protos */
#define RGP_SELF_IntToDecStr_1d7d10 1
#include "port/game_protos.h"
#line 1
#pragma divbyzerocheck on
#include "types.h"

void IntToDecStr_1d7d10(s32 v, char *out)
{
    char buf[0x80] __attribute__((aligned(16)));
    s32 n;
    s32 i;
    s32 j;
    n = 0;
    for (i = 0; i < 0x80; i++) {
        buf[n] = (v % 10) + 0x30;
        n++;
        v = v / 10;
        if (v == 0) break;
    }
    for (j = 0; j < n; j++) {
        out[j] = buf[n - j - 1];
    }
    out[n] = 0;
}
