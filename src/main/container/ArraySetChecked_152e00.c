#include "types.h"

/* Head of a 3-member BYTE-IDENTICAL group (56 B each): ArraySetChecked_152e00 /
   ArraySetChecked_152f90 / ArraySetChecked_153120.  Bounds-checked store into a s32 array.  The
   two guards share ONE `return`, so the second compare takes a GPR. */

typedef struct Vec32 {
    s32  m0;
    s32 *m4;
} Vec32;

void ArraySetChecked_152e00(Vec32 *v, s32 i, s32 x)
{
    if (i < 0 || i >= v->m0) {
        return;
    }
    v->m4[i] = x;
}
