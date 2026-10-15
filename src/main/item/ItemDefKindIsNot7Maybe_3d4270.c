#include "types.h"

struct S3D4270 { u8 pad000[0x2]; s8 f2; };
struct T3D4270 { u8 pad000[0x10]; struct S3D4270 *f10; };

s32 ItemDefKindIsNot7Maybe_3d4270(struct T3D4270 *p)
{
    struct S3D4270 *s;

    s = p->f10;
    if (s == 0) {
        return 1;
    }
    return s->f2 != 7;
}
