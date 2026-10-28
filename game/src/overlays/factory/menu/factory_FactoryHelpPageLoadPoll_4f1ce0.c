/* rgp:protos */
#define RGP_SELF_factory_FactoryHelpPageLoadPoll_4f1ce0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Ent {
    s16 f0;
    s16 f2;
} Ent;

typedef struct Ctx {
    u8    pad00[0x68];
    s16   f68;
    u8    pad6A[0x2];
    s32   f6C;
    u8    f70;
    u8    f71;
    u8    pad72[0x2];
    Ent  *f74;
    s32   f78;
    s32   f7C;
    s32   f80;
    u8    pad84[0x4];
    void *f88;
} Ctx;

extern void *D_00484A30;                        /* _gp - 0x740  */
extern void *D_00484A70;                        /* _gp - 0x700  */
extern void *D_004807E8;                        /* _gp - 0x4988 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void  memcpy(void *d, void *s, s32 n);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void factory_FactoryHelpPageLoadPoll_4f1ce0(Ctx *c)
{
    void *h;
    void *s;
    void *d;
    void *p;
    s32   sz;
    s32   r;
    s32   t;

    if (c->f80 != 0) {
        return;
    }
    if (c->f7C == -1) {
        return;
    }
    h = GetLoaderMgr_1f59d0();
    c->f80 = LoaderGetStatus_1cd4f0(h, c->f7C);
    if (c->f80 != 1) {
        return;
    }
    c->f71 = 1;
    MemStackAlign64_14d8e0(D_00484A30);
    d = MemStackPeekQw_14d9d0(D_00484A30, 1);
    s = LoaderGetData_1cd490(h, c->f7C, &sz);
    MemStackAllocAligned64_14da10(D_00484A30, sz / 16 + 1);
    memcpy(d, s, sz);
    NameTableRegisterImArchive_1594d0(GetDrawCtxNameTable_15de40(), d, 0x32E, D_00484A30, 0);
    LoaderReleaseById_1cd340(h, c->f7C);
    c->f7C = -1;
    p = MsgTableLookup_28aa30(D_00484A70, c->f78 + (c->f74[c->f6C].f0 + 0x2710));
    r = ((s32)Strchr_1347c0(p, 0xA));
    t = r + 1;
    if (c->f70 == 2) {
        UiSetWidgetTexName_290ac0(c->f88, 0x84, t);
        UiSetWidgetVisible_290010(c->f88, 0x84, 1, -1);
        UiFadeWidgetAlpha_290690(c->f88, 0x84, 1.0f, 0.125f, -1.0f);
        c->f68 = 0;
        UiSetWidgetVisible_290010(D_004807E8, 0x96, 1, -1);
        UiFadeWidgetAlpha_290690(D_004807E8, 0x96, 1.0f, 0.125f, 0.0f);
        c->f70 = 1;
    } else if (c->f70 == 3) {
        if (c->f78 % 2 == 0) {
            UiSetWidgetTexName_290ac0(c->f88, 0x84, (int)(t));
            UiSetWidgetVisible_290010(c->f88, 0x84, 1, -1);
            UiFadeWidgetAlpha_290690(c->f88, 0x84, 1.0f, 0.125f, -1.0f);
        } else {
            UiSetWidgetTexName_290ac0(c->f88, 0x85, (int)(t));
            UiSetWidgetVisible_290010(c->f88, 0x85, 1, -1);
            UiFadeWidgetAlpha_290690(c->f88, 0x85, 1.0f, 0.125f, -1.0f);
        }
        c->f70 = 1;
    }
}
