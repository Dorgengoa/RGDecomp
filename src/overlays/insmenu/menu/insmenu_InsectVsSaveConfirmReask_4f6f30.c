#include "types.h"

/* insmenu 0x004F6F30 (120 bytes) -- start the item list's fade when asked to,
 * then raise the "list settled" event once the fade has run out. */

extern const u8 D_004FA180[];
extern u8 D_004842E8;           /* gp - 0xE88, passed by address */
extern s16 D_00484364;          /* gp - 0xE0C */
extern f32 D_0047D3C8;          /* gp - 0x7DA8 */

extern void func_290690(const void *a, s32 id, f32 x, f32 y, f32 z);
extern f32  func_290770(const void *a, s32 id);
extern void func_28EDE0(void *a, s32 id, s32 c);

s32 insmenu_InsectVsSaveConfirmReask_4f6f30(s32 a, s32 start)
{
    if (start) {
        func_290690(D_004FA180, 0x5F, 0.0f, D_0047D3C8, -1.0f);
        D_00484364 = 1;
    }
    if (func_290770(D_004FA180, 0x5F) <= 0.0f) {
        func_28EDE0(&D_004842E8, 0x88CC, 0);
    }
    return 1;
}
