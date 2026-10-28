/* rgp:protos */
#define RGP_SELF_ObjRefTableDtor_3148d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Deleting destructor with an owned sub-object at +0.  ObjRefSlotDtor_314960's address
   is taken (%hi/%lo of a text symbol).  The signed-16-bit release is the tail. */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void *ObjRefTableDtor_3148d0(void *self, s16 n, int rgp_a2, int rgp_a3)
{
    void *p;

    if (self == 0) {
        goto done;
    }
    HandleRegistryClear_314790((void *)self, (int)n, (int)rgp_a2, (int)rgp_a3);
    p = *(void **)self;
    if (p != 0) {
        DestroyArray_1005b0(p, (void *)ObjRefSlotDtor_314960, 8, 0x200);
        OperatorDelete_100840(p);
    }
    if (n > 0) {
        OperatorDelete_100840(self);
    }
done:
    return self;
}
