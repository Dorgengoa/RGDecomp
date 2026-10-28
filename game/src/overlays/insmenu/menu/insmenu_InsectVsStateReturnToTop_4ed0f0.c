/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsStateReturnToTop_4ed0f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x004ED0F0 -- the handle is held in a callee-saved register ($16,
 * saved with sq/lq) across two calls and its +0x24 member is RE-READ for the
 * second, because the call boundary forces the reload.
 * `beql $2, $0, <join>` exits to the join carrying `ld $31`, so the two stores
 * are the != 0 arm and the `return 1` is materialised ONCE at the join --
 * a single return at the end, not one per arm.
 *
 * ★★★★ THE MEMBER MUST BE A STRUCT MEMBER, NOT `*(void **)((u8 *)h + 0x24)`.
 * Written as the cast expression twice, mwcc CSEs the ADDRESS and keeps
 * `addiu $16, $2, 0x24` in the callee-saved register, then reloads
 * `lw $4, 0x0($16)`.  Retail keeps the BASE (`daddu $16, $2, $0`) and reloads
 * `lw $4, 0x24($16)`.  Both are the right length, so only a byte compare sees
 * it -- 2 words.  A member access folds the offset into the load's immediate
 * and leaves the base as the thing worth caching. */
typedef struct {
    u8 pad00[0x24];
    void *field24;
} Handle;

/*rgp*/
/*rgp*/
/*rgp*/

s32 insmenu_InsectVsStateReturnToTop_4ed0f0(void)
{
    Handle *h = ((Handle *)GetGameData_1fede0());
    s32 *p;

    RecordSetMode_431310(h->field24, 2);
    p = ((s32 *)RecordGetPayloadIfKind14_430b90(h->field24));
    if (p != 0) {
        p[0] = 5;
        p[1] = 0x32;
    }
    return 1;
}
