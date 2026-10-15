#include "types.h"

/* Deleting destructor with an owned sub-object at +0.  ObjRefSlotDtor_314960's address
   is taken (%hi/%lo of a text symbol).  The signed-16-bit release is the tail. */

extern void HandleRegistryClear_314790(void);
extern void ObjRefSlotDtor_314960(void);
extern void DestroyArray_1005b0(void *a, void *b, s32 c, s32 d);
extern void OperatorDelete_100840(void *p);

void *ObjRefTableDtor_3148d0(void *self, s16 n)
{
    void *p;

    if (self == 0) {
        goto done;
    }
    HandleRegistryClear_314790();
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
