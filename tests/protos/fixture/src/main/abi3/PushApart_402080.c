#include "types.h"
/* rule u128-view, extra lane (2026-10-25): the definition has ONE GPR parameter and
   its listing never reads $a1; the caller's view passes a u128 there (EvMapObjPartStep_363ba0
   -> VecSolveDistanceConstraint_364740): on i686 the u128 is a word in front of the floats */
void PushApart_402080(f32 *p, f32 a, f32 b)
{
    p[0] = a;
    p[1] = b;
}
