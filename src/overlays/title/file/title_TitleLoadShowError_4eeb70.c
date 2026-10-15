#include "types.h"

/* title.bin overlay, 0x004EEB70 -- store a halfword, then tail-call into main
 * with a gp-relative pointer and two constants.
 */

extern s16 D_00484204;
extern void *D_004841E0;
extern void func_28EDE0(void *a, s32 b, s32 c);

void title_TitleLoadShowError_4eeb70(s16 v)
{
    D_00484204 = v;
    func_28EDE0(D_004841E0, 0xA, 0);
}
