/* rgp:protos */
#define RGP_SELF_factory_FactoryPartsAllRunning_4ffc80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Item {
    u8  pad00[0x25];
    s8  f25;
    u8  pad26[0x1A];
} Item;                                         /* 0x40 */

typedef struct Ent {
    u8    pad00[0x8];
    u16   f08;
    u8    pad0A[0x2];
    s16   f0C;
    u8    pad0E[0x2];
    Item *f10;
    u8    pad14[0x54];
} Ent;                                          /* 0x68 */

typedef struct Ctx {
    u8   pad00[0xD4];
    Ent *fD4;
    s32  fD8;
} Ctx;

s32 factory_FactoryPartsAllRunning_4ffc80(Ctx *c)
{
    Ent  *e;
    s32   i;
    Item *it;
    s32   j;
    s32   n;

    e = c->fD4;
    if (e == 0) {
        return 0;
    }
    n = c->fD8;
    for (i = 0; i < n; i++, e++) {
        if ((e->f08 & 0x3C) != 0) {
            it = e->f10;
            for (j = 0; j < e->f0C; j++, it++) {
                if (4 > it->f25) {
                    return 0;
                }
            }
        }
    }
    return 1;
}
