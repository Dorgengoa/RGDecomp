#include "types.h"

/* insmenu 0x004ED850 (80 bytes, 20 instructions, 5 calls) -- open the record
 * at +0x350, blank its 0x8F-byte text buffer, close it and set the dirty flag.
 * Near-twin of insmenu_InsectVsRegPwEnter_4ed0a0 (different opener, different offset).
 */

typedef struct Handle Handle;
struct Handle {
    u8 pad00[0x24];
    void *field024;
};

extern u8 D_00484304;       /* gp - 0xE6C */

extern Handle *func_1FEDE0(void);
extern void *func_430B50(void *a);
extern void func_131B60(void *a, s32 b, s32 c);
extern void func_430BF0(void *a, s32 b);

s32 insmenu_InsectVsPwBattleEnter_4ed850(void)
{
    Handle *h;
    void *r;

    h = func_1FEDE0();
    r = func_430B50(h->field024);
    func_131B60((u8 *)r + 0x350, 0, 0x8F);
    func_430BF0(h->field024, 0);
    D_00484304 = 1;
    return 1;
}
