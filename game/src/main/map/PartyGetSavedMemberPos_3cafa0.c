/* rgp:protos */
#define RGP_SELF_PartyGetSavedMemberPos_3cafa0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct V4_3CAFA0 { s32 a; s32 b; s32 c; s32 d; };

/*rgp*/

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
