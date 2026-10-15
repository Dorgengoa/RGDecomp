#include "types.h"

extern void MemStackAllocAligned64_14da10(s32 arg0, s32 arg1);
extern s32 D_0049D39C __attribute__((section(".data")));
extern s32 *D_0049D41C __attribute__((section(".data")));
extern s32 D_0049D424 __attribute__((section(".data")));
extern s32 D_0049D428 __attribute__((section(".data")));

s32 InfoCfgKeyEndCmd_1ab210(void)
{
    s32 *p;
    s32 a;
    s32 b;
    s32 x;
    if (D_0049D424 == 0) {
        return 0;
    }
    x = D_0049D39C;
    if (D_0049D41C == NULL) {
        return 0;
    }
    MemStackAllocAligned64_14da10(x, (((u32)(D_0049D428 * 0x30)) >> 4) + 1);
    b = D_0049D428;
    p = D_0049D41C;
    a = D_0049D424;
    p[2] = a;
    p[1] = b;
    return 1;
}
