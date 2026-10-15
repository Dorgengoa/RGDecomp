#include "types.h"

/* title.bin overlay, 0x004EED60 -- one guarded call then three unconditional
 * ones.  The incoming first argument is never used; only the second is, as
 * the guard.
 *
 * `lui $5, 0x4B` + `addiu $5, $5, 0x2570` is the absolute address of a
 * main-image object, so it has to be `const` -- a plain extern comes out
 * gp-relative.
 */

extern void *D_004841E8;
extern void *D_00484174;
extern const u8 D_004B2570;
extern void func_28EA90(void *a, s32 b, s32 c);
extern void func_37BAC0(s32 a);
extern void func_28E170(void *a, void *b, s32 c, s32 d);
extern void func_3774D0(void *a);

s32 title_TitleLoadTick_4eed60(void *o, s32 flag)
{
    if (flag != 0) {
        func_28EA90(D_004841E8, 0x7532, 0);
    }
    func_37BAC0(0);
    func_28E170(D_004841E8, (void *)&D_004B2570, 0, 0);
    func_3774D0(D_00484174);
    return 1;
}
