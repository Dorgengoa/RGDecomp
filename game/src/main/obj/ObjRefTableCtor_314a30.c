/* rgp:protos */
#define RGP_SELF_ObjRefTableCtor_314a30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* MEASURED (q12 sweep, 6 arms): the guard must test the CALL RESULT, not a
   named local -- `if ((p = f()) != 0)` gives a plain `beqz $2` with the copy
   to $16 in its delay slot, while `p = f(); if (p != 0)` gives `beqzl $16`
   and DUPLICATES the join block's store into the likely slot, one word too
   many.  The plain-local, goto and extra-temporary arms are ONE object
   (sha1 a37144d7).  Retail FALLS THROUGH into the registration call, so the
   guard is `!= 0`.  Both callback addresses are %hi/%lo text symbols. */
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
void *ObjRefTableCtor_314a30(void *self)
{
    void *p;
    if ((p = OperatorNew_100990(0x1000)) != 0) {
        ConstructArray_100620(p, (void *)ObjRefSlotCtor_314a90, (void *)ObjRefSlotDtor_314960, 8, 0x200);
    }
    *(void **)self = p;
    return self;
}
