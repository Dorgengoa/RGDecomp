/* rgp:protos */
#define RGP_SELF_factory_FactoryBuildModels_503d30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct A { u8 pad00[0x14]; } A;
typedef struct B { u8 pad00[0x68]; } B;

typedef struct Ctx {
    u8  pad00[0xCC];
    A  *fCC;
    s32 fD0;
    B  *fD4;
    s32 fD8;
} Ctx;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void factory_FactoryBuildModels_503d30(Ctx *c)
{
    void *p;
    void *t;
    void *q;
    void *w;
    A    *a;
    s32   i;
    B    *b;
    s32   j;

    EffectMgrUnlinkActive_2e1550(GetEffectMgr_2d9040());
    q = GetMapMgr_201a90();
    p = 0;
    t = MapSlotsFindBlockById_1e49b0(q, 0x2EE0, 0);
    if (t != 0) {
        p = MapDataGetModel_1e7810(t);
    }
    if (p != 0) {
        MapAreaModelNopRelated_188fe0();
    }
    w = (u8 *)c + 0x304;
    MemStackReset_14d830(w);
    a = c->fCC;
    if (a != 0) {
        for (i = 0; i < c->fD0; i++, a++) {
            factory_FactoryBeltTileGroupBuildObjs_4ff1e0(a, w);
        }
    }
    b = c->fD4;
    if (b != 0) {
        for (j = 0; j < c->fD8; j++, b++) {
            factory_FactoryPartGroupBuildObjs_4fead0(b, w);
        }
    }
    if (p != 0) {
        MapAreaModelBuildBoundsMaybe_188ff0(p, w);
    }
    factory_FactoryFloorClearAll_501150(c);
}
