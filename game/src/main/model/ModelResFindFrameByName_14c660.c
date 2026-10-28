/* rgp:protos */
#define RGP_SELF_ModelResFindFrameByName_14c660 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Linear scan.  The redundant second null test on the head is an inlined
   count accessor written as a ternary (plain branch, not branch-likely).
   The stride is RE-READ through p0->m00 every iteration -- retail
   recomputes the cheap index across the call (the CSE cost split), so the
   source reads the member at its use.
   Callee-saved order: $18 p, $17 i, $16 cnt -> that declaration order. */

struct Head {
    u8 pad000[0xC];
    s32 mC;    /* count  */
    u8 pad010[4];
    s32 m14;   /* stride */
    u8 *m18;   /* base   */
};

struct Obj {
    struct Head *m00;
};

/*rgp*/

u8 *ModelResFindFrameByName_14c660(struct Obj *p0, void *p1)
{
    struct Head *h;
    u8 *p;
    s32 i;
    s32 cnt;

    h = p0->m00;
    if (h == 0) {
        return 0;
    }
    p = h->m18;
    cnt = (h != 0) ? h->mC : 0;
    for (i = 0; i < cnt; i++) {
        if (NameEqualBeforeDashes_14c710(p1, *(s32 *)p) != 0) {
            return p;
        }
        p += p0->m00->m14;
    }
    return 0;
}
