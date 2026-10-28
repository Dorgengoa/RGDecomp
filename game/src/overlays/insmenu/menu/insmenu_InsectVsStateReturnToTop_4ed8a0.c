/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsStateReturnToTop_4ed8a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x004ED8A0 -- the handle is held in a callee-saved register
 * ($16, saved with sq/lq) across two calls and its +0x24 member is
 * RE-READ for the second, because the call boundary forces the
 * reload.  `beql $2, $0, <join>` exits to the join carrying
 * `ld $31`, so the two stores are the != 0 arm and the `return 1`
 * is materialised ONCE at the join.
 *
 * The member must be a STRUCT MEMBER, not `*(void **)((u8 *)h +
 * 0x24)`: written as the cast expression twice, mwcc CSEs the
 * ADDRESS into $16 and reloads `lw $4, 0x0($16)` where retail
 * caches the BASE and reloads `lw $4, 0x24($16)`.  Right length,
 * 2 wrong words. */
typedef struct {
    u8 pad00[0x24];
    void *field24;
} Handle;

/*rgp*/
/*rgp*/
/*rgp*/
s32 insmenu_InsectVsStateReturnToTop_4ed8a0(void)
{
    Handle *h = ((Handle *)GetGameData_1fede0());
    s32 *p;

    RecordSetMode_431310(h->field24, 2);
    p = ((s32 *)RecordGetPayloadIfKind14_430b90(h->field24));
    if (p != 0) {
        p[0] = 3;
        p[1] = 0x1E;
    }
    return 1;
}
