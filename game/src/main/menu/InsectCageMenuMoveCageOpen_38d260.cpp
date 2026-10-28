/* rgp:protos */
#line 1
#include "types.h"

typedef struct BufA {
    u8 pad0[0x1C];
    s32 unk1C;
    u8 pad20[0xB0 - 0x20];
} BufA;

typedef struct BufB {
    u8 pad0[0x12];
    s16 unk12;
    u8 pad14[0x20 - 0x14];
} BufB;

typedef struct Obj004E94E0 {
    u8 pad0[0x10];
    s16 unk10;
} Obj004E94E0;

class V0038d260 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f118(s32 a0) { return VCM(s32, (void *, s32), 0x118, a0); }
};

extern "C" {
void MsgFormat_28a9a0(s32, s32, BufA *, s32);
void MsgFormatParamsCtor_28aa00(BufA *);
Obj004E94E0 *UiEntryListFindDataByTag_28ec30(Obj004E94E0 *, s32);
void UiSetWidgetVisible_290010(s32, s32, s32, s32);
void UiFitCenterWindow_388270(s32, s32);
void InsectCageMenuSetCursorTarget_389790(s32, void *, s32);
void InsectCageMenuSetRowMarker_389a80(s32, s32, s32, s32);
void InsectCageMenuSetCursorVisible_389d00(s32);
s32 InsectCageMenuMsgLookup_389d30(s32);
V0038d260 *InsectCageMenuGetCursorInsect_38d510();
void InsectCageMenuSlotTextSetStateMaybe_38d550(s32, s32);
void InsectCageMenuRefreshInsectNames_38d5f0();
s32 InsectCageGetType_3910c0();
}
extern "C" s32 D_00483304;
extern "C" s16 D_00483334;
extern "C" Obj004E94E0 D_004E94E0;

extern "C" s32 InsectCageMenuMoveCageOpen_38d260(void *arg0, s32 arg1)
{
    BufB b __attribute__((aligned(16)));
    BufA a __attribute__((aligned(16)));
    s32 i;

    UiSetWidgetVisible_290010(arg1, 0x7576, 1, -1);
    InsectCageMenuRefreshInsectNames_38d5f0();
    D_00483334 = 2;
    b.unk12 = UiEntryListFindDataByTag_28ec30(&D_004E94E0, 0x7531)->unk10;
    InsectCageMenuSetCursorTarget_389790(2, &b, 1);
    InsectCageMenuSlotTextSetStateMaybe_38d550(((signed char)InsectCageGetType_3910c0()), 0);
    for (i = 0; i < 3; i++) {
        InsectCageMenuSlotTextSetStateMaybe_38d550(i, i != ((signed char)InsectCageGetType_3910c0()));
    }
    for (i = 0; i < 3; i++) {
        InsectCageMenuSetRowMarker_389a80(1, 0, i, -1);
    }
    UiSetWidgetVisible_290010(arg1, 0x754E, 1, -1);
    MsgFormatParamsCtor_28aa00(&a);
    a.unk1C = InsectCageMenuGetCursorInsect_38d510()->f118(0);
    MsgFormat_28a9a0(D_00483304 + 0x200, InsectCageMenuMsgLookup_389d30(0x515), &a, 1);
    UiFitCenterWindow_388270(0x754E, 0);
    InsectCageMenuSetCursorVisible_389d00(1);
    InsectCageMenuSetCursorTarget_389790(1, arg0, 1);
    return 1;
}
