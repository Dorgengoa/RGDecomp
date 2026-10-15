#include "types.h"

extern s32 MesWinGetMsgTable_274670(s32);
extern s32 MesWinGetMsgCount_274690(void);

s32 MesWinLookupMsg_2745f0(s32 arg0, s32 arg1)
{
    s32 count;
    s32 base;
    s32 i;
    s32 elem;

    count = MesWinGetMsgCount_274690();
    base = MesWinGetMsgTable_274670(arg0);
    i = 0;
    while (i < count) {
        elem = base + i * 4;
        if (arg1 == *(u16 *)(elem + 2)) {
            return base + count * 2 + *(u16 *)(elem + 4) * 2;
        }
        i++;
    }
    return 0;
}
