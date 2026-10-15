#include "types.h"

typedef struct Q { u8 b0 : 1; u8 b1 : 1; u8 b2 : 1; u8 b3 : 1;
                   u8 b4 : 1; u8 b5 : 1; u8 b6 : 1; u8 b7 : 1; } Q;

extern Q *GameRecGetInsectSlot_3ce350(void);

s32 GameRecReleaseInsectSlot_3ce2a0(void)
{
    Q *q = GameRecGetInsectSlot_3ce350();
    if (q == 0) return 0;
    q->b0 = 0;
    q->b1 = 0;
    return 1;
}
