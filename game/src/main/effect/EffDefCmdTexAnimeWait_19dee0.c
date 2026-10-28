/* rgp:protos */
#define RGP_SELF_EffDefCmdTexAnimeWait_19dee0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* `daddu $16,$2,$0` sits AFTER the jal, so $2 there is the RETURN VALUE:
   EffTexAnimeParamAppendStep_1981f0 hands back the object the tail call works on.  ctx[0] itself
   only lives in $2 across the two loads before that call.
   Two callee-saved FPRs: the LATER-declared one takes the LOWER register,
   so `a` ($f21) is declared before `b` ($f20). */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EffDefCmdTexAnimeWait_19dee0(u8 *args, s32 n, void **ctx)
{
    u8 *o = (u8 *)ctx[0];
    u8 *r;
    f32 a;
    f32 b;
    void *h;

    if (*(void **)(o + 0x54) == 0) {
        return 0;
    }
    r = (u8 *)EffTexAnimeParamAppendStep_1981f0(*(void **)(o + 0x54), *(void **)(o + 0x20), 3, 0);
    a = VariantGetFloat_15f740(args);
    b = 0.0f;
    h = 0;
    if (n > 0) {
        h = SlotGetInt_15f720(args + 8);
    }
    if (n >= 2) {
        b = VariantGetFloat_15f740(args + 0x10);
    }
    EffRandParamParse_19a3d0(r + 4, h, a, b);
    return 1;
}
