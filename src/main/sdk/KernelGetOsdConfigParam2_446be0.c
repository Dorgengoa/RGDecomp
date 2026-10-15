typedef unsigned long u64 __attribute__((mode(DI)));
typedef struct { u64 a:6; unsigned int b:3; u64 c:31; u64 d:1; u64 e:1; u64 f:2; unsigned int g:4; u64 h:16; } K;
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
