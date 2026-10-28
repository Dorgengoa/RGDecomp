/* rgp:protos */
#define RGP_SELF_ArraySetChecked_152f90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Member of the 3-member BYTE-IDENTICAL group headed by ArraySetChecked_152e00; the shape and
   every lever are documented there.  Bounds-checked store into a s32 array.  The
   two guards share ONE `return`, so the second compare takes a GPR. */

typedef struct Vec32 {
    s32  m0;
    s32 *m4;
} Vec32;

void ArraySetChecked_152f90(Vec32 *v, s32 i, s32 x)
{
    if (i < 0 || i >= v->m0) {
        return;
    }
    v->m4[i] = x;
}
