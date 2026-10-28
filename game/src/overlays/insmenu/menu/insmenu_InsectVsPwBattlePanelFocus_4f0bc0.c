/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsPwBattlePanelFocus_4f0bc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004F0BC0 -- insmenu_FUN_004F0A00 with a different item accessor
 * (func_430B50), a different id table (insmenu_D_004F9990) and the 0x192..0x194
 * dispatch.  The two references differ in exactly six words; every comment
 * below was measured on 004F0A00.
 *
 * build the two-item panel, count how many of the item's two flag bits are
 * set, pick a widget id from that count and lay the panel out.
 *
 * The bit tests are BITFIELDS, not shifts: bit 0 reads as a bare `andi $2, 1`
 * and bit 1 as `dsll32 $2, 30 / dsrl32 $2, 31`, which is mwcc's one-bit
 * extraction idiom -- an explicit `(x >> 1) & 1` would be `srl`/`andi`.
 *
 * The 0x192/0x193/0x194 dispatch is a SWITCH, not an if/else-if chain: the two
 * converted `beql`s carry the CASE BODY'S constant in their delay slots, which
 * is the switch tell, and the compare chain runs 0x194/0x193/0x192 -- reverse
 * of source-case order.  case 0x192 gets a PLAIN `beq` with a `nop` slot
 * because its body assigns the value `k` already holds, so there is nothing to
 * duplicate; that is the confirmation the initialiser is the default.
 * The two orphan blocks at 0x004F0CB4 and 0x004F0CC0 are the ORIGINAL case
 * arms, left unreachable by that same delay-slot duplication -- mwcc emits
 * them from this source, they are not something to write.
 *
 * `p->field12 = k;` then `p->field12 * 57` in the same block is FORWARDED, not
 * reloaded: retail sign-extends the stored value with dsll32/dsra32 instead of
 * issuing an `lh`.  The `lh $3, 0x12($17)` before the second call is a genuine
 * reload, forced by the intervening call.
 *
 * The `h->field00 = insmenu_D_004F9990[n];` store is written OUTSIDE the `h != 0`
 * guard on purpose.  Retail computes the table load, then puts the `sw` in the
 * DELAY SLOT of `beqz $16` -- which is ordinary sinking of a store that
 * dominates the branch, not speculation past a guard.  Written inside the
 * guard, mwcc keeps the whole address computation in the guarded block and
 * forwards the value into the switch instead of reloading it: two words short,
 * and the switch then compares the loaded value rather than `lw $3, 0x0($16)`.
 */

typedef struct {
    s16 field00;
    s16 field02;
    u8 pad04[2];
    s16 field06;
    u8 pad08[2];
    s16 field0A;
    u8 pad0C[6];
    s16 field12;
} Panel;

typedef struct {
    s32 field00;
    u8 bit0 : 1;
    u8 bit1 : 1;
} Item;

typedef struct {
    u8 pad00[0x24];
    void *field24;
} Handle;

/* 0x004FA1A0, 0x004FA180 and 0x004F99A0 are OVERLAY data, far outside the gp
 * window 0x47D170..0x48D170, so every one of them must be `const` or mwcc
 * emits a single %gp_rel instruction where retail has lui + addiu -- and the
 * link would then fail with GP offset overflow. */
extern u8 insmenu_D_004FA1A0[];
extern u8 insmenu_D_004FA180[];
extern s32 insmenu_D_004F9990[];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insmenu_InsectVsPwBattlePanelFocus_4f0bc0(void)
{
    Panel *p;
    Item *h;
    s32 n;
    s32 k;

    UiEntryListSelectByTag_28ea90(insmenu_D_004FA1A0, 0x7535, 0);
    p = ((Panel *)UiEntryListGetCurrentData_28ec60(insmenu_D_004FA1A0));
    p->field06 = 0x39;
    p->field0A = 2;
    h = ((Item *)RecordGetPayloadIfKind28_430b50(((Handle *)GetGameData_1fede0())->field24));
    n = 0;
    if (h != 0) {
        if (h->bit0) {
            n++;
        }
        if (h->bit1) {
            n++;
        }
        p->field0A = n;
    }
    if (insmenu_InsectVsTakeCancelFlag_4ea0d0() == 0) {
        k = 0;
        h->field00 = insmenu_D_004F9990[n];
        if (h != 0) {
            switch (h->field00) {
            case 0x192:
                k = 0;
                break;
            case 0x193:
                k = 1;
                break;
            case 0x194:
                k = 2;
                break;
            }
        }
        p->field12 = k;
        UiSetWidgetPos_290f60(insmenu_D_004FA180, 0x23, p->field00, p->field02 + p->field12 * 57);
        UiSetWidgetPos_290f60(insmenu_D_004FA180, 0x21, 0, p->field12 * 57);
        UiSetWidgetAlpha_2907a0(insmenu_D_004FA180, 0x21, 1.0f);
    }
    insmenu_InsectVsPwWatchPanelBright_4f0ec0();
    insmenu_InsectVsListSetRowColors_4ea110(0x22, 3, n);
    insmenu_InsectVsPwWatchCursorFadeIn_4f0e70();
}
