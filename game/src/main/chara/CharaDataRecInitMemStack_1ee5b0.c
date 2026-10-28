/* rgp:protos */
#define RGP_SELF_CharaDataRecInitMemStack_1ee5b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

void CharaDataRecInitMemStack_1ee5b0(u8 *p, int rgp_a1, int rgp_a2)
{
    MemStackInit_14d810(p + 8, (int)rgp_a1, (int)rgp_a2);
    MemStackReset_14d830(p + 8);
}
