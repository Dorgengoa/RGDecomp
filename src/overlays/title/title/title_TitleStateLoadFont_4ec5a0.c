#include "types.h"

/* title.bin overlay, 0x004EC5A0 -- teardown: two fire-and-forget calls, then a
 * guarded four-call block on an object that may not exist, then two more.
 *
 * The guard is a PLAIN `beqz` with an empty delay slot jumping over the block,
 * so the block is the positively-guarded arm and there is no early return.
 */

extern void *D_00484158;
extern const u8 D_004B2570;

extern void func_1F59D0(void);
extern void *func_15DE40(void);
extern void func_158AC0(void *a, s32 b);
extern void *func_1C6DC0(void);
extern void func_3134E0(void *a);
extern void *func_2025E0(void);
extern void *func_14DB10(void *a, s32 b, s32 c, s32 d);
extern void func_313470(s32 a, void *b, s32 c);
extern void func_14DAD0(void *a);
extern void func_14DCB0(void *a, void *b);
extern void func_1849E0(void *a);
extern void func_28EDE0(void *a, s32 b, s32 c);

s32 title_TitleStateLoadFont_4ec5a0(void)
{
    void *p;
    void *q;

    func_1F59D0();
    func_158AC0(func_15DE40(), 0x32D);
    func_3134E0(func_1C6DC0());
    p = func_2025E0();
    if (p != 0) {
        q = func_14DB10(p, 2, 0, 0x40);
        func_313470(1, q, 0x338);
        func_14DAD0(p);
        func_14DCB0(p, q);
    }
    func_1849E0((void *)&D_004B2570);
    func_28EDE0(D_00484158, 3, 1);
    return 1;
}
