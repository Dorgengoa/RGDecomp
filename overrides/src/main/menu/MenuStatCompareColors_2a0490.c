/* rg-override: replaces game/src/main/menu/MenuStatCompareColors_2a0490.c sha256 03a12932d6adee60d3f3796eed6a9aa08434c55066fee0a20a474ebb67f0ec59
 * why: accessibility.colour_blind (docs/ACCESSIBILITY.md "Equipment comparison"): the stat
 * comparison's up / down digits are told apart by widget tint alone (green 0.6/1.2/0.6, red
 * 1.2/0.6/0.6); protanopia / deuteranopia tint them sky blue / vermillion (Okabe-Ito, as the
 * topmenu_08a patch).  Off and tritanopia run the generated colours unchanged (lane fpsgate 2026-11-01) */
/* rgp:protos */
#define RGP_SELF_MenuStatCompareColors_2a0490 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern f32 D_0047D288;
extern f32 D_0047D354;
int rg_texpatch_colour_blind(void);   /* src/settings/rg_texpatch.h (RG_CB_PROTAN 1, RG_CB_DEUTAN 2) */

s32 MenuStatCompareColors_2a0490(s32 p0, s32 p1, s32 p2, s32 p3, s32 p4)
{
    s32 r0;
    s32 l1;
    s64 t0;
    s16 t1;
    f32 t2;
    f32 t3;
    f32 t4;
    f32 t5;

    r0 = ((s32)UiGetWidgetSubItem_28f2b0(p1, p3, 0));
    if (r0 == 0) {
        return 0;
    }
    l1 = 0;
    do {
        UiSetSubItemFlags_28ef30(p1, p3, (long long)(0x1A0), -1, l1);
        t0 = *(s64 *)((u8 *)r0 + (l1 << 5) + 0x8);
        t1 = *(s16 *)((u8 *)p4 + (l1 << 1));
        if (t0 < t1) {
            UiSetSubItemFlags_28ef30(p1, p3, (long long)(0x80), 1, l1);
        } else {
            if (t1 == t0) {
                UiSetSubItemFlags_28ef30(p1, p3, (long long)(0x20), 1, l1);
            } else {
                UiSetSubItemFlags_28ef30(p1, p3, (long long)(0x100), 1, l1);
            }
        }
        l1 = (l1 + 1);
    } while (l1 < 6);
    {
        int cb = rg_texpatch_colour_blind();
        if (cb == 1 || cb == 2) {
            /* white glyphs x tint: 1.2 shows ~235, so ~196 per 1.0; down #D55E00, up #56B4E9 */
            UiSetWidgetColor_2905b0(p1, p3, 1.09f, 0.48f, 0.0f, 1.0f);
            UiSetWidgetColor_2905b0(p1, p2, 0.44f, 0.92f, 1.19f, 1.0f);
            return 1;
        }
    }
    t2 = D_0047D288;
    t3 = D_0047D354;
    UiSetWidgetColor_2905b0(p1, p3, t3, t2, t2, 1.0f);
    t4 = D_0047D288;
    t5 = D_0047D354;
    UiSetWidgetColor_2905b0(p1, p2, t4, t5, t4, 1.0f);
    return 1;
}
