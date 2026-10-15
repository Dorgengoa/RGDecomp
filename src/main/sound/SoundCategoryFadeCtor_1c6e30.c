#include "types.h"

/* Call the setup below, then return the object itself.
   Callee arity is the read-before-write scan in build/w1_arity.py
   (transitive through untouched jals, rotated-loop reads rejected);
   parameters past the first are PASS-THROUGH and typed s32 as a
   placeholder -- the bytes cannot see their types, only their count. */

typedef struct Obj_FUN_001c6e30 Obj_FUN_001c6e30;

extern void SoundCategoryFadeInit_1b60c0(Obj_FUN_001c6e30 *);

Obj_FUN_001c6e30 *SoundCategoryFadeCtor_1c6e30(Obj_FUN_001c6e30 *o)
{
    SoundCategoryFadeInit_1b60c0(o);
    return o;
}
