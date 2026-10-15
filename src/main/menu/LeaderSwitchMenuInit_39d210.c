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
extern s32 GetMenuEasyStack_206a80(void);
extern s32 SceneSoundGetSlot0HandleCur_207df0(void);
extern s32 MsgTableLookup_28aa30(s32, s32);
extern void UiEntryListAlloc_28e0c0(void *, s32, s32);
extern void UiEntryListLoad_28eb70(void *, s32, void *);
extern void UiEntryListReset_28ec80(void *);
extern void UiSetTextString_28f510(void *, s32, s32, s32);
extern void UiAddWidgets_2901d0(void *, s32, s32, s32);
extern void UiInitWidgetPool_290390(void *, s32, s32);
extern void UiTextStyleReset_290450(void *);
extern void UiWidgetListReset_2912e0(void *);
extern Info *ResGroupListFindById_42c040(s32, s32);
extern Info *ResGroupListFindById_42c500(s32, s32);
extern s32 MenuStateTableForId_42c950(s32, s32);
extern s32 D_00481BBC;
extern s32 D_004835F8;
extern s16 D_00483600;
extern s32 D_00483604;
extern s32 D_00483608;
extern s8 D_0048361C;
extern s16 D_00483620;
extern s32 D_00483630;
extern s32 D_00483634;
extern s8 D_00483638;
extern u8 D_004E9610[0x20];
extern s32 D_004E9618[4];
extern u8 D_004E9630[0x18];
extern s32 D_004E9648[4];
extern Flags D_004E9650;
extern u8 D_004E9651[16];

void LeaderSwitchMenuInit_39d210(void)
{
    s32 h;
    Info *p;
    s32 a;
    s32 b;

    D_004835F8 = GetMenuEasyStack_206a80();
    MemStackReset_14d830(D_004835F8);
    h = GetMenuResGroup_206a40();
    p = ResGroupListFindById_42c500(h, 1);
    a = p->f4;
    b = p->fa_2;
    UiWidgetListReset_2912e0(D_004E9610);
    UiInitWidgetPool_290390(D_004E9610, D_004835F8, b);
    UiAddWidgets_2901d0(D_004E9610, a, 0, 0);
    D_004E9618[0] = 0x32B;
    UiTextStyleReset_290450(D_004E9610);
    p = ResGroupListFindById_42c040(h, 1);
    a = p->f4;
    b = p->fa_2;
    UiEntryListReset_28ec80(D_004E9630);
    UiEntryListAlloc_28e0c0(D_004E9630, D_004835F8, b);
    UiEntryListLoad_28eb70(D_004E9630, a, D_004E9610);
    D_004E9648[0] = SceneSoundGetSlot0HandleCur_207df0();
    D_004E9650.b0 = 0;
    D_00483604 = 0;
    D_00483608 = 0;
    D_004E9651[0] = 0;
    D_00483600 = 0;
    D_00483608 = MenuStateTableForId_42c950(h, 1);
    UiSetTextString_28f510(D_004E9610, 3, MsgTableLookup_28aa30(D_00481BBC, 0x46), 0);
    UiSetTextString_28f510(D_004E9610, 5, MsgTableLookup_28aa30(D_00481BBC, 0x47), 0);
    UiSetTextString_28f510(D_004E9610, 6, MsgTableLookup_28aa30(D_00481BBC, 0x48), 0);
    D_00483638 = 1;
    D_00483634 = -1;
    D_00483620 = 1;
    D_0048361C = 1;
    D_00483630 = 1;
}
