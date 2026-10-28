/* rgp:protos */
#define RGP_SELF_factory_FactoryBlueprintSelChanged_4fb3d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Sub {
    u8  pad00[0x10];
    s16 f10;
    u8  pad12[0x4];
    s16 f16;
} Sub;

typedef struct Hdr {
    u8  pad00[0x4];
    Sub f04;
} Hdr;

typedef struct Ent {
    s16 f00;
    u8  pad02[0x16];
    s16 f18;
} Ent;

typedef struct Scr {
    u8    pad00[0x5C];
    s16   f5C;
    u8    pad5E[0x2];
    s16   f60;
    s16   f62;
    u8    pad64[0x4];
    f32   f68;
    u8    pad6C[0x10];
    u8    f7C;
    u8    pad7D[0x3];
    void *f80;
    void *f84;
} Scr;

extern void *D_004807E8;                        /* _gp - 0x4988 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void factory_FactoryBlueprintSelChanged_4fb3d0(Scr *o)
{
    Hdr *h;
    Sub *m;
    Ent *e;

    switch (o->f7C) {
    case 0:
        h = ((Hdr *)UiEntryListFindByTag_28ea40(o->f84, 0x88CC));
        m = &h->f04;
        if (m->f16 != o->f62) {
            factory_FactoryBlueprintGridRefresh_4f9ac0(o);
            o->f62 = m->f16;
            UiMoveWidgetUniform_290f50(o->f80, 0x21, 0x170, (s32)(m->f16 * o->f68 + 32.0f), 0.25f, 0);
        }
        factory_FactoryBlueprintShowName_4f9db0(o);
        break;
    case 1:
        h = ((Hdr *)UiEntryListFindByTag_28ea40(o->f84, 0x88D6));
        m = &h->f04;
        e = ((Ent *)UiGetWidgetSprite_28fe10(o->f80, 0x3D, 3));
        UiSetSpriteX_28fcd0(o->f80, 0x3D, e->f00 + 2 + m->f10 * e->f18, 6);
        o->f60 = m->f10;
        break;
    case 3:
    case 4:
    case 6:
    case 9:
        h = ((Hdr *)UiEntryListFindByTag_28ea40(o->f84, 0x88EA));
        m = &h->f04;
        e = ((Ent *)UiGetWidgetSprite_28fe10(D_004807E8, 0x95, 0));
        if (m->f10 == 0) {
            UiSetSpriteX_28fcd0(D_004807E8, 0x95, e->f00 + 2, 3);
        } else {
            UiSetSpriteX_28fcd0(D_004807E8, 0x95, e->f00 + 2 + e->f18, 3);
        }
        o->f5C = m->f10;
        break;
    }
}
