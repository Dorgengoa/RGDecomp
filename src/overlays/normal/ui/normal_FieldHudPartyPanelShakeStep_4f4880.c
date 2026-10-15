#include "types.h"
/* normal 0x004F4880 -- BYTE-IDENTICAL (s23).  Three levers, in order.
 *
 * (1) [[at-compare-class]] via build/wf-normal/s22/at_screen.py: retail has
 *     `slti $1,$2,3` ($at) for the `r >= 3` guard and `slti $3,$17,3` (GPR)
 *     for the `i < 3` latch, so the guard is `r > 2` and the latch stays
 *     strict.  The two halves of the rule point OPPOSITE ways -- read which
 *     compare the screen names before editing.
 *
 * (2) RETAIL HOLDS THE UN-OFFSET BASE AND FOLDS +0x300 INTO EVERY
 *     DISPLACEMENT.  In the decay branch `$19 = b + i*0x14` and every access
 *     is 0x304 / 0x308 / 0x310 off it, with `px`/`py` as `addiu $19,0x304` and
 *     `addiu $19,0x308`.  A `Slot *` CANNOT express that -- its members start
 *     at 0, so the +0x300 has to be materialised, which is the one extra
 *     `addiu` this unit was long by.  A CTX RE-BASE can, because `Ctx::s` is
 *     already at 0x300:  `w = (Ctx *)((u8 *)&b->s[i] - 0x300)` then
 *     `w->s[0].fXXX`.  One word LONG -> right length, 6 bad.
 *  => When a residue is ONE materialised constant offset, look for a struct
 *     type that already carries that offset instead of a spelling of the add.
 *
 * (3) THE `addu` OPERAND ORDER IS NOT A SOURCE TERM ORDER.  `(i + i*4)*4`,
 *     `((i<<2)+i)*4`, `(i*4+i)*4`, `((i<<2)+i)<<2` and `(i+(i<<2))*4` all give
 *     `addu $2,$17,$2`; retail has `addu $2,$2,$17`.  ONLY the member access
 *     `&b->s[i]` compiles to retail's order (the top-of-loop `s` already did).
 *     But a bare member access CSEs with `s` and loses 4 more words, so both
 *     sites take the [[insect-cse-two-spellings]] split: `&b->s[(u32)i]`.
 *     `i * 0x14` also gets the order right and CSEs -- 12 words SHORT.
 *  => `(u32)` on the INDEX is what closed [[normal-cse-cost-split]]; here it
 *     buys the member-access instruction ORDER without the member-access CSE.
 *
 * ⚠ px/py are materialised in REVERSE source order: retail puts 0x304 in $2
 * and 0x308 in $30, so `py` is assigned FIRST.  Swapping the two assignments
 * is 6 bad -> 2; swapping their DECLARATIONS is inert.
 */

typedef struct Slot {
    s32 f000;
    s32 f004;
    s32 f008;
    s16 f00C;
    s16 f00E;
    f32 f010;
} Slot;

typedef struct Ctx {
    u8   pad000[0x2B0];
    s16  f2B0;
    u8   pad2B2[0x300 - 0x2B2];
    Slot s[3];
    u8   pad33C[0x430 - 0x33C];
    u8   f430;
} Ctx;

typedef struct Cam {
    u8  pad000[0x18];
    s32 f018;
} Cam;

extern f32 D_0047D538;            /* gp - 0x7C38 */
extern f32 D_0047D5D0;            /* gp - 0x7BA0 */

extern Cam *func_1FEDE0(void);
extern s32  func_3C3070(s32 a, s32 b);
extern void func_290F60(void *w, u16 id, s32 x, s32 y);

void normal_FieldHudPartyPanelShakeStep_4f4880(Ctx *b)
{
    Cam  *c;
    s32   i;
    Slot *s;
    s32   r;
    u16   id1;
    u16   id2;
    s32   v;
    s32   m;
    Ctx  *w;
    Slot *u;
    s32  *px;
    s32  *py;
    s32   x;
    s32   cnt;

    c = func_1FEDE0();
    if (c != 0) {
        for (i = 0; i < 3; i++) {
            s = &b->s[i];
            if (b->s[i].f000 >= 0) {
                r = func_3C3070(c->f018, s->f000);
                id1 = i * 7 + 6;
                id2 = i + 3;
                if (r < 0 || r > 2) {
                    u = &b->s[(u32)i];
                    func_290F60(b, id1, u->f004, u->f008);
                    func_290F60(b, id2, i * 0x7D + 0x26, 0x16F);
                    s->f000 = -1;
                } else if (b->f430 != 1 && b->f2B0 != 2) {
                    v = 0;
                    m = b->s[i].f00C % 4;
                    if (m == 0) {
                        v = (s32)(-b->s[i].f010);
                    } else if (m == 1) {
                        v = (s32)(-b->s[i].f010 / D_0047D538);
                    } else if (m == 2) {
                        v = (s32)(-b->s[i].f010 / 8.0f);
                    }
                    w = (Ctx *)((u8 *)&b->s[(u32)i] - 0x300);
                    py = &w->s[0].f008;
                    px = &w->s[0].f004;
                    w->s[0].f010 = w->s[0].f010 - D_0047D5D0;
                    func_290F60(b, id1, w->s[0].f004, w->s[0].f008 + v);
                    x = i * 0x7D + 0x26;
                    func_290F60(b, id2, x, v + 0x16F);
                    cnt = w->s[0].f00C + 1;
                    w->s[0].f00C = cnt;
                    if (w->s[0].f00E < (s16)cnt) {
                        func_290F60(b, id2, x, 0x16F);
                        func_290F60(b, id1, *px, *py);
                        s->f000 = -1;
                    }
                } else {
                    s->f000 = -1;
                }
            }
        }
    }
}
