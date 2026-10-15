#include "types.h"

extern s32 CharaCollIgnoreTimerDone_2384f0(void *);

struct Obj0 {
    u8 pad000[0xA32];
    s16 mA32;
    s16 mA34;
    u8 padA36[0xE];
    s32 mA44;
};

s32 CharaIsMagnetPullableMaybe_210440(struct Obj0 *p0)
{
    s32 r;
    s16 a;

    if (CharaCollIgnoreTimerDone_2384f0(p0) == 0) {
        return 0;
    }
    if ((p0->mA44 & 0x80000) != 0) {
        return 0;
    }
    a = p0->mA32;
    if (a != 0x10) {
        if (a != 4) {
            r = 1;
        } else {
            r = p0->mA34 != 0;
        }
    } else {
        r = p0->mA34 == 3;
    }
    return r;
}
