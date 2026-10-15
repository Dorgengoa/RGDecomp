#include "types.h"

/* Three consecutive 8-byte records parsed into a float triple.  The cursor
   advances in the call's delay slot, which is the post-increment form. */

typedef struct Rec8 {
    u8 b[8];
} Rec8;

extern f32 VariantGetFloat_15f740(Rec8 *p);

void VariantReadVec3_15f6c0(f32 *out, Rec8 *p)
{
    out[0] = VariantGetFloat_15f740(p++);
    out[1] = VariantGetFloat_15f740(p++);
    out[2] = VariantGetFloat_15f740(p);
}
