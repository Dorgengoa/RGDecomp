#include "types.h"

struct T1CE8F0 { u8 pad000[0xB560]; u8 fB560; u8 fB561; u8 fB562; u8 fB563; };

extern void ScreenColorFilterMaybe_179c60(u8 a, u8 b, u8 c);

void GameSceneTintApply_1ce8f0(struct T1CE8F0 *p)
{
    if (p->fB560 == 0) return;
    ScreenColorFilterMaybe_179c60(p->fB561, p->fB562, p->fB563);
}
