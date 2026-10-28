/* rgp:protos */
#define RGP_SELF_normal_TransSaveDrawSlotIconsCb_518660 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00518660 -- a FIVE integer-parameter callback (EABI: the fifth
 * lands in $8, which is the register retail's `beqz $8` guard reads).  Both
 * guards fall into the shared `return 1`. */

extern void *D_00484710;   /* gp - 0xA60 */

/*rgp*/
/*rgp*/

s32 normal_TransSaveDrawSlotIconsCb_518660(void *a, s32 b, s32 c, s32 d, s32 e)
{
    if (e != 0) {
        if (D_00484710 != NULL) {
            SaveMenuDrawSlotIconFrames_3764b0(a, 0, normal_TransSaveGetSlotScroll_519e20());
        }
    }
    return 1;
}
