/* rgp:protos */
#define RGP_SELF_normal_MenuBattleEndLevelUpGlowUpdate_4ea0f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004EA0F0 -- per-entity ramp update over p->f008 entries.
 * 12-byte items at 0x30, s8 gate array at 0xF9. */

typedef struct Ea0Item {    /* 0xC */
    f32 f00;
    f32 f04;
    s16 f08;
    s16 f0A;
} Ea0Item;

typedef struct Ea0Obj {
    u8      pad000[8];
    s32     f008;
    u8      pad00C[0x30 - 0xC];
    Ea0Item f030[16];
    u8      pad0F0[0xF9 - 0xF0];
    s8      f0F9[16];
} Ea0Obj;

void normal_MenuBattleEndLevelUpGlowUpdate_4ea0f0(Ea0Obj *p)
{
    f32 *q;
    f32 *r;
    s32 i;

    for (i = 0; i < p->f008; i++) {
        if (p->f0F9[i] < 2) {
            continue;
        }
        q = &p->f030[i].f04;
        r = &p->f030[i].f00;
        *r = *r + *q;
        if (*r > 48.0f) {
            *q = 2.0f;
            *q = *q * -1.0f;
            *r = 48.0f;
        } else if (*r <= 0.0f) {
            *r = 0.0f;
            p->f030[i].f08 = 2;
        }
    }
}
