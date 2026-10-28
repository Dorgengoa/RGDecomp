/* rgp:protos */
#define RGP_SELF_AbilityDataMatchesType_3f57d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct P3F57D0 { u8 pad000[0x3]; u8 m3; } P3F57D0;
s32 AbilityDataMatchesType_3f57d0(P3F57D0 *p, s32 v)
{
    if (v < 0) goto yes;
    if (p->m3 != v) goto no;
yes:
    return 1;
no:
    return 0;
}
