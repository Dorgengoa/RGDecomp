extern void (*D_80074760)();
extern void (*D_80074764)();
extern void (*D_8007474C)();
extern void (*D_80074750)();
extern void (*D_8007475C)();
extern void (*D_80074754)();
extern void (*D_80074758)();
void KernelVblankWaitInitHooks_446d00(void)
{
    *(volatile unsigned int *)0x1000f000 = 4;
    while (!(*(volatile unsigned int *)0x1000f000 & 4)) {}
    *(volatile unsigned int *)0x1000f000 = 4;
    D_80074760();
    D_80074764(1,2,1);
    D_8007474C(0xdffd);
    D_80074750();
    D_8007475C(0x7f);
    D_80074754();
    D_80074758();
}
