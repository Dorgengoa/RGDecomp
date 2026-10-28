/* rgp:protos */
#define RGP_SELF_InsectCageMenuGetCageInsect_390f00 1
#include "port/game_protos.h"
#line 1
/* MATCH (main s22): the MIRROR branch-likely case of
   [[mwcc-branch-likely-duplication]] -- ours emitted `bnel` with the join's
   `return p` copy (`daddu $2,$16,$0`) in the annulled slot where retail has a
   plain `bnez` + nop.  The fix is to TAKE THE SINKABLE INSTRUCTION AWAY:
   `p = NULL;` then the shared `return p;` gives the branch a join copy to
   duplicate; spelling the arm as a direct `return NULL;` removes the join and
   the branch goes plain.  (`!(x & 0xFF)` vs `(x & 0xFF) == 0` is INERT.) */
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

void *InsectCageMenuGetCageInsect_390f00(s32 p0, s32 p1)
{
    s32 h;
    void *p;

    h = InsectCageMenuGetCageItem_391060(p0);
    if (h == 0) {
        return NULL;
    }
    p = InsectRecSlotGetItem_3cfb30(h, p1);
    if (p == NULL) {
        return NULL;
    }
    if ((((unsigned char)ItemDefIsInsect_40e340(*(s32 *)((u8 *)p + 0x10))) & 0xFF) == 0) {
        return NULL;
    }
    return p;
}
