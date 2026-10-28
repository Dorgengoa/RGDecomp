/* rgp:protos */
#define RGP_SELF_normal_BtlChgPageSetLayout_506250 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00506250 -- one call, then `return 1`. */
/*rgp*/

s32 normal_BtlChgPageSetLayout_506250(void *rgp_a0, int rgp_a1)
{
    UiPageSetLayout_289c30((void *)rgp_a0, (int)rgp_a1);
    return 1;
}
