/* rgp:protos */
#define RGP_SELF_GameSceneTintApply_1ce8f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct T1CE8F0 { u8 pad000[0xB560]; u8 fB560; u8 fB561; u8 fB562; u8 fB563; };

/*rgp*/

void GameSceneTintApply_1ce8f0(struct T1CE8F0 *p)
{
    if (p->fB560 == 0) return;
    ScreenColorFilterMaybe_179c60(p->fB561, p->fB562, p->fB563);
}
