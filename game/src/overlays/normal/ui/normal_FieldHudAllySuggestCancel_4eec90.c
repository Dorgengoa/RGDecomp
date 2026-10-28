/* rgp:protos */
#define RGP_SELF_normal_FieldHudAllySuggestCancel_4eec90 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004EEC90 -- DRAFTED s27 by ORACLE TRANSFER from normal_FUN_004EE940
 * (same `A`/`N` types, the same func_3C3070(a->f18, p->f398) lookup against
 * normal_FieldHudPartyRowCount_4f9c50's count, and the same `id = i*7 + 0xA` walk) and from
 * normal_FUN_004EB400 / 004EB290 (the func_290690 / func_2905B0 / func_2904E0 /
 * func_2904B0 float-argument shapes, all MERGED).
 *
 * The three gp floats are MAIN `.lit4` POOL entries, not globals -- read out of
 * t_lit4.retail_words(): -0x7E40($28) = 0x0047D330 = -0.1f,
 * -0x7E3C = 0x0047D334 = -0.05f, -0x7E38 = 0x0047D338 = 0.05f.  Spelled as
 * literals per [[mwcc-float-literal-pool]]; scored through try.py's lit4 path.
 *
 * FOUR distinct return values (1 twice, 2, 3, 0) -- read them off the
 * `addiu $2,$0,K` in each `b .L004EEE58` delay slot.
 *
 * FIRST BUILD: RIGHT LENGTH, 2 bad -- a pure TRANSPOSITION
 * ([[residue-transposition-class]]) at 0x004EED0C/0x004EED1C.
 * ★★★★★★ CLOSED ON ONE EDIT: `*(volatile s16 *)&p->f398`.
 * The `bnel` guarding the func_1FEDE0 NULL test is a branch-LIKELY, so its
 * ANNULLED slot takes the guarded block's FIRST instruction
 * ([[mwcc-branch-likely-duplication]]).  Retail's first instruction is the
 * SECOND argument's load `lh $5,0x398($19)` and the `jal` slot then takes
 * `lw $4,0x18($2)`; ours had them the other way round.  Pinning the f398 read
 * AT ITS ACCESS SITE ([[mwcc-volatile-access-site-pin]]) stops mwcc sinking it
 * past the pointer deref and both slots land on retail's instruction.
 * ⚠ It must be the SECOND argument alone: pinning BOTH is the base object, and
 * pinning only `a->f18` is the base object.
 * MEASURED NULLS (build/wf-normal/s27/): 5 statement-order arms (named locals
 * for either or both arguments, in both orders) are ONE object -- mwcc fixes
 * the argument evaluation order regardless of source order, so this is NOT
 * reachable by reordering; 4 byte-address spellings of either argument are the
 * same object; 21 pragma knobs (6 of which change the LENGTH, so the deck is
 * armed) do not move it. */
typedef struct A {
    u8    pad000[0x18];
    void *f18;
} A;

typedef struct N {
    u8  pad000[0x378];
    s16 f378;
    u8  pad37A[0x398 - 0x37A];
    s16 f398;
    u8  pad39A[0x3A2 - 0x39A];
    s16 f3A2;
    u8  pad3A4[0x3AC - 0x3A4];
    s16 f3AC;
} N;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_FieldHudAllySuggestCancel_4eec90(N *p)
{
    A  *a;
    u16 id;
    s16 k;
    s32 i;
    s32 n;
    f32 v;

    if (p->f3A2 == 0) {
        return 1;
    }
    if (p->f378 == 0) {
        return 1;
    }
    UiFadeWidgetAlpha_290690(p, 0x60, 0.0f, -0.1f, -1.0f);
    UiFadeWidgetAlpha_290690(p, 0x65, 0.0f, -0.1f, -1.0f);
    a = ((A *)GetGameData_1fede0());
    if (a == NULL) {
        return 2;
    }
    k = PartyFindSlotOfId_3c3070(a->f18, *(volatile s16 *)&p->f398);
    n = normal_FieldHudPartyRowCount_4f9c50();
    if (k >= n) {
        for (i = 0; i < n; i++) {
            id = i * 7 + 0xA;
            UiSetWidgetColor_2905b0(p, id, 1.0f, 1.0f, 1.0f, -1.0f);
            UiFadeWidgetColor_2904e0(p, id, 1.0f, 1.0f, 1.0f, -1.0f, -0.05f);
        }
        return 3;
    }
    id = k * 7 + 0xA;
    v = *((f32 *)UiGetWidgetColor_2904b0(p, id));
    if (v > 1.0f) {
        UiFadeWidgetColor_2904e0(p, id, 1.0f, 1.0f, 1.0f, -1.0f, 0.05f);
    } else if (v < 1.0f) {
        UiFadeWidgetColor_2904e0(p, id, 1.0f, 1.0f, 1.0f, -1.0f, -0.05f);
    }
    p->f3A2 = 10;
    p->f3AC = 0;
    return 0;
}
