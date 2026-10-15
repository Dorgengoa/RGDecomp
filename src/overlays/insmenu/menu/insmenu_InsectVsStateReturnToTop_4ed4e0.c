#include "types.h"
/* insmenu 0x004ED4E0 -- the handle is held in a callee-saved register
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

extern Handle *func_1FEDE0(void);
extern void func_431310(void *a, s32 b);
extern s32 *func_430B90(void *a);
s32 insmenu_InsectVsStateReturnToTop_4ed4e0(void)
{
    Handle *h = func_1FEDE0();
    s32 *p;

    func_431310(h->field24, 2);
    p = func_430B90(h->field24);
    if (p != 0) {
        p[0] = 4;
        p[1] = 0x28;
    }
    return 1;
}
