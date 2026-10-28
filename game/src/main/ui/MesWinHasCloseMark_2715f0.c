/* rgp:protos */
#define RGP_SELF_MesWinHasCloseMark_2715f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

s32 MesWinHasCloseMark_2715f0(s32 arg0) {
    s32 limit;
    s32 i;

    limit = MesWinGetShownEnd_271680((void *)arg0) - 1;
    i = MesWinGetShownStart_2716a0(arg0);
    while (limit >= i) {
        if ((((unsigned short)MesWinGetCharCode_274dd0(arg0, i)) & 0xFFFF) == 0xFF07) {
            return 1;
        }
        i += 1;
    }
    return 0;
}
