/* rgp:protos */
#define RGP_SELF_PartyGetReserveChara_3c1d20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
extern void *D_00483890;

s32 PartyGetReserveChara_3c1d20(s16 *arg0, s32 arg1) {
    s32 var_5;

    if (D_00483890 == NULL) {
        return 0;
    }
    if (arg1 < 0 || arg1 >= 7) {
        var_5 = -1;
    } else {
        var_5 = (arg0 + 0xCB)[arg1];
    }
    if (var_5 < 0) {
        return 0;
    }
    return ((s32)CharaMgrPoolFindById_3a8c60(*(s32 *)((u8 *)D_00483890 + 0x14), var_5));
}
