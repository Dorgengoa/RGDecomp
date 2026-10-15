#include "types.h"

typedef struct Info {
    s32 f0;
    s32 f4;
    u16 f8;
    u16 fa_0 : 2;
    u16 fa_2 : 14;
} Info;

typedef struct Flags {
    u8 b0 : 1;
    u8 b1 : 7;
    u8 pad[15];
} Flags;

extern void MemStackReset_14d830(s32);
extern s32 GetMenuResGroup_206a40(void);
extern s32 GetMenuGoTitleStack_206a70(void);
extern s32 SceneSoundGetSlot0HandleCur_207df0(void);
extern void UiEntryListAlloc_28e0c0(void *, s32, s32);
extern void UiEntryListLoad_28eb70(void *, s32, void *);
extern void UiEntryListReset_28ec80(void *);
extern void UiAddWidgets_2901d0(void *, s32, s32, s32);
extern void UiInitWidgetPool_290390(void *, s32, s32);
extern void UiTextStyleReset_290450(void *);
extern void UiWidgetListReset_2912e0(void *);
extern Info *ResGroupListFindById_42c040(s32, s32);
extern Info *ResGroupListFindById_42c500(s32, s32);
extern s32 MenuStateTableForId_42c950(s32, s32);
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
    D_0048360C = GetMenuGoTitleStack_206a70();
    MemStackReset_14d830(D_0048360C);
    h = GetMenuResGroup_206a40();
    p = ResGroupListFindById_42c500(h, 0x18);
    a = p->f4;
    b = p->fa_2;
    UiWidgetListReset_2912e0(D_004E9660);
    UiInitWidgetPool_290390(D_004E9660, D_0048360C, b);
    UiAddWidgets_2901d0(D_004E9660, a, 0, 0);
    D_004E9668[0] = 0x32B;
    UiTextStyleReset_290450(D_004E9660);
    p = ResGroupListFindById_42c040(h, 1);
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
