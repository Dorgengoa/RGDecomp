/* rgp:protos */
#define RGP_SELF_normal_BtlChgPageSetMemStack_506270 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00506270 -- one call, then `return 1`. */
/*rgp*/

s32 normal_BtlChgPageSetMemStack_506270(void *rgp_a0, int rgp_a1)
{
    UiPageSetMemStack_289c40((void *)rgp_a0, (int)rgp_a1);
    return 1;
}
