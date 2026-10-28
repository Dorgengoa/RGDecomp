/* rgp:protos */
#define RGP_SELF_normal_BtlChgPageSetStateTable_506230 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00506230 -- one call, then `return 1`. */
/*rgp*/

s32 normal_BtlChgPageSetStateTable_506230(void *rgp_a0, int rgp_a1)
{
    UiPageSetStateTable_289c10((void *)rgp_a0, (int)rgp_a1);
    return 1;
}
