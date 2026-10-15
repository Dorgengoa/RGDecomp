#include "types.h"
/* insmenu 0x004EFAE0 -- two calls; the first passes the SAME 1.0f four
 * times.  mwcc materialises the constant once into $f12 and copies
 * it out with three `mov.s`, which is exactly retail's shape -- do
 * not read the mov.s run as four separate values. */
extern const u8 D_004FA180[];
extern void func_2905B0(const void *a, s32 b, f32 x, f32 y, f32 z, f32 w);
extern void func_2907D0(const void *a, s32 b, u32 rgba, s32 d);
void insmenu_InsectVsRegSavePanelBright_4efae0(void)
{
    func_2905B0(D_004FA180, 0x19, 1.0f, 1.0f, 1.0f, 1.0f);
    func_2907D0(D_004FA180, 0x27, 0xFF303030, 1);
}
