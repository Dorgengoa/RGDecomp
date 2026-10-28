/* rgp:protos */
#define RGP_SELF_KernelGetOsdConfigParam2_446be0 1
#define RGP_SELF_func_00446C88 1
#include "port/game_protos.h"
#line 1
typedef unsigned long u64 __attribute__((mode(DI)));
typedef struct { __extension__ unsigned long long a:6; unsigned long long b:3; unsigned long long c:31; unsigned long long d:1; unsigned long long e:1; unsigned long long f:2; unsigned long long g:4; unsigned long long h:16; } __attribute__((aligned(8))) K;
extern K D_80074700;
extern unsigned char D_800747B0[0x80];
int KernelGetOsdConfigParam2_446be0(unsigned char *dst, unsigned int n, unsigned int off)
{
    unsigned int i, k;
    if (n + off > 0x80) {
        if (off < 0x80) {
            n = 0x80 - off;
        } else {
            off = 0x80;
            n = 0;
        }
    }
    for (i = off, k = 0; i < n + off; i++, k++)
        dst[k] = D_800747B0[i];
    if (D_80074700.b == 0)
        return 0;
    return D_80074700.g;
}
void func_00446C88(unsigned char *src, unsigned int n, unsigned int off)
{
    unsigned int i, k;
    if (n + off > 0x80) {
        if (off < 0x80) {
            n = 0x80 - off;
        } else {
            off = 0x80;
            n = 0;
        }
    }
    for (i = off, k = 0; i < n + off; i++, k++)
        D_800747B0[i] = src[k];
}
