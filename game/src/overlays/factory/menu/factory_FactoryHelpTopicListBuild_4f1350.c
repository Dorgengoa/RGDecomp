/* rgp:protos */
#define RGP_SELF_factory_FactoryHelpTopicListBuild_4f1350 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Ent {
    s16 f00;
} Ent;

typedef struct Rec {
    u8  pad00[0x4];
    Ent *f04;
    u8  pad08[0xC];
    u8  b0 : 1;
    u8  b1 : 1;
} Rec;

typedef struct Hdr {
    u8  pad00[0x12];
    s16 f12;
} Hdr;

typedef union F84 {
    s32 i;
    f32 f;
} F84;

typedef struct Obj {
    u8    pad00[0x6A];
    u8    f6A;
    u8    pad6B[0x19];
    F84   f84;
    void *f88;
    void *f8C;
} Obj;

typedef struct Iter { u8 pad[0x8]; } Iter;

typedef struct World {
    u8    pad00[0x8];
    void *f08;
} World;

typedef struct Zone {
    u8    pad00[0xA4];
    void *fA4;
} Zone;

typedef struct Area {
    u8  pad00[0xC];
    s32 f0C;
} Area;

extern void *D_00484A70;                        /* _gp - 0x700  */
extern u8    D_00480830[1];                     /* _gp - 0x4940 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void factory_FactoryHelpTopicListBuild_4f1350(Obj *o)
{
    Iter it __attribute__((aligned(16)));
    Rec *p;
    Rec *e;
    s32  i;
    s32  n;
    s32  key;
    World *w;
    Hdr *h;

    UiSetTextString_28f510(o->f88, 0x80, MsgTableLookup_28aa30(D_00484A70, 0x11), 0);
    for (i = 0; i < 9; i++) {
        UiSetTextString_28f510(o->f88, 0x80, MsgTableLookup_28aa30(D_00484A70, D_00480830[i] + 0x9C40), i + 1);
    }
    w = ((World *)GetGameData_1fede0());
    key = ((Area *)((Zone *)w->f08)->fA4)->f0C;
    if (key != 0) {
        key = key + 0x88;
    }
    IterInit_370170(&it, key, 0, 0);
    e = 0;
    while ((p = ((Rec *)IterNext_370040(&it))) != 0) {
        if (p->f04->f00 == 0x418F) {
            e = p;
            break;
        }
    }
    if (e != 0) {
        n = 0xF;
        if (e->b0 != 0) {
            if (e->b1 != 0) {
                n = 0x10;
                o->f6A = 1;
            }
        }
        o->f84.i = 0;
        o->f84.f = UiPageScrollBarLayout_289710(o, 0x81, 0xED, 9, n, 0);
        UiSetSpriteUv_28f970(o->f88, 0x81, 0x76, 0x56, 0);
        UiSetSpriteUv_28f970(o->f88, 0x81, 0x76, 0x5C, 1);
        UiSetSpriteUv_28f970(o->f88, 0x81, 0x76, 0x64, 2);
        UiSetWidgetPos_290f60(o->f88, 0x81, 0x16C, 0x42);
        h = ((Hdr *)UiEntryListFindByTag_28ea40(o->f8C, 0x8944));
        h->f12 = n - 1;
    }
}
