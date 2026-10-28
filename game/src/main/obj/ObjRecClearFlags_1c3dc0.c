/* rgp:protos */
#define RGP_SELF_ObjRecClearFlags_1c3dc0 1
#include "port/game_protos.h"
#line 1
#include "objrec.h"

/* Clear an arbitrary mask, passed in the FOURTH argument. The three leading
   parameters are forwarded to the lookup untouched, which is why only $7 is
   saved across the call. */

int ObjRecClearFlags_1c3dc0(void *owner, s32 which, s32 index, s32 mask)
{ int rgp_v0 = 0;
    ObjRec *r;

    r = (rgp_v0 = ObjRecLookup_1c3ef0(owner, which, index));
    if (r != 0) {
        r->flags &= ~mask;
    }
return rgp_v0; }
