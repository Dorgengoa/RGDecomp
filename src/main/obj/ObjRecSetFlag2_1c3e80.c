#include "objrec.h"

/* Set bit 1 of the record's flag word -- the inverse of ObjRecClearFlag2_1c3e40. */

void ObjRecSetFlag2_1c3e80(void *owner, s32 which, s32 index)
{
    ObjRec *r;

    r = ObjRecLookup_1c3ef0(owner, which, index);
    if (r != 0) {
        r->flags |= 2;
    }
}
