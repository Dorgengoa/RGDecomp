#include "types.h"

extern void MatDecomposeScaleRotPos_1cad20(void *, void *, void *, s32);
extern void EventObjSetScale_2e72e0(s32, void *);
extern void EventObjSetRot_2e7240(s32, void *);
extern void EventObjSetPos_2e7230(s32, void *);
typedef unsigned __int128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void EventObjSetFromMatrix_2e72f0(s32 p0, s32 p1)
{
    u128 v40;
    u128 v30;
    u128 v20;

    MatDecomposeScaleRotPos_1cad20(&v40, &v30, &v20, p1);
    EventObjSetScale_2e72e0(p0, &v40);
    EventObjSetRot_2e7240(p0, &v30);
    EventObjSetPos_2e7230(p0, &v20);
}
