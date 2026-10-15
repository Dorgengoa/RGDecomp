#include "types.h"

/* insmenu 0x004F8990 (112 bytes) -- once the fade widget has run out, raise
 * either the "resumed" or the "opened" event.
 *
 * ★ `sb $0, -0xE18($28)` rides the call's delay slot: the flag is cleared in
 * the SOURCE before the call, which is what gives mwcc something to sink. */

extern const u8 D_004FA180[];
extern u8 D_004842E8;           /* gp - 0xE88, passed by address */
extern u8 D_00484358;           /* gp - 0xE18 */

extern f32  func_290770(const void *a, s32 b);
extern void func_28EDE0(void *a, s32 id, s32 c);

s32 insmenu_InsectVsTeamViewClose_4f8990(void)
{
    if (func_290770(D_004FA180, 0x9CA7) <= 0.0f) {
        if (D_00484358 != 0) {
            D_00484358 = 0;
            func_28EDE0(&D_004842E8, 0x88C6, 0);
        } else {
            func_28EDE0(&D_004842E8, 0x88BF, 0);
        }
    }
    return 1;
}
