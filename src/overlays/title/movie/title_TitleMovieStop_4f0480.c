#include "types.h"

/* title.bin overlay, 0x004F0480 -- four calls, three of them with a
 * gp-relative argument loaded in the call's own delay slot, then a store and
 * a constant return. */

extern void *D_00484290;
extern void *D_0048429C;
extern s32 D_00480430;
extern void func_1D56C0(void *a);
extern void func_1D5870(void *a);
extern void func_1D4B20(void);
extern void func_14D830(void *a);

s32 title_TitleMovieStop_4f0480(void)
{
    func_1D56C0(D_00484290);
    func_1D5870(D_00484290);
    func_1D4B20();
    func_14D830(D_0048429C);
    D_00480430 = -1;
    return 1;
}
