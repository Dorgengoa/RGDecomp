/* rgp:protos */
#define RGP_SELF_MesWinFindPageStart_270840 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s32 MesWinFindPageStart_270840(s32 arg0, s32 arg1) {
    s32 count;
    s32 i;

    if (arg1 < 0) {
        return -1;
    }
    if (arg1 == 0) {
        return 0;
    }
    count = 0;
    for (i = 0; i < 0x300; i++) {
        if ((((unsigned short)MesWinGetCharCode_274dd0(arg0, i)) & 0xFFFF) == 0xFF01) {
            return -1;
        }
        if ((((unsigned short)MesWinGetCharCode_274dd0(arg0, i)) & 0xFFFF) == 0xFF03) {
            count += 1;
            if (count == arg1) {
                return i + 1;
            }
        }
    }
    return -1;
}
