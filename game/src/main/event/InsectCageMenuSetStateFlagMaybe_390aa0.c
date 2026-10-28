/* rgp:protos */
#define RGP_SELF_InsectCageMenuSetStateFlagMaybe_390aa0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
extern void *D_004832AC;
extern u8 D_00483360;

int InsectCageMenuSetStateFlagMaybe_390aa0(s32 arg0, s32 arg1) { int rgp_v0 = 0;
    s32 i;

    if (arg0 == 2) {
        i = 0;
        do {
            (rgp_v0 = BitArraySetReturnOld_384360((u8 *)D_004832AC + (i * 0x9D0) + 0x986, 8, arg1));
            i += 1;
        } while (i < 5);
        return rgp_v0;
    }
    (rgp_v0 = BitArraySetReturnOld_384360(&D_00483360, arg0, arg1));
return rgp_v0; }
