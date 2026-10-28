/* rgp:protos */
#define RGP_SELF_IsInBattle_288420 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the small-data u8 D_004821B8. */

extern u8 D_004821B8;

u8 IsInBattle_288420(void)
{
    return D_004821B8;
}
