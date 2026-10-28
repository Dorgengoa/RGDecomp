/* rgp:protos */
#define RGP_SELF_factory_FactoryPartsRefreshIcons_4efc80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Ent { u8 pad00[0x2C]; s16 f2C; } Ent;
typedef struct Meta { u8 pad00[0x16]; s16 f16; u8 pad18[0x2]; s16 f1A; } Meta;
typedef struct Iter { u8 pad00[0x8]; } Iter;

typedef struct Scr {
    u8    pad00[0x74];
    u8    f74[0x14];
    u8    pad88[0x4];
    void *f8C;
    void *f90;
} Scr;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void factory_FactoryPartsRefreshIcons_4efc80(Scr *o, int rgp_a1, int rgp_a2, int rgp_a3)
{
    Iter  cur __attribute__((aligned(16)));
    Meta *m;
    Ent  *e;
    s32   n;
    s32   i;

    IterInit_370170(&cur, o->f74, (int)rgp_a2, (int)rgp_a3);
    UiSetWidgetVisible_290010(o->f8C, 0x44, 0, -1);
    m = ((Meta *)UiEntryListFindByTag_28ea40(o->f90, 0x88F4));
    n = m->f16 + m->f1A;
    if (m->f16 == 3) {
        n -= 3;
    }
    IterSeek_36fff0(&cur, n, 0, 0);
    e = ((Ent *)IterGetCurrent_36ff80(&cur, 0, 0, 0));
    i = 0;
    while (i <= 3 && e != 0) {
        factory_FactoryPartsSetIcon_4efc40(o, e->f2C, i);
        e = ((Ent *)IterNext_370040(&cur));
        i++;
    }
}
