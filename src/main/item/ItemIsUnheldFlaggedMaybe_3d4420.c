#include "types.h"

struct S3D4420 { u8 pad000[0x17]; u8 f17_a : 7; u8 f17_b : 1; };
struct T3D4420 { u8 pad000[0x10]; struct S3D4420 *f10; };

extern s32 PartyFindItemHolder_3d4c20(void);

s32 ItemIsUnheldFlaggedMaybe_3d4420(struct T3D4420 *p)
{
    struct S3D4420 *q;
    s32 t;

    q = p->f10;
    if (q == 0) return 0;
    if (q->f17_b == 0) return 0;
    t = PartyFindItemHolder_3d4c20() != 0;
    if (t == 0) goto one;
    return 0;
one:
    return 1;
}
