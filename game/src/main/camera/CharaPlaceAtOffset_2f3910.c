/* rgp:protos */
#define RGP_SELF_CharaPlaceAtOffset_2f3910 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D1FC __attribute__((section(".sdata")));

void CharaPlaceAtOffset_2f3910(s32 arg0, s32 arg1, s32 arg2, f32 fparg0, f32 fparg1)
{
    f32 temp_f20;

    temp_f20 = AngleWrap_1cbf30(D_0047D1FC + fparg0);
    {
        f32 out[4] __attribute__((aligned(16)));
        f32 buf[4] __attribute__((aligned(16))) = {0};
        buf[0] = fparg1 * Sinf_128fd0(temp_f20);
        buf[2] = fparg1 * Cosf_128d30(temp_f20);
        VecAddXyzW1_1cbd80(out, arg1, buf);
        CharaPlaceAt_2f3a40(arg0, out, arg2, fparg0);
    }
}
