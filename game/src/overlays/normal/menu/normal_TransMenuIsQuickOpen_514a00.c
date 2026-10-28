/* rgp:protos */
#define RGP_SELF_normal_TransMenuIsQuickOpen_514a00 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00514A00 -- `lb` then `sltu $2,$0,$2`: a boolean-ising read. */

extern s8 D_00484778;             /* gp - 0x9F8 */

s32 normal_TransMenuIsQuickOpen_514a00(void)
{
    return D_00484778 != 0;
}
