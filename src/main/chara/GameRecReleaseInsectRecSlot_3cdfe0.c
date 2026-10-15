#include "types.h"

typedef struct Q { u8 b0 : 1; u8 b1 : 1; u8 b2 : 1; u8 b3 : 1;
                   u8 b4 : 1; u8 b5 : 1; u8 b6 : 1; u8 b7 : 1; } Q;

extern Q *GameRecGetInsectRecSlot_3ce090(void);

s32 GameRecReleaseInsectRecSlot_3cdfe0(void)
{
    Q *q = GameRecGetInsectRecSlot_3ce090();
    if (q == 0) return 0;
    q->b0 = 0;
    q->b1 = 0;
    return 1;
}
