/* rgp:protos */
#define RGP_SELF_factory_FactorySlotRoutesReachMachine_4ffd00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Ent {
    u8  pad00[0x4];
    s16 f04;
    u8  pad06[0x4];
    s16 f0A;
    s16 f0C;
    u8  pad0E[0x32];
} Ent;                                          /* 0x40 */

typedef struct Out {
    s16 f00;
    s16 f02;
    s16 f04;
} Out;

typedef struct Ctx {
    u8   pad00[0xD4];
    void *fD4;
    u8   padD8[0x8];
    Ent  fE0[4];
} Ctx;

/*rgp*/
/*rgp*/

s32 factory_FactorySlotRoutesReachMachine_4ffd00(Ctx *c)
{
    Out  t __attribute__((aligned(16)));
    Ent *e;
    s32  i;

    if (c->fD4 == 0) {
        return 0;
    }
    e = c->fE0;
    for (i = 0; i < 4; i++, e++) {
        if (e->f04 >= 0) {
            if (factory_FactoryRouteStart_4fff20(c, &t, e->f0A, e->f0C) == 0) {
                return 0;
            }
            do {
                if (factory_FactoryRouteStep_4ffdc0(c, &t, &t) == 0) {
                    return 0;
                }
            } while (t.f00 != 0xE);
        }
    }
    return 1;
}
