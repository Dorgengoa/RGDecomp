#include "types.h"

/* insmenu 0x004F8630 (224 bytes) -- start the sub-panel's fade when asked to,
 * then raise the event the current mode calls for once it has run out.
 *
 * ★ The mode == 0 arm is written as the `else` of a NEGATIVE outer guard, not
 * as the head of an if/else-if chain: retail tests 0 first and lays its block
 * LAST, which is what an inverted guard does and an ordinary chain does not.
 * Spelled `if (mode == 0) ... else if (mode == 2) ...` the arms come out in the
 * wrong order and the unit reads 24 bad at the right length. */

extern const u8 D_004FA180[];
extern const u8 D_004FA1A0[];
extern u8 D_004842E8;           /* gp - 0xE88, passed by address */
extern s16 D_0048436C;          /* gp - 0xE04 */
extern f32 D_0047D3C8;          /* gp - 0x7DA8 */

extern void func_290690(const void *a, s32 id, f32 x, f32 y, f32 z);
extern void func_2907A0(const void *a, s32 id, f32 v);
extern f32  func_290770(const void *a, s32 id);
extern void func_28EB10(const void *a, s32 id);
extern void func_28EDE0(void *a, s32 id, s32 c);

s32 insmenu_InsectVsSourceChoiceClose_4f8630(s32 a, s32 start)
{
    s16 mode;

    if (start) {
        func_290690(D_004FA180, 0x5C, 0.0f, D_0047D3C8, -1.0f);
        func_2907A0(D_004FA180, 0x5E, 0.0f);
    }
    if (func_290770(D_004FA180, 0x5C) <= 0.0f) {
        mode = D_0048436C;
        if (mode != 0) {
            if (mode == 2) {
                func_28EB10(D_004FA1A0, 0x88B9);
                func_28EDE0(&D_004842E8, 0x88BE, 0);
            } else if (mode == 1) {
                func_28EDE0(&D_004842E8, 0x88C9, 0);
            }
        } else {
            func_28EDE0(&D_004842E8, 0x88BF, 0);
        }
    }
    return 1;
}
