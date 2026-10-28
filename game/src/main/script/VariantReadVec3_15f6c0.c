/* rgp:protos */
#define RGP_SELF_VariantReadVec3_15f6c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Three consecutive 8-byte records parsed into a float triple.  The cursor
   advances in the call's delay slot, which is the post-increment form. */

typedef struct Rec8 {
    u8 b[8];
} Rec8;

/*rgp*/

float VariantReadVec3_15f6c0(f32 *out, Rec8 *p)
{ float rgp_v0 = 0;
    out[0] = VariantGetFloat_15f740(p++);
    out[1] = VariantGetFloat_15f740(p++);
    out[2] = (rgp_v0 = VariantGetFloat_15f740(p));
return rgp_v0; }
