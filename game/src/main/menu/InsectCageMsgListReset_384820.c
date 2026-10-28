/* rgp:protos */
#define RGP_SELF_InsectCageMsgListReset_384820 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct T384820 { u8 *f00; s32 f04; };

/*rgp*/

void InsectCageMsgListReset_384820(struct T384820 *p)
{
    s32 i;

    for (i = 0; i < 0x40; i++) {
        InsectCageMsgEntryReset_3848d0(p->f00 + i * 264);
    }
    p->f04 = 0;
}
