#include "types.h"

/* title.bin overlay, 0x004F0440 -- three calls, the first feeding the second,
 * then two gp-relative stores. */

extern s32 D_004842A0;
extern s32 D_00484290;
extern s32 D_00480430;
extern void *func_15DE40(void);
extern void func_158AC0(void *a, s32 b);
extern void func_17FE80(s32 a);

void title_TitleMovieRelease_4f0440(void)
{
    func_158AC0(func_15DE40(), D_004842A0);
    func_17FE80(1);
    D_00484290 = 0;
    D_00480430 = -1;
}
