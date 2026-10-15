#include "types.h"
/* insmenu 0x004F2950 -- the insmenu_FUN_004EEF10 pair with a THIRD call: the
 * same colour written to two widget ids. */
extern const u8 D_004FA180[];
extern void func_2905B0(const void *a, s32 b, f32 x, f32 y, f32 z, f32 w);
extern void func_2907D0(const void *a, s32 b, u32 rgba, s32 d);
void insmenu_InsectVsTopPanelBright_4f2950(void)
{
    func_2905B0(D_004FA180, 1, 1.0f, 1.0f, 1.0f, 1.0f);
    func_2907D0(D_004FA180, 0x37, 0xFF303030, 1);
    func_2907D0(D_004FA180, 0x38, 0xFF303030, 1);
}
