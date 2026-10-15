#include "types.h"

struct S3F5850 { u8 pad000[0x4A]; u8 f4A; };

extern struct S3F5850 *AbilityDataGetKind0Rec_3f5db0(void);

f32 AbilityDataGetGuardBreakMaybe_3f5850(void)
{
    struct S3F5850 *r;

    r = AbilityDataGetKind0Rec_3f5db0();
    if (r != 0) {
        return (f32)(u32)(r->f4A & 1);
    }
    return 0.0f;
}
