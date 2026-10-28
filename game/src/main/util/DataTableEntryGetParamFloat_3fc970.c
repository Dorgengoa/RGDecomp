/* rgp:protos */
#define RGP_SELF_DataTableEntryGetParamFloat_3fc970 1
#include "port/game_protos.h"
#line 1
#include "types.h"
struct S3FC970 { u8 pad000[0x2]; s16 f02; s32 f04; };
/*rgp*/
f32 DataTableEntryGetParamFloat_3fc970(void *rgp_a0, int rgp_a1)
{
    struct S3FC970 *r;

    r = ((struct S3FC970 *)DataTableEntryFindParam_3fc9c0((void *)rgp_a0, (int)rgp_a1));
    if (r != 0) {
        if (r->f02 == 3) {
            return *(f32 *)&r->f04;
        }
        return (f32)r->f04;
    }
    return 0.0f;
}
