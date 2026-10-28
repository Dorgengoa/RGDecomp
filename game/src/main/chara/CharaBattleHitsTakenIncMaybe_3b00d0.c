/* rgp:protos */
#define RGP_SELF_CharaBattleHitsTakenIncMaybe_3b00d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct O {
    u8  pad000[0x4AE];
    s16 m4AE;
} O;

s32 CharaBattleHitsTakenIncMaybe_3b00d0(O *o)
{
    return (s16)(++o->m4AE);
}
