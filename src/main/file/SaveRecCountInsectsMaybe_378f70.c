#include "types.h"

extern s32 GetGameData_1fede0(void);
extern u8 *SlotRecordFindById_3e4e80(s32, s32);

s32 SaveRecCountInsectsMaybe_378f70(s32 p0)
{
    s32 r0;
    u8 *r1;
    s32 total;
    s32 i;
    u8 *e;
    u8 t0;
    u8 t1;

    r0 = GetGameData_1fede0();
    if (r0 == 0) {
        return -1;
    }
    total = 0;
    r1 = SlotRecordFindById_3e4e80(r0, p0);
    if (r1 == 0) {
        return -1;
    }
    i = 0;
    do {
        e = r1 + (i << 1);
        t0 = e[0x348];
        if ((t0 & 1) != 0) {
            t1 = e[0x349];
            total = total + t1;
        }
        i = i + 1;
    } while (i < 3);
    return total;
}
