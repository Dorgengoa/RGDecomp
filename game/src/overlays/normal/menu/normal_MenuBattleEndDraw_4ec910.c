/* rgp:protos */
#define RGP_SELF_normal_MenuBattleEndDraw_4ec910 1
#include "port/game_protos.h"
#line 1
/* SESSION 32 (2026-09-05, lane nc32h): MATCH.
 * s21 parked this at 25 words / 3 bad, all three the same class: ours put
 * `v = p->f00` in `$4`, retail in `$5` (`lw` / `bltzl` / `bne`).  s21's
 * proposed rule ("the first register above the highest argument register any
 * call uses") is NOT the mechanism, and neither is any spelling of the body:
 * 24 arms this session -- double-reading `p->f00` instead of naming it, a
 * `&p->f00` pointer, a u8 flag local, early-return vs nested guard, flat vs
 * else-if, `!(x < 0)`, `(v = p->f00) >= 0`, a `q = p` copy, block-scoped `v`,
 * an unused second parameter, and a C++ port -- put 21 of 24 on ONE object.
 *
 * The lever is the CALLEE SIGNATURE, not the body: normal_MenuBattleEndDrawWindowMaybe_4ea1a0 TAKES
 * `p`.  Nothing sets up the argument (`jal` + `nop`, and $4 still holds the
 * incoming pointer), which is exactly why it was invisible -- the call is
 * argument-free in the listing.  Passing p keeps the incoming a0 web LIVE
 * across the `lw`, so $4 is not free when `v` is coloured and `v` takes $5.
 * The copy into the callee-saved $16 in the beqz delay slot is the split of
 * that same web, not a replacement for it.
 * Also MATCH, same object: `normal_MenuBattleEndDrawWindowMaybe_4ea1a0(p, v)` (v coalesces into the
 * a1 slot), `(void *p, s32 v)`, an `s32` return type, and a K&R declaration.
 * `normal_MenuBattleEndDrawWindowMaybe_4ea1a0(v)` alone stays at 3 bad -- it is the POINTER argument
 * that pays.  Passing v to either of the other two calls costs 3-4 words.
 */
#include "types.h"
typedef struct N {
    s32 f00;
    u8  pad004[0x10];
    u8  f014[0xFD];
    u8  f111;
} N;

/*rgp*/
/*rgp*/
/*rgp*/

void normal_MenuBattleEndDraw_4ec910(N *p)
{
    s32 v;

    if (p->f111 != 0) {
        v = p->f00;
        if (v >= 0) {
            normal_MenuBattleEndDrawWindowMaybe_4ea1a0(p);
            normal_MenuBattleEndDrawLevelUpGlow_4e9f00(p);
            UiDrawWidgets_291910(p->f014);
        } else if (v == -2) {
            UiDrawWidgets_291910(p->f014);
        }
    }
}
