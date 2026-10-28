/* rgp:protos */
#define RGP_SELF_normal_TransMenuResRequest_518370 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00518370 -- teardown list, `return 0`. */

extern void *D_00484788;          /* gp - 0x9E8  */
extern void *D_004802A4;          /* gp - 0x4ECC */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_TransMenuResRequest_518370(void)
{
    LoadHandleArrayReset_28b160(D_00484788, 1);
    LoadHandleRequestFile_28b550(D_00484788, D_004802A4, 0, 0);
    LoaderQueueAppendSeparator_1cd670(GetLoaderMgr_1f59d0());
    return 0;
}
