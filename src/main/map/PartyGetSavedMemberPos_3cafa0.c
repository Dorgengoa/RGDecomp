#include "types.h"

struct V4_3CAFA0 { s32 a; s32 b; s32 c; s32 d; };

extern void VecCopy_1cbe30(struct V4_3CAFA0 *dst, u8 *src);

void PartyGetSavedMemberPos_3cafa0(u8 *base, s32 i, struct V4_3CAFA0 *out)
{
    if (i < 0) goto fail;
    if (i < 3) goto ok;
fail:
    out->a = 0;
    out->b = 0;
    out->c = 0;
    out->d = 0;
    return;
ok:
    VecCopy_1cbe30(out, base + i * 16 + 0xA0);
}
