#include "types.h"

struct S3ABDD0 { u8 pad000[0x10]; f32 f10; };
struct T3ABDD0 { u8 pad000[0x498]; struct S3ABDD0 *f498; };

s32 CharaGetActiveSlotGaugeValue_3abdd0(struct T3ABDD0 *p)
{
    struct S3ABDD0 *s;

    s = p->f498;
    if (s == 0) {
        return -1;
    }
    return (s32)s->f10;
}
