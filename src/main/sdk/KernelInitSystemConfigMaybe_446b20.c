typedef unsigned long u64 __attribute__((mode(DI)));
typedef struct { u64 a:6; unsigned int b:3; u64 c:31; u64 d:1; u64 e:1; u64 f:2; unsigned int g:4; u64 h:16; } K;
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
