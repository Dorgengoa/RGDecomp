/* rgp:protos */
#define RGP_SELF_FontIsAsciiCode_26ed80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s32 FontIsAsciiCode_26ed80(void *a, s32 k)
{
    if (k != 0xFF02) goto g1;
    return 1;
g1:
    if (k >= 0) goto g2;
    return 0;
g2:
    return k < FontGetAsciiCount_26f640((int)a);
}
