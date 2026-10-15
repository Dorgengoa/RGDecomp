#include "types.h"

/* insmenu 0x004F2F30 (92 bytes, 23 instructions, 3 calls) -- show one widget,
 * clear its fade and nudge it up by 0x3C.  `daddu $7, $6, $0` is mwcc sharing
 * the 1 it materialised for the third argument.
 */

extern const u8 D_004FA180[];

extern void func_291110(const void *a, s32 b, s32 c, s32 d);
extern void func_2907A0(const void *a, s32 b, f32 t);
extern void func_290F60(const void *a, s32 b, s32 c, s32 d);

void insmenu_InsectVsTitleBannerReset_4f2f30(void)
{
    func_291110(D_004FA180, 0x39, 1, 1);
    func_2907A0(D_004FA180, 0x39, 1.0f);
    func_290F60(D_004FA180, 0x39, 0, -0x3C);
}
