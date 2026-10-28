/* rgp:protos */
#define RGP_SELF_factory_FactoryHelpTopicListRefresh_4f1240 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Meta { u8 pad00[0x16]; s16 f16; u8 pad18[0x2]; s16 f1A; } Meta;

typedef struct Scr {
    u8    pad00[0x6A];
    u8    f6A;
    u8    pad6B[0x19];
    f32   f84;
    void *f88;
    void *f8C;
} Scr;

extern void *D_00484A70;
extern u8    D_00480830[8];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void factory_FactoryHelpTopicListRefresh_4f1240(Scr *o)
{
    Meta *m;
    s32   base;
    s32   i;
    s32   k;

    m = ((Meta *)UiEntryListFindByTag_28ea40(o->f8C, 0x8944));
    base = m->f16 + m->f1A;
    if (m->f16 == 8) {
        base -= 8;
    }
    for (i = 0; i < 9; i++) {
        k = base + i;
        if (o->f6A == 0 && k >= 0xB) {
            k = k + 1;
        }
        UiSetTextString_28f510(o->f88, 0x80,
                    MsgTableLookup_28aa30(D_00484A70, D_00480830[k] + 0x9C40), i + 1);
    }
    UiMoveWidgetUniform_290f50(o->f88, 0x81, 0x16C, (s32)(66.0f + (f32)m->f1A * o->f84), 0.25f, 0
);
}
