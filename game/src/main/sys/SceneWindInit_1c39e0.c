/* rgp:protos */
#define RGP_SELF_SceneWindInit_1c39e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef rg_u128 u128;
typedef struct P1C39E0 { f32 m00; u8 pad004[0xC]; u128 m10; } P1C39E0;
void SceneWindInit_1c39e0(P1C39E0 *p)
{
    p->m00 = 1.0f;
    p->m10 = 0;
    *(f32 *)((u8 *)p + 0x18) = 1.0f;
}
