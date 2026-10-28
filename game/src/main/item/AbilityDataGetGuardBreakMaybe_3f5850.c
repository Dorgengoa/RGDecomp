/* rgp:protos */
#define RGP_SELF_AbilityDataGetGuardBreakMaybe_3f5850 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct S3F5850 { u8 pad000[0x4A]; u8 f4A; };

/*rgp*/

f32 AbilityDataGetGuardBreakMaybe_3f5850(void *rgp_a0)
{
    struct S3F5850 *r;

    r = ((struct S3F5850 *)AbilityDataGetKind0Rec_3f5db0((void *)rgp_a0));
    if (r != 0) {
        return (f32)(u32)(r->f4A & 1);
    }
    return 0.0f;
}
