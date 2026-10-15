#include "types.h"
/* normal 0x005053C0 -- positions and sizes one two-box popup row.  Pass-33
 * LIST rank: 176 bytes, 44 instructions, THREE conditional branches, 3 calls.
 * The same thunk/handle/row guard chain as normal_FUN_005057C0.
 *
 * The eight stores are in SOURCE order -- mwcc does not reschedule them -- and
 * the order is again not address order: A.x A.y, then the two widths and the
 * two heights B-first, and B's origin LAST.
 *
 * Every path returns 0, including the one that does the work: `daddu $2,$0,$0`
 * sits in the middle of the store block because the scheduler had a slot, not
 * because it is an early exit. */

typedef struct Box  { s16 x; s16 y; s16 w; s16 h; } Box;
typedef struct Row  { Box a; Box b; } Row;
typedef struct Hold { u8 pad000[0x20]; Row *f020; } Hold;

extern Hold *func_290460(void *p, u16 id);
extern void  func_290F60(void *p, u16 id, s32 c, s32 d);
extern void *normal_UiPageGetLayout_289b60(void *p);

extern s32 normal_BtlChgPageDetailTabLayout_5053c0(void *a, u16 id);

s32 normal_BtlChgPageDetailTabLayout_5053c0(void *a, u16 id)
{
    void *w;
    Hold *h;
    Row  *r;

    w = normal_UiPageGetLayout_289b60(a);
    if (w == 0) {
        return 0;
    }
    h = func_290460(w, id);
    if (h == 0) {
        return 0;
    }
    r = h->f020;
    if (r == 0) {
        return 0;
    }
    func_290F60(w, id, 0xAB, -0x24);
    r->a.x = 0;
    r->a.y = 0;
    r->b.w = 0x66;
    r->a.w = 0x66;
    r->b.h = 0x1E;
    r->a.h = 0x1E;
    r->b.x = 0;
    r->b.y = 0x3C;
    return 0;
}
