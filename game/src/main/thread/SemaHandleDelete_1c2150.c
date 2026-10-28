/* rgp:protos */
#define RGP_SELF_SemaHandleDelete_1c2150 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct T1C2150 { s32 f0; };

extern s32 DeleteSema(s32);

void SemaHandleDelete_1c2150(struct T1C2150 *p)
{
    if (*(volatile s32 *)&p->f0 > 0) {
        DeleteSema(p->f0);
    }
    p->f0 = -1;
}
