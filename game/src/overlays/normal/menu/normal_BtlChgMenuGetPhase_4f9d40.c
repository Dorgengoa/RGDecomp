/* rgp:protos */
#define RGP_SELF_normal_BtlChgMenuGetPhase_4f9d40 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004F9D40 -- two words: return the gp s16 at _gp-0xD08. */

extern s16 D_00484468;            /* gp - 0xD08 */

s16 normal_BtlChgMenuGetPhase_4f9d40(void)
{
    return D_00484468;
}
