/* rgp:protos */
#define RGP_SELF_MsgFormat_28a9a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

void *MsgFormat_28a9a0(void *a, s32 b, void *rgp_a2, unsigned char rgp_a3)
{
    if (a == 0) goto zero;
    if (b != 0) goto ok;
zero:
    return 0;
ok:
    MsgExpandTokens_28a250(a, (void *)b, (void *)rgp_a2, (unsigned char)rgp_a3);
    return a;
}
