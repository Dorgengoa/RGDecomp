/* rgp:protos */
#define RGP_SELF_GoTitleMenuInit_39bfe0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Info {
    s32 f0;
    s32 f4;
    u16 f8;
    __extension__ unsigned short fa_0 : 2;
    unsigned short fa_2 : 14;
} __attribute__((aligned(2))) Info;

typedef struct Flags {
    u8 b0 : 1;
    u8 b1 : 7;
    u8 pad[15];
} Flags;

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
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_0048360C;
extern s16 D_00483610;
extern s32 D_00483614;
extern s32 D_00483618;
extern s8 D_00483624;
extern s16 D_00483628;
extern s8 D_0048363C;
extern s32 D_00483640;
extern u8 D_004E9660[0x20];
extern s32 D_004E9668[4];
extern u8 D_004E9680[0x18];
extern s32 D_004E9698[4];
extern Flags D_004E96A0;
extern u8 D_004E96A1[16];

void GoTitleMenuInit_39bfe0(void)
{
    s32 h;
    Info *p;
    s32 a;
    s32 b;

    D_00483640 = 0;
    D_0048360C = ((s32)GetMenuGoTitleStack_206a70());
    MemStackReset_14d830(D_0048360C);
    h = ((s32)GetMenuResGroup_206a40());
    p = ((Info *)ResGroupListFindById_42c500(h, 0x18));
    a = p->f4;
    b = p->fa_2;
    UiWidgetListReset_2912e0(D_004E9660);
    UiInitWidgetPool_290390(D_004E9660, D_0048360C, b);
    UiAddWidgets_2901d0(D_004E9660, a, 0);
    D_004E9668[0] = 0x32B;
    UiTextStyleReset_290450();
    p = ((Info *)ResGroupListFindById_42c040(h, 1));
    a = p->f4;
    b = p->fa_2;
    UiEntryListReset_28ec80(D_004E9680);
    UiEntryListAlloc_28e0c0(D_004E9680, D_0048360C, b);
    UiEntryListLoad_28eb70(D_004E9680, a, D_004E9660);
    D_004E9698[0] = SceneSoundGetSlot0HandleCur_207df0();
    D_004E96A0.b0 = 0;
    D_00483614 = 0;
    D_00483618 = 0;
    D_004E96A1[0] = 0;
    D_00483610 = 0;
    D_00483618 = MenuStateTableForId_42c950(h, 1);
    D_0048363C = 1;
    D_00483628 = 1;
    D_00483624 = 1;
}
