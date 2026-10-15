#include "types.h"

struct T3b1850 { u8 pad000[0x8]; s32 m08; };
struct S3b1850 { u8 pad000[0x48]; struct T3b1850 *m48; };

extern struct S3b1850 *D_0048381C;
extern s32 D_00483818;
extern s32 BtlEffSetRowSelectEntry_3fae00(s32, s32, s32, s32, s32);

s32 CharaSelectBtlEffRowMaybe_3b1850(s32 a, s32 b, s32 c)
{
    struct S3b1850 *p;

    p = D_0048381C;
    if (p == 0) goto fail;
    return BtlEffSetRowSelectEntry_3fae00(p->m48->m08, b, c, a, D_00483818);
fail:
    return 0;
}
