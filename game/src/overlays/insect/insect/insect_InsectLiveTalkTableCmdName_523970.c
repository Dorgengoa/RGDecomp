/* rgp:protos */
#define RGP_SELF_insect_InsectLiveTalkTableCmdName_523970 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vm_slot.h"
/* insect 0x00523970 -- a handler in the {opcode, fn} dispatch table at
 * insect_D_00524620, whose sibling entries (0x00523920, 0x005238D0, 0x00523880 ...)
 * are already matched as `s32 f(Slot *v)`.  That table is what names the
 * parameter: the caller marshals NOTHING into $4 here, so the arity comes from
 * the table's other handlers and from func_15F720's own marshalled call sites
 * (0x00510A44 / 0x00510A94 both set $4 from the operand cursor).
 *
 * D_00485208 is re-read after the call because the call boundary forces the
 * reload -- written as two reads of the global, not one hoisted local, per the
 * per-basic-block CSE rule. */
typedef struct InsectRec {
    s32 f00, f04, f08, f0C, f10, f14, f18, f1C, f20, f24, f28, f2C;   /* 0x30 */
} InsectRec;

typedef struct InsectCtx {
    InsectRec *base;   /* +0x00 */
    void *f04;         /* +0x04 */
    s32 f08;
    s32 count;         /* +0x0C */
} InsectCtx;

extern InsectCtx *D_00485208;
/*rgp*/
/*rgp*/
extern void memset(void *dst, s32 c, s32 n);
extern void strcpy(void *a, s32 b);

s32 insect_InsectLiveTalkTableCmdName_523970(Slot *v)
{
    InsectCtx *c;
    InsectRec *r;
    s32 t;
    void *x;

    c = D_00485208;
    r = &c->base[c->count];
    t = SlotGetInt_15f720(v);
    x = MemStackAllocQw_14d950(D_00485208->f04, 2);
    memset(x, 0, 0x20);
    strcpy(x, t);
    r->f2C = (s32)x;
    return 1;
}
