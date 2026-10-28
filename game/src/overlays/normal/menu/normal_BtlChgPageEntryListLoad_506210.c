/* rgp:protos */
#define RGP_SELF_normal_BtlChgPageEntryListLoad_506210 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00506210 -- one call, then `return 1`. */
/*rgp*/

s32 normal_BtlChgPageEntryListLoad_506210(void *rgp_a0, int rgp_a1, int rgp_a2, int rgp_a3)
{
    UiPageEntryListReload_289b70((void *)rgp_a0, (int)rgp_a1, (int)rgp_a2, (int)rgp_a3);
    return 1;
}
