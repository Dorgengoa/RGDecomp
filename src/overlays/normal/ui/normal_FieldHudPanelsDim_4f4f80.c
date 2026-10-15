/* SESSION 31: LENGTH-WRONG -> 86 words, 25 bad, scoreable for the first time.
 * The lever is the pool-wide BOOLEAN-STRUCTURE deck (mkbool31.py): a nested
 * `if (A) { if (B) { X } }` rewritten as `if (A && B) { X }`.  That family is
 * live on 7 of 12 sites across the pool; `||` was settled long ago and the
 * `&&` half had never been swept.
 * KEEP OUT OF config/ocunits/normal.txt.
 * SESSION 38 (n38h): retail's loop guard is actually a `continue`-shaped
 * skip (`if (sel != i) {...} else if (sel != -1) continue;` -- read L28
 * bnel/L31 bnel in the retail listing), not a single wrapping `if`.
 * Rewrote the loop body as `if (sel == i && sel != -1) continue;` followed
 * by the unconditional work -- MEASURED NULL: byte-identical object to the
 * `if (sel != i || sel == -1) { work }` wrapping form (still 86 words, 25
 * bad, same word-for-word diff).  25-bad residue starts at 0x4F5008 (right
 * after the func_290460 call) and was not decoded further this session. */
#include "types.h"
/* normal 0x004F4F80 -- dims every row except the selected one; a row whose box
 * is already showing only gets the tween, an empty one gets the snap too.
 * The `dsll32/dsra32 ,24` pairs are s8 casts on the slot id. */
typedef struct Box {
    u8  pad000[0x8];
    s64 f08;
} Box;

typedef struct Ret {
    u8   pad000[0x24];
    Box *f24;
} Ret;

typedef struct N {
    u8  pad000[0x378];
    s16 f378;
} N;

extern void *func_1FEDE0(void);
extern s32   normal_FieldHudPartyRowCount_4f9c50(N *p);
extern Ret  *func_290460(N *p, s32 id);
extern void  func_2904E0(N *p, s32 id, f32 a, f32 b, f32 c, f32 d, f32 e);
extern void  func_2905B0(N *p, s32 id, f32 a, f32 b, f32 c, f32 d);

void normal_FieldHudPanelsDim_4f4f80(N *p, s32 sel)
{
    Ret *r;
    Box *b;
    s32  n;
    s32  i;

    if (p->f378 == 0) {
        return;
    }
    if (func_1FEDE0() == NULL) {
        return;
    }
    n = normal_FieldHudPartyRowCount_4f9c50(p);
    for (i = 0; i < n; i++) {
        if (sel == i && sel != -1) {
            continue;
        }
        r = func_290460(p, (s8)(i * 7 + 0xB));
        if (r != NULL) {
            b = r->f24;
            if (b != NULL) {
                s32 t = (s8)(i * 7 + 6);
                if (b->f08 > 0) {
                    func_2904E0(p, (s8)t, 0.7f, 0.7f, 0.7f,
                                -1.0f, -0.0523f);
                } else {
                    func_2904E0(p, (u16)(s8)t, 0.7f, 0.7f, 0.7f,
                                -1.0f, -0.0523f);
                    func_2905B0(p, (u16)(s8)t, 0.7f, 0.7f, 0.7f,
                                -1.0f);
                }
            }
        }
    }
}
