#include "types.h"
/* normal 0x004FF5C0 -- reads widget 0x23's origin and, when the Y component is
 * exactly +/-0x32, re-anchors it to 0,0 and posts 0x55FA.  Out-params at
 * sp+0x1C / sp+0x18, so `x` (0x1C) is declared FIRST; only `y` is read.
 * The `beql`/`bne` pair against 0x32 and -0x32 is a two-arm `||`. */

extern const u8 D_005278E0;

extern void *D_00484498;          /* gp - 0xCD8 */
extern void *D_0048449C;          /* gp - 0xCD4 */

extern void func_2910A0(void *w, u16 id, s32 *ox, s32 *oy);
extern void func_290F60(void *w, u16 id, s32 a, s32 b);
extern void func_28EDE0(void *w, s32 id, s32 a);
extern void func_28D820(const u8 *p, s32 a);

s32 normal_BtlChgMenuItemListScrollState_4ff5c0(void *a, s32 b)
{
    s32 x;
    s32 y;

    func_2910A0(D_0048449C, 0x23, &x, &y);
    if ((y == 0x32) || (y == -0x32)) {
        func_290F60(D_0048449C, 0x23, 0, 0);
        func_28EDE0(D_00484498, 0x55FA, 0);
    }
    func_28D820(&D_005278E0, 0x28);
    return 1;
}
