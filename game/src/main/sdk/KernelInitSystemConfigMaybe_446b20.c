/* rgp:protos */
#define RGP_SELF_KernelInitSystemConfigMaybe_446b20 1
#include "port/game_protos.h"
#line 1
typedef unsigned long u64 __attribute__((mode(DI)));
typedef struct { __extension__ unsigned long long a:6; unsigned long long b:3; unsigned long long c:31; unsigned long long d:1; unsigned long long e:1; unsigned long long f:2; unsigned long long g:4; unsigned long long h:16; } __attribute__((aligned(8))) K;
extern K D_80074700;
void KernelInitSystemConfigMaybe_446b20(void)
{
    unsigned char *src;
    unsigned char *dst;
    int i;
    src = *(unsigned char **)0xBC0003C0;
    if (src != 0) {
        src += 0xBC000000;
        src += 0xF;
        dst = (unsigned char *)&D_80074700;
        for (i = 0; i < 0x26; i++)
            dst[i] = src[i];
    }
    if (D_80074700.b == 0) { D_80074700.d = 0; D_80074700.f = 0; D_80074700.g = 0; }
}
