#include "types.h"

/* insmenu 0x004EE9E0 (216 bytes, 54 instructions, 10 calls) -- lay out the
 * confirm prompt: place and show the frame, then fill the two-line label from
 * the string bank.  `daddu $7, $6, $0` in the second call's delay slot is mwcc
 * sharing the 1 it already materialised.
 */

extern const u8 D_004FA180[];
extern s32 D_00481BBC;      /* gp - 0x35B4 */

extern void func_290F60(const void *a, s32 b, s32 c, s32 d);
extern void func_291110(const void *a, s32 b, s32 c, s32 d);
extern void func_2907A0(const void *a, s32 b, f32 t);
extern void func_28F930(const void *a, s32 b, s32 c, s32 d);
extern s32 func_28AA30(s32 a, s32 b);
extern void func_28F510(const void *a, s32 b, s32 c, s32 d);
extern void insmenu_InsectVsBackGuideHide_4ea000(void);

void insmenu_InsectVsConfirmDialogLayout_4ee9e0(void)
{
    func_290F60(D_004FA180, 6, 0x60, 0xF0);
    func_291110(D_004FA180, 6, 1, 1);
    func_2907A0(D_004FA180, 6, 0.0f);
    func_28F930(D_004FA180, 8, 0x7A, 0);
    func_28F930(D_004FA180, 8, 0x46, 1);
    func_28F510(D_004FA180, 8, func_28AA30(D_00481BBC, 0x52), 1);
    func_28F510(D_004FA180, 8, func_28AA30(D_00481BBC, 0x53), 2);
    insmenu_InsectVsBackGuideHide_4ea000();
}
