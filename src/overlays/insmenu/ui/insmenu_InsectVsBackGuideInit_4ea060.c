#include "types.h"

/* insmenu 0x004EA060 (100 bytes, 22 instructions, 4 calls) -- show one widget
 * and give it its label.  `daddu $7, $6, $0` in the first call's delay slot is
 * mwcc sharing the 1 it already materialised for the third argument; both are
 * written out as literals.
 */

extern const u8 D_004FA180[];
extern s32 D_004842FC;      /* gp - 0xE74 */

extern void func_291110(const void *a, s32 b, s32 c, s32 d);
extern void func_2907A0(const void *a, s32 b, f32 t);
extern s32 func_28AA30(s32 a, s32 b);
extern void func_28F510(const void *a, s32 b, s32 c, s32 d);

void insmenu_InsectVsBackGuideInit_4ea060(void)
{
    func_291110(D_004FA180, 0x59, 1, 1);
    func_2907A0(D_004FA180, 0x59, 0.0f);
    func_28F510(D_004FA180, 0x5B, func_28AA30(D_004842FC, 0x5E0), 0);
}
