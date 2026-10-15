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
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual void v45();
    virtual void v46();
    virtual void v47();
    virtual void v48();
    virtual void v49();
    virtual void v50();
    virtual void v51();
    virtual void v52();
    virtual void v53();
    virtual void v54();
    virtual void v55();
    virtual void v56();
    virtual void v57();
    virtual void v58();
    virtual void v59();
    virtual void v60();
    virtual void v61();
    virtual void v62();
    virtual void v63();
    virtual void v64();
    virtual void v65();
    virtual void v66();
    virtual void v67();
    virtual s32 f118(s32);
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
extern s32 D_00483304;
extern s16 D_00483334;
extern Obj004E94E0 D_004E94E0;

extern "C" s32 InsectCageMenuMoveCageOpen_38d260(void *arg0, s32 arg1)
{
    BufB b;
    BufA a;
    s32 i;

    UiSetWidgetVisible_290010(arg1, 0x7576, 1, -1);
    InsectCageMenuRefreshInsectNames_38d5f0();
    D_00483334 = 2;
    b.unk12 = UiEntryListFindDataByTag_28ec30(&D_004E94E0, 0x7531)->unk10;
    InsectCageMenuSetCursorTarget_389790(2, &b, 1);
    InsectCageMenuSlotTextSetStateMaybe_38d550(InsectCageGetType_3910c0(), 0);
    for (i = 0; i < 3; i++) {
        InsectCageMenuSlotTextSetStateMaybe_38d550(i, i != InsectCageGetType_3910c0());
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
