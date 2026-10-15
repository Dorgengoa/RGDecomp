#include "types.h"

/* Call the setup below, then return the object itself.
   Callee arity is the read-before-write scan in build/w1_arity.py
   (transitive through untouched jals, rotated-loop reads rejected);
   parameters past the first are PASS-THROUGH and typed s32 as a
   placeholder -- the bytes cannot see their types, only their count. */

typedef struct Obj_FUN_0033eb70 Obj_FUN_0033eb70;

extern void UiPanelInit_33ea10(Obj_FUN_0033eb70 *);

Obj_FUN_0033eb70 *CaptionPanelCtor_33eb70(Obj_FUN_0033eb70 *o)
{
    UiPanelInit_33ea10(o);
    return o;
}
