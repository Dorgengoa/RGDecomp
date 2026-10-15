#include "types.h"
/* insmenu 0x004F2F90 -- teardown.  0x4B2570 / 0x4B27E0 are unsymbolised
 * main-image data addresses taken by `&extern` so they get %hi/%lo.
 * `h` is a named local because TWO calls share it: retail computes it once
 * and issues `daddu $4, $16, $0` before each. */
extern s32 D_00484104;
extern s16 D_00484300;
extern const u8 D_004B2570;
extern const u8 D_004B27E0;
extern void func_4366D0(s32 a);
extern void insmenu_InsectVsMenuResFree_4f3340(void);
extern void func_183960(const void *a);
extern void func_183940(const void *a);
extern void *func_206A40(void);
extern void func_42B650(void *a, s32 b);

void insmenu_InsectVsMenuRelease_4f2f90(void)
{
    void *h;

    if (D_00484104 != 0) {
        func_4366D0(D_00484104);
    }
    insmenu_InsectVsMenuResFree_4f3340();
    func_183960(&D_004B2570);
    func_183940(&D_004B2570);
    func_183960(&D_004B27E0);
    func_183940(&D_004B27E0);
    h = func_206A40();
    func_42B650(h, 1);
    func_42B650(h, 3);
    D_00484104 = 0;
    D_00484300 = 0;
}
