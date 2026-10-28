/* rgp:protos */
#define RGP_SELF_EventPlayerIsArgZeroOrOneRelated_23ff70 1
#include "port/game_protos.h"
#line 1
#include "types.h"
s32 EventPlayerIsArgZeroOrOneRelated_23ff70(s32 a, u8 v)
{
    if (v == 1) return 1;
    return v == 0;
}
