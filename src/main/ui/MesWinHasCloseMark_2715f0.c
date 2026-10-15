#include "types.h"

extern s32 MesWinGetShownEnd_271680(void);
extern s32 MesWinGetShownStart_2716a0(s32);
extern s32 MesWinGetCharCode_274dd0(s32, s32);

s32 MesWinHasCloseMark_2715f0(s32 arg0) {
    s32 limit;
    s32 i;

    limit = MesWinGetShownEnd_271680() - 1;
    i = MesWinGetShownStart_2716a0(arg0);
    while (limit >= i) {
        if ((MesWinGetCharCode_274dd0(arg0, i) & 0xFFFF) == 0xFF07) {
            return 1;
        }
        i += 1;
    }
    return 0;
}
