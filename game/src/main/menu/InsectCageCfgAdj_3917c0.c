/* rgp:protos */
#define RGP_SELF_InsectCageCfgAdj_3917c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
extern s32 D_00483430;
extern s16 D_00483434;

s32 InsectCageCfgAdj_3917c0(s64 *arg0) { __typeof__(arg0) rgp_entry_arg0 = arg0;
    f32 f0;
    f32 f20;
    f32 f21;
    s32 temp_16;
    s64 *p;
    u8 *rec;

    arg0++;
    temp_16 = VariantGetInt_15f780((void *)rgp_entry_arg0);
    f21 = VariantGetFloat_15f740((s32)arg0++);
    f20 = VariantGetFloat_15f740((s32)arg0++);
    f0 = VariantGetFloat_15f740((s32)arg0);
    rec = (u8 *)D_00483430 + D_00483434 * 0x10;
    *(s32 *)(rec + 0x0) = temp_16;
    *(f32 *)(rec + 0x4) = f21;
    *(f32 *)(rec + 0x8) = f20;
    *(f32 *)(rec + 0xC) = f0;
    D_00483434 += 1;
    return 0;
}
