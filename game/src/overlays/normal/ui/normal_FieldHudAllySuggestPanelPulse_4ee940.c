/* rgp:protos */
#define RGP_SELF_normal_FieldHudAllySuggestPanelPulse_4ee940 1
#include "port/game_protos.h"
#line 1
/* SESSION 39 (n39i, SOLO): 25 -> 23 bad, still exact 83/83 words.
 * The fix is in a PROTOTYPE, not in the body:
 *     extern s16 func_3C3070(void *p, s32 key);   (was s16 key)
 * Found by build/wf-normal/s39/multisweep.py, the batched callee-parameter
 * WIDTH sweep -- the same lever class that closed normal_InsectEntryMenuResPoll_524680,
 * normal_SpaceMenuResPollState_510e30, normal_FieldHudReshowMaybe_4f7a00 and normal_BtlChgMenuCommandSelectState_500e10 this
 * session.  `p->f398` is an s16 field; declaring the parameter s32 makes the
 * argument a widening conversion and reorders it against a->f18.
 *
 * RESIDUE (23 bad, exact length) -- the sign-extension shape around `i`:
 * retail sign-extends TWICE, `dsll32 $17,$2,16 / dsra32` for the s16 return
 * and again `dsll32 $5,$17,16 / dsra32 $5,$5,16` at the point of use, then
 * uses that ONE $5 for all three consumers (the `>=` compare, the f360 index,
 * and the i*7+0xA chain).  Ours keeps $17 unextended, uses it directly for
 * the compare and the multiply, and spends a single `andi $3,$17,0xFFFF`
 * (a ZERO-extend) for the index.
 * ⚠ THE `(u16)i` INDEX CAST IS LOAD-BEARING FOR LENGTH, counter-intuitively.
 * It is what session 31 -> 38 converged on, and every attempt to replace it
 * with the sign-extending spelling retail appears to use comes out ONE WORD
 * SHORT (0x148 vs 0x14c).  SIX arms, all measured, all 1 short: `(s16)i` on
 * the index; `(s16)i` on the multiply; `(s16)i` on the compare; the index and
 * multiply together; all three together; and a separate `s32 e = i;` local
 * feeding all three uses.  mwcc canonicalises to ONE sign-extension pair no
 * matter how many the source asks for, so the second pair retail emits is not
 * reachable by adding casts.
 * ALSO NULL: `s32 i` with the (u16) cast kept (23, same object); `s32 i` with
 * no cast, `s16 i` with `(s32)i`, and an s32 return type for func_3C3070 --
 * all length-wrong. */
/* SESSION 31 (combined six-deck sweep, 31,338 arms over 98 units).
 * Installed arm `I_u32_L43_0_idx` from the index-cast deck (mkidx31.py)
 *   before: 82 words, ? bad   after: 84 words, ? bad   (retail 83 words)
 * Every line BELOW this note predates that install -- read its numbers
 * as the state at the time it was written, not as the current score.
 * Re-score with build/wf-normal/s31/nscore.py, not dv_osbuild.py.
 * KEEP OUT OF config/ocunits/normal.txt.
 * SESSION 38 (n38h): that `(u32)i` index cast is why length was wrong (84
 * vs retail 83).  Swept the cast width: no cast -> 82 words (1 SHORT),
 * `(u32)i` -> 84 words (1 LONG), `(u16)i` -> 83 words EXACT, 25 bad -- this
 * is the correct cast width, installed.  Remaining 25-bad residue starts at
 * the very first call: retail's `func_3C3070(a->f18, p->f398)` schedules
 * `lw $4,a->f18` BEFORE the jal, with `lh $5,p->f398` in the delay slot;
 * ours schedules the two loads in the OPPOSITE order.  MEASURED NULL: a
 * `void *h = a->f18;` temp forcing the load early did not change the
 * schedule at all (byte-identical diff before/after) -- the ordering is
 * decided elsewhere, not at this call site's argument spelling.  Residue
 * continues through the id/v tween-threshold comparisons (0x4EE988-0x4EEA28)
 * and was not investigated further this session. */
#include "types.h"
/* normal 0x004EE940 -- pulses the currently selected row between scale 1.0 and
 * 1.9; only the two endpoints start a new tween.  1.9f / 0.1f / -0.05f are all
 * MAIN `.lit4` pool entries. */
typedef struct A {
    u8    pad000[0x18];
    void *f18;
} A;

typedef struct N {
    u8  pad000[0x360];
    u8  f360[0x18];
    s16 f378;
    u8  pad37A[0x398 - 0x37A];
    s16 f398;
} N;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void normal_FieldHudAllySuggestPanelPulse_4ee940(N *p)
{
    A  *a;
    u16 id;
    s32 i;
    f32 v;

    a = ((A *)GetGameData_1fede0());
    if (a == NULL) {
        return;
    }
    if (p->f378 == 0) {
        return;
    }
    i = PartyFindSlotOfId_3c3070(a->f18, p->f398);
    {
    s32 n = normal_FieldHudPartyRowCount_4f9c50();
    if ((s16)i >= n) {
        return;
    }
    id = (s16)i * 7 + 0xA;
    if (p->f360[(s16)i] != 0) {
        return;
    }
    }
    v = *((f32 *)UiGetWidgetColor_2904b0(p, id));
    if (v <= 1.0f) {
        UiSetWidgetColor_2905b0(p, id, 1.0f, 1.0f, 1.0f, -1.0f);
        UiFadeWidgetColor_2904e0(p, id, 1.9f, 1.9f, 1.9f, -1.0f, 0.1f);
    } else if (v >= 1.9f) {
        UiSetWidgetColor_2905b0(p, id, 1.9f, 1.9f, 1.9f, -1.0f);
        UiFadeWidgetColor_2904e0(p, id, 1.0f, 1.0f, 1.0f, -1.0f, -0.05f);
    }
}
