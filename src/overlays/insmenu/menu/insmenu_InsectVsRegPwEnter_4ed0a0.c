#include "types.h"

/* insmenu 0x004ED0A0 (80 bytes, 20 instructions, 5 calls) -- the twin of
 * insmenu_InsectVsPwBattleEnter_4ed850 with a different opener and a 0xEC offset.
 */

typedef struct Handle Handle;
struct Handle {
    u8 pad00[0x24];
    void *field024;
};

extern u8 D_00484304;       /* gp - 0xE6C */

extern Handle *func_1FEDE0(void);
extern void *func_430B10(void *a);
extern void func_131B60(void *a, s32 b, s32 c);
extern void func_430BF0(void *a, s32 b);

s32 insmenu_InsectVsRegPwEnter_4ed0a0(void)
{
    Handle *h;
    void *r;

    h = func_1FEDE0();
    r = func_430B10(h->field024);
    func_131B60((u8 *)r + 0xEC, 0, 0x8F);
    func_430BF0(h->field024, 0);
    D_00484304 = 1;
    return 1;
}
