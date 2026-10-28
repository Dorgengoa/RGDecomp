/* rgp:protos */
#define RGP_SELF_title_TitleLoadGetSlotScroll_4edde0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004EDDE0 -- a guarded call whose result is dereferenced.
 *
 * The guard is `beql` -- a LIKELY branch, so its delay slot runs only when
 * TAKEN and `daddu $2, $0, $0` IS the taken arm: the zero rides in the branch
 * and the CALL is laid out inline as the fallthrough.
 *
 * Spelling it `if (p == 0) return 0;` gets the opposite polarity -- mwcc emits
 * `bnezl` around an inline zero and pays a `b` plus a `nop` for it, two words
 * long.  Guarding on the CALL puts the call inline, which is the shape retail
 * has.  A ternary is worse still (four words long).
 */

typedef struct Ret_title_FUN_004edde0 {
    u8 pad000[0x16];
    s16 field016;      /* +0x16 */
} Ret_title_FUN_004edde0;

extern void *D_0048415C;
/*rgp*/

s16 title_TitleLoadGetSlotScroll_4edde0(void)
{
    void *p;

    p = D_0048415C;
    if (p != 0) {
        return ((Ret_title_FUN_004edde0 *)UiEntryListFindDataByTag_28ec30(p, 0x7534))->field016;
    }
    return 0;
}
