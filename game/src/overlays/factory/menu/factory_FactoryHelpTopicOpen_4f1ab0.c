/* rgp:protos */
#define RGP_SELF_factory_FactoryHelpTopicOpen_4f1ab0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Rec {
    s16 f00;
    s16 f02;
} Rec;

typedef struct Meta {
    u8  pad00[0x16];
    s16 f16;
    u8  pad18[0x2];
    s16 f1A;
} Meta;

typedef struct Scr {
    u8    pad00[0x6A];
    u8    f6A;
    u8    pad6B[0x1];
    s32   f6C;
    s8    f70;
    s8    f71;
    u8    pad72[0x2];
    Rec  *f74;
    s32   f78;
    s32   f7C;
    s32   f80;
    u8    pad84[0x4];
    void *f88;
    void *f8C;
} Scr;

extern void *D_00484A30;                        /* _gp - 0x740 */
extern void *D_00484A70;                        /* _gp - 0x700 */
extern u8    factory_D_0050CB20[];

extern void  Sprintf_1343b8(u8 *dst, u8 *fmt, void *s);
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

void factory_FactoryHelpTopicOpen_4f1ab0(Scr *o)
{
    u8   buf[0x20] __attribute__((aligned(16)));
    u8  *p;
    u8  *q;
    u8  *r;
    Meta *m;
    s32  h;
    u32  n;
    s32  v;

    if (o->f7C == -1) {
        if (D_00484A30 != 0) {
            MemStackReset_14d830(D_00484A30);
        }
        NameTableFreeGroup_158ac0(GetDrawCtxNameTable_15de40(), 0x32E);
        h = ((s32)GetLoaderMgr_1f59d0());
        o->f7C = -1;
        o->f80 = 0;
        m = ((Meta *)UiEntryListFindByTag_28ea40(o->f8C, 0x8944));
        v = m->f16 + m->f1A;
        if (o->f6A == 0 && v >= 0xB) {
            v = v + 1;
        }
        o->f6C = v;
        q = MsgTableLookup_28aa30(D_00484A70, o->f74[v].f00 + 0x2710);
        p = ((u8 *)Strchr_1347c0(q, 0xA));
        *p = 0;
        r = buf;
        n = 0x20;
        if (r != 0) {
            do {
                *r = 0;
                n--;
                r++;
            } while (n != 0);
        }
        Sprintf_1343b8(buf, factory_D_0050CB20, q);
        *p = 0xA;
        o->f7C = LoaderRequestFile_1cd870(h, buf, 0);
        if (o->f7C != -1) {
            o->f78 = 0;
            o->f71 = 0;
            LoaderQueueAppendSeparator_1cd670(h);
            UiFadeWidgetAlpha_290690(o->f88, 0x7C, 0.0f, -0.125f, -1.0f);
            UiEntryListSelectByTag_28ea90(o->f8C, 0x894E, 0);
            o->f70 = 2;
        }
    }
}
