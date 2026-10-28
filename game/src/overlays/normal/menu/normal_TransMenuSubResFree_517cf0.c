/* rgp:protos */
#define RGP_SELF_normal_TransMenuSubResFree_517cf0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00517CF0 -- the handle is RE-READ after the call (retail's frame is
 * 0x10, no callee-saved register), so the guard load cannot be CSE'd with the
 * argument load: the global is volatile. */

extern void *D_0048478C;                   /* gp - 0x9E4 */
extern void *volatile D_00484784;          /* gp - 0x9EC */

/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_TransMenuSubResFree_517cf0(void)
{
    LoadHandleArrayFree_28b0f0(D_0048478C, 9);
    if (D_00484784 != NULL) {
        HeapHandleFree_1cdae0(GetLoaderMgr_1f59d0(), D_00484784);
        D_00484784 = NULL;
    }
    return 1;
}
