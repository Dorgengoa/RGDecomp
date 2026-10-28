/* rgp:protos */
#define RGP_SELF_LightningMgrAllocBolts_2d6690 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void LightningMgrAllocBolts_2d6690(s32 *arg0, void *rgp_a1) {
    s32 i;

    *arg0 = ((s32)ConstructNewArray_100710(((s32)MemStackNew_14e1b0(0x3410, (void *)rgp_a1)), (void *)LightningBoltCtor_2d6720, 0, 0xD0, 0x40));
    i = 0;
    do {
        LightningBoltInit_2d6750(*arg0 + (i * 0xD0));
        i += 1;
    } while (i < 0x40);
}
