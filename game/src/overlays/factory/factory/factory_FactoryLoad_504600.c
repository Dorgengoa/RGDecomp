/* rgp:protos */
#define RGP_SELF_factory_FactoryLoad_504600 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Anim {
    s16 f00;
    s16 f02;
    u8  pad04[0x8];
} Anim;

typedef struct Scr {
    u8   pad00[0x20];
    Anim f20[4];
    s32  f50;
    u8   pad54[0x14];
    u8   f68[0x4];
} Scr;

extern u8 factory_D_0050CE58[];
extern u8 factory_D_0050CE68[];
extern u8 factory_D_0050CE78[];
extern u8 factory_D_0050CE88[];
extern u8 factory_D_0050CE90[];
extern u8 factory_D_0050CE98[];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void factory_FactoryLoad_504600(Scr *o)
{
    s32 i;

    if (o->f50 == 1) {
        return;
    }
    if (o->f50 == 2) {
        return;
    }
    if (o->f50 == 3) {
        LoadHandleRequestFile_1ccbb0(&o->f20[0], factory_D_0050CE58);
        LoadHandleRequestFile_1ccbb0(&o->f20[1], factory_D_0050CE68);
        LoadHandleRequestFile_1ccbb0(&o->f20[2], factory_D_0050CE78);
        o->f50 = 4;
        return;
    }
    for (i = 0; i < 4; i++) {
        LoadHandlePoll_1ccb00(&o->f20[i]);
    }
    switch (o->f50) {
    case 4:
        if (o->f20[0].f02 == 0) {
            return;
        }
        if (o->f20[0].f02 == 1 && factory_FactoryCursorModelLoad_504250(o, 0, 0, 0x2A4, factory_D_0050CE88, o->f68) != 0) {
            o->f50 = 5;
        } else {
            o->f50 = 1;
        }
        break;
    case 5:
        if (o->f20[1].f02 == 0) {
            return;
        }
        if (o->f20[1].f02 == 1 && factory_FactoryCursorModelLoad_504250(o, 1, 1, 0x2A4, factory_D_0050CE90, o->f68) != 0) {
            o->f50 = 6;
        } else {
            o->f50 = 1;
        }
        break;
    case 6:
        if (o->f20[2].f02 == 0) {
            return;
        }
        if (o->f20[2].f02 == 1 && factory_FactoryCursorModelLoad_504250(o, 2, 2, 0x2A4, factory_D_0050CE98, o->f68) != 0) {
            o->f50 = 7;
        } else {
            o->f50 = 1;
        }
        break;
    case 7:
        o->f50 = 2;
        break;
    }
    switch (o->f50) {
    case 2:
    case 1:
        for (i = 0; i < 4; i++) {
            LoaderReleaseHandle_1ccb70(&o->f20[i]);
        }
        break;
    }
}
