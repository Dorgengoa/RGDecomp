/* rgp:protos */
#define RGP_SELF_InsectMenuScreenInit_398210 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[4];
    s32 unk4;
    u8 pad8[2];
    __extension__ unsigned short lo : 2;
    unsigned short val : 14;
} __attribute__((aligned(2))) Item;

typedef struct {
    u8 b0 : 1;
    u8 b1 : 7;
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
extern s32 D_004834E8;
extern u8 D_004E95C0[];
extern s32 D_004E95C8[];
extern u8 D_004E95E0[];
extern s32 D_004E95F8[];
extern Flags D_004E9600[];
extern u8 D_004E9601[];

void InsectMenuScreenInit_398210(s32 arg0)
{
    s32 h;
    Item *it;
    Item *it2;

    h = ((s32)GetMenuResGroup_206a40());
    ResGroupLoadByKind_42b840(h, 2, 0xC, D_004834E8, arg0);
    it = ((Item *)ResGroupListFindById_42c500(h, 0xB));
    UiWidgetListReset_2912e0(D_004E95C0);
    if (it != NULL) {
        UiInitWidgetPool_290390(D_004E95C0, D_004834E8, it->val);
        UiAddWidgets_2901d0(D_004E95C0, it->unk4, 0);
    }
    D_004E95C8[0] = 0x32D;
    UiTextStyleReset_290450();
    it2 = ((Item *)ResGroupListFindById_42c040(h, 8));
    UiEntryListReset_28ec80(D_004E95E0);
    if (it2 != NULL) {
        UiEntryListAlloc_28e0c0(D_004E95E0, D_004834E8, it2->val);
        UiEntryListLoad_28eb70(D_004E95E0, it2->unk4, D_004E95C0);
    }
    D_004E95F8[0] = SceneSoundGetSlot0HandleCur_207df0();
    D_004E9600[0].b0 = 0;
    D_004E9601[0] = 0;
}
