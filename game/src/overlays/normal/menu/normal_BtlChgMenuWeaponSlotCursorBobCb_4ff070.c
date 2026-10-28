/* rgp:protos */
#define RGP_SELF_normal_BtlChgMenuWeaponSlotCursorBobCb_4ff070 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004FF070 -- positions the 0x40 widget from a record's geometry and
 * drives the two 0x31/0x32 wobble widgets off a 30-frame phase counter.
 * ★ The FIRST product is its own statement (retail keeps mul.s + add.s) and
 * the two `-78.0f + -6.0f*k` / `48.0f + 6.0f*k` expressions are written INLINE,
 * because retail contracts THOSE into adda.s/madd.s.  Both forms in one
 * function, so the discriminator is read off the listing per site.
 * 0x40C00000 6.0f, 0x41F00000 30.0f, 0xC29C0000 -78.0f, 0xC0C00000 -6.0f,
 * 0x42400000 48.0f.  `mult1` is mwcc using the R5900's second multiplier for
 * an independent product -- it is not source. */

typedef struct Geo {
    s16 f000;
    s16 f002;
    s16 f004;
    s16 f006;
    u8  pad008[0x10 - 8];
    s16 f010;
    s16 f012;
} Geo;

typedef struct Rec { u8 pad000[0x14]; s16 f014; } Rec;

extern void *D_0048449C;          /* gp - 0xCD4 */
extern void *D_004844A0;          /* gp - 0xCD0 */
extern f32   D_004844B8;          /* gp - 0xCB8 */
extern s32   D_004844D8;          /* gp - 0xC98 */
extern f32   D_0047D3F4;          /* gp - 0x7D7C */
extern f32   D_0047D3F0;          /* gp - 0x7D80 */
extern f32   D_0047D1FC;          /* gp - 0x7F74 */
extern u8 normal_D_00527020[];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_BtlChgMenuWeaponSlotCursorBobCb_4ff070(Geo *p)
{
    s32 x;
    s32 y;
    f32 t;
    f32 k;

    x = 0;
    y = 0;
    UiGetWidgetPos_2910a0(D_0048449C, 0x3E, &x, &y);
    x = x - 0x14;
    y = y + 4;
    PhaseAdvanceWrapPi_28b630(&D_004844B8, D_0047D3F4);
    t = 6.0f * Sinf_128fd0(D_004844B8);
    UiMoveWidgetUniform_290f50(D_0048449C, 0x40, (s32)(t + (f32)(x + p->f000 + p->f010 * p->f004)), y + p->f002 + p->f012 * p->f006, D_0047D3F0, 0

);
    k = Sinf_128fd0(D_0047D1FC * (f32)D_004844D8 / 30.0f);
    D_004844D8 = D_004844D8 + 1;
    if (D_004844D8 >= 0x1E) {
        D_004844D8 = 0;
    }
    UiSetWidgetPos_290f60(D_0048449C, 0x31, (s32)(-78.0f + -6.0f * k), 0x17);
    UiSetWidgetPos_290f60(D_0048449C, 0x32, (s32)(48.0f + 6.0f * k), 0x17);
    UiSetWidgetAlpha_2907a0(D_0048449C, 0x31, k);
    UiSetWidgetAlpha_2907a0(D_0048449C, 0x32, k);
    normal_FieldHudPanelSelectHide_4f4eb0(normal_D_00527020, ((Rec *)UiEntryListFindByTag_28ea40(D_004844A0, 0x55F2))->f014);
    return 1;
}
