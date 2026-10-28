/* rgp:protos */
#define RGP_SELF_normal_TransMenuResFree_5181a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x005181A0 -- one call, `return 1`. */

extern void *D_00484788;          /* gp - 0x9E8 */

/*rgp*/

s32 normal_TransMenuResFree_5181a0(void)
{
    LoadHandleArrayFree_28b0f0(D_00484788, 1);
    return 1;
}
