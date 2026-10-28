/* rgp:protos */
#define RGP_SELF_ObjRecSetFlag2_1c3e80 1
#include "port/game_protos.h"
#line 1
#include "objrec.h"

/* Set bit 1 of the record's flag word -- the inverse of ObjRecClearFlag2_1c3e40. */

int ObjRecSetFlag2_1c3e80(void *owner, s32 which, s32 index)
{ int rgp_v0 = 0;
    ObjRec *r;

    r = (rgp_v0 = ObjRecLookup_1c3ef0(owner, which, index));
    if (r != 0) {
        r->flags |= 2;
    }
return rgp_v0; }
