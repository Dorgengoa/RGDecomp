/* rgp:protos */
#define RGP_SELF_normal_TransSaveIconSysInit_518a50 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00518A50 -- guarded pair of teardown calls on one gp handle. */

extern void *D_00484724;   /* gp - 0xA4C */

/*rgp*/
/*rgp*/

void normal_TransSaveIconSysInit_518a50(s32 a)
{
    if (a != 0) {
        SaveIconFilesSetAll_375b10(D_00484724, a);
        SaveIconSysBuild_375d10(D_00484724);
    }
}
