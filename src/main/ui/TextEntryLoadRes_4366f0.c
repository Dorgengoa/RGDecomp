#include "types.h"

typedef struct Info {
    u8 pad0[4];
    s32 x4;
    u64 lo : 18;
    u64 hi : 14;
    u64 rest : 32;
} Info;

typedef struct Sub {
    u8 pad0[8];
    s32 x8;
    u8 padC[0xC];
    s32 x18;
    u8 pad1C[4];
    u8 f0 : 1;
    u8 fr : 7;
    u8 x21;
} Sub;

typedef struct Obj {
    Sub *x0;
    Sub *x4;
    u8 pad8[4];
    s32 xC;
} Obj;

extern s32 MsgTableLoadFromArchive_202a50(s32, u8 *, s32);
extern void TexGroupLoadFromArchive_202be0(s32, u8 *, s32, s32, s32);
extern s32 GetMenuResGroup_206a40();
extern s32 SceneSoundGetSlot0HandleCur_207df0();
extern void UiEntryListAlloc_28e0c0(Sub *, s32, s32);
extern void UiEntryListLoad_28eb70(Sub *, s32, Sub *);
extern void UiEntryListReset_28ec80(Sub *);
extern void UiAddWidgets_2901d0(Sub *, s32, s32, s32);
extern void UiInitWidgetPool_290390(Sub *, s32, s32);
extern void UiTextStyleReset_290450(Sub *);
extern void UiWidgetListReset_2912e0(Sub *);
extern void ResGroupLoadByKind_42b840(s32, s32, s32, s32, s32);
extern Info *ResGroupListFindById_42c040(s32, s32);
extern Info *ResGroupListFindById_42c500(s32, s32);
extern u8 D_00469120[0x20];
extern u8 D_00469140[0x400];

void TextEntryLoadRes_4366f0(Obj *arg0, s32 arg1, s32 arg2)
{
    s32 id;
    Info *a;
    Info *b;
    Sub *s;

    id = GetMenuResGroup_206a40();
    ResGroupLoadByKind_42b840(id, 3, 0xE, arg1, arg2);
    TexGroupLoadFromArchive_202be0(arg2, D_00469120, arg1, 0x32D, 0);
    arg0->xC = MsgTableLoadFromArchive_202a50(arg2, D_00469140, arg1);
    a = ResGroupListFindById_42c500(id, 0x30);
    UiWidgetListReset_2912e0(arg0->x0);
    if (a != 0) {
        UiInitWidgetPool_290390(arg0->x0, arg1, a->hi);
        UiAddWidgets_2901d0(arg0->x0, a->x4, 0, 0);
    }
    arg0->x0->x8 = 0x32D;
    UiTextStyleReset_290450(arg0->x0);
    b = ResGroupListFindById_42c040(id, 0x20);
    UiEntryListReset_28ec80(arg0->x4);
    if (b != 0) {
        UiEntryListAlloc_28e0c0(arg0->x4, arg1, b->hi);
        UiEntryListLoad_28eb70(arg0->x4, b->x4, arg0->x0);
    }
    id = SceneSoundGetSlot0HandleCur_207df0();
    s = arg0->x4;
    s->x18 = id;
    s->f0 = 0;
    s->x21 = 0;
}
