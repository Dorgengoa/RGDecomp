#include "objrec.h"

/* Clear an arbitrary mask, passed in the FOURTH argument. The three leading
   parameters are forwarded to the lookup untouched, which is why only $7 is
   saved across the call. */

void ObjRecClearFlags_1c3dc0(void *owner, s32 which, s32 index, s32 mask)
{
    ObjRec *r;

    r = ObjRecLookup_1c3ef0(owner, which, index);
    if (r != 0) {
        r->flags &= ~mask;
    }
}
