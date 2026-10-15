#include "types.h"
struct S3FC970 { u8 pad000[0x2]; s16 f02; s32 f04; };
extern struct S3FC970 *DataTableEntryFindParam_3fc9c0(void);
f32 DataTableEntryGetParamFloat_3fc970(void)
{
    struct S3FC970 *r;

    r = DataTableEntryFindParam_3fc9c0();
    if (r != 0) {
        if (r->f02 == 3) {
            return *(f32 *)&r->f04;
        }
        return (f32)r->f04;
    }
    return 0.0f;
}
