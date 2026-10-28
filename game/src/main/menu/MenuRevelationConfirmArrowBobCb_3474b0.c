/* rgp:protos */
#define RGP_SELF_MenuRevelationConfirmArrowBobCb_3474b0 1
#include "port/game_protos.h"
#line 1
/* MATCH (s41m). Stale pre-match note follows -- PARKED: 1 round trip: mechanical m2c conversion; length 0x84 vs retail 0x8C. */
#include "types.h"
#pragma opt_common_subs off

/*rgp*/
/*rgp*/
extern f32 D_0047D1FC __attribute__((section(".sdata")));
extern f32 D_0047D3B8 __attribute__((section(".sdata")));
extern s32 D_00482360 __attribute__((section(".sdata")));
extern f32 D_00482E30;

s32 MenuRevelationConfirmArrowBobCb_3474b0(void)
{
    f32 temp_f1;
    f32 m;

    temp_f1 = D_00482E30 + D_0047D3B8;
    D_00482E30 = temp_f1;
    if (!(temp_f1 <= 0.0f)) {
        D_00482E30 = temp_f1 - D_0047D1FC;
    }
    m = 12.0f * Sinf_128fd0(D_00482E30);
    UiMoveWidgetUniform_290f50(D_00482360, 0x63, (s32)(-20.0f + m), 8, 0.25f, 0);
    return 1;
}
