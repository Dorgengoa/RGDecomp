/* rgp:protos */
#define RGP_SELF_GameSceneCameraPop_1ced20 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* the counter is addressed by DISPLACEMENT off $4 in both accesses; a
   `(u8 *)p + 0x5DFC` cast written twice makes mwcc CSE the ADDRESS into a
   register and costs a word. */
typedef struct P1CED20 {
    u8  pad000[0x4344];
    s32 m4344;
    u8  pad4348[0x1AB4];
    s32 m5DFC;
} P1CED20;
void GameSceneCameraPop_1ced20(P1CED20 *p)
{
    s32 n;
    s32 t;

    n = p->m5DFC;
    if (n != 0) {
        n = n - 1;
        p->m5DFC = n;
        t = n * 4;
        p->m4344 = *(s32 *)(t + (s32)p + 0x5DDC);
    }
}
