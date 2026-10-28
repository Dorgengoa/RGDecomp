/* rgp:protos */
#define RGP_SELF_PtmfTest_100eb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct T100EB0 { s32 f00; s32 f04; s32 f08; };

s32 PtmfTest_100eb0(struct T100EB0 *p)
{
    s32 v;

    v = p->f00;
    v |= p->f04;
    v |= p->f08;
    return v != 0;
}
