/* rgp:protos */
#define RGP_SELF_GameReqListAlloc_20a510 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct T20A510 { void *f00; u8 pad004[0x2]; s16 f06; };

/*rgp*/

void GameReqListAlloc_20a510(struct T20A510 *p, s32 n, void *a)
{
    void *r;

    if (a == 0) return;
    r = MemStackNew_14e1b0(n * 20, a);
    p->f00 = r;
    if (r == 0) return;
    p->f06 = (s16)n;
}
