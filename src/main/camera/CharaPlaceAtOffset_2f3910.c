#include "types.h"

extern f32 Cosf_128d30(f32 arg0);
extern f32 Sinf_128fd0(f32 arg0);
extern void VecAddXyzW1_1cbd80(void *arg0, s32 arg1, f32 *arg2);
extern f32 AngleWrap_1cbf30(f32 arg0);
extern void CharaPlaceAt_2f3a40(s32 arg0, void *arg1, s32 arg2, f32 arg3);
extern const f32 D_0047D1FC __attribute__((section(".sdata")));

void CharaPlaceAtOffset_2f3910(s32 arg0, s32 arg1, s32 arg2, f32 fparg0, f32 fparg1)
{
    f32 temp_f20;

    temp_f20 = AngleWrap_1cbf30(D_0047D1FC + fparg0);
    {
        f32 out[4];
        f32 buf[4] = {0};
        buf[0] = fparg1 * Sinf_128fd0(temp_f20);
        buf[2] = fparg1 * Cosf_128d30(temp_f20);
        VecAddXyzW1_1cbd80(out, arg1, buf);
        CharaPlaceAt_2f3a40(arg0, out, arg2, fparg0);
    }
}
