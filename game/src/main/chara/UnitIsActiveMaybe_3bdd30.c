/* rgp:protos */
#define RGP_SELF_UnitIsActiveMaybe_3bdd30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct P { u8 pad[0x408]; u8 b0 : 1; u8 b1 : 1; u8 b2 : 1; u8 b3 : 1; u8 b4 : 1; u8 b5 : 1; u8 b6 : 1; u8 b7 : 1; } P;

/*rgp*/

s32 UnitIsActiveMaybe_3bdd30(P *p, int rgp_a1, int rgp_a2, int rgp_a3)
{
    return ((unsigned char)CharaIsNotDead_3b66f0(p, (int)rgp_a1, (int)rgp_a2, (int)rgp_a3)) != 0 ? p->b2 : 0;
}
