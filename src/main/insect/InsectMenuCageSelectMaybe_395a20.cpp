#include "types.h"

class E395A20 {
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
    virtual s32 f68(s32);
};

extern "C" {
extern u8 *GetGameData_1fede0(void);
extern u8 *GetSelectedInsectEntryMaybe_206ad0(void);
extern void MsgFormat_28a9a0(s32, s32, void *, s32);
extern void MsgFormatParamsCtor_28aa00(void *);
extern void UiLayoutWindowFrame_28b8e0(u8 *, s32, s32, s32);
extern void UiLayoutFrameRectsMaybe_28bbb0(u8 *, s32, s32);
extern void UiWindowFitToText_28d0c0(void *, s32, s32, s32);
extern s32 MenuGridCursorInput_28e170(void *, void *, s32, s32);
extern u8 *UiEntryListFindByTag_28ea40(void *, s32);
extern u8 *UiEntryListGetCurrentData_28ec60(void *);
extern void StateMachineSetState_28ede0(void *, s32, s32);
extern void UiSetTextString_28f510(void *, s32, s32, s32);
extern u8 *UiGetWidgetSprite_28fe10(void *, s32, s32);
extern void UiSetWidgetVisible_290010(void *, s32, s32, s32);
extern void UiSetWidgetColor_2905b0(void *, s32, f32, f32, f32, f32);
extern void UiFadeWidgetAlpha_290690(void *, s32, f32, f32, f32);
extern void UiSetWidgetTextColor_2907d0(void *, s32, s32, s32);
extern void UiSetWidgetPos_290f60(void *, s32, s32, s32);
extern void UiSetWidgetsVisibleById_291110(void *, s32, s32, s32);
extern void UiWindowFitInit_398170(void *, s32);
extern s32 InsectMenuMsgLookup_398200(s32);
extern s32 InvGetCageItem_3c8040(s32, s32);
extern E395A20 *InsectRecSlotGetItem_3cfb30(s32, s32);
extern s32 InsectRecSlotCountItems_3cfb80(s32);
extern void InsectItemCreateFromCageCatch_3cfea0(s32, s32);
extern void CageRecUnplace_3d0a70(s32);
extern f32 D_004504F0[][2];
extern f32 D_004504F4[][2];
extern f32 D_0047D288;
extern f32 D_0047DADC;
extern f32 D_0047DD2C;
extern s32 D_0047FF48;
extern s16 D_0047FF50;
extern u8 D_004834F0;
extern s32 D_0048351C;
extern f32 D_00483520;
extern f32 D_00483524;
extern s32 D_00483530;
extern s8 D_00483540[3][5] __attribute__((section(".sdata")));
extern s32 D_00483560;
extern s32 D_00483564;
extern u8 D_004B2570[];
extern u8 D_004E95C0[];
extern u8 D_004E95E0[];
}

extern "C" s32 InsectMenuCageSelectMaybe_395a20(s32 pad0, s32 arg1) {
    s8 *row;
    s32 b[0x2C];
    s32 a[0x10];
    u8 *d;
    u8 *fp;
    s32 j;
    s32 k;
    s32 i;
    s32 x;
    s32 id0;
    s32 id1;
    s32 id2;
    s32 id3;
    u8 *w;
    s32 m;
    s32 n;
    E395A20 *e;
    s32 r;
    u8 *p;
    s32 kk;
    u8 *q;
    s32 v;

    if (arg1 != 0) {
        d = GetGameData_1fede0();
        if (d == 0) {
            return 0;
        }
        MsgFormatParamsCtor_28aa00(b);
        b[3] = D_0047FF48;
        MsgFormat_28a9a0(D_00483530, InsectMenuMsgLookup_398200(6), b, 1);
        UiSetTextString_28f510(D_004E95C0, 0x7534, D_00483530, 0);
        UiWindowFitInit_398170(a, 0x7534);
        a[6] = 0x58;
        a[5] = 0xC;
        a[10] = 0x200;
        a[7] = 8;
        a[11] = 0x80;
        a[8] = 8;
        a[4] = 0x164;
        *(u16 *)&a[12] |= 8;
        UiWindowFitToText_28d0c0(a, 0, 0, 0);
        UiSetWidgetsVisibleById_291110(D_004E95C0, 0x7534, 1, 1);
        UiSetWidgetVisible_290010(D_004E95C0, 0x7538, 1, -1);
        UiFadeWidgetAlpha_290690(D_004E95C0, 0x7538, 1.0f, 0.1f, 0.0f);
        fp = UiEntryListFindByTag_28ea40(D_004E95E0, 0x7533);
        D_0047FF50 = -1;
        UiSetWidgetPos_290f60(D_004E95C0, 0x7546, *(s16 *)(fp + 4), *(s16 *)(fp + 6));
        for (j = 0; j < 3; j++) {
            for (k = 0; k < 5; k++) {
                D_00483540[j][k] = -1;
            }
        }
        for (i = 0; i < 3; i++) {
            id0 = (u16)(i + 0x753F);
            x = i * 5 * 32;
            UiSetWidgetPos_290f60(D_004E95C0, id0, x + 0x12, 0xD3);
            UiLayoutWindowFrame_28b8e0(UiGetWidgetSprite_28fe10(D_004E95C0, id0, 0), 0xA0, 0x91, 5);
            id1 = (u16)(i + 0x7539);
            UiSetWidgetPos_290f60(D_004E95C0, id1, x + 0x31, 0x73);
            id2 = (u16)(i + 0x753C);
            UiSetWidgetPos_290f60(D_004E95C0, id2, x + 0x2C, 0x6D);
            w = UiGetWidgetSprite_28fe10(D_004E95C0, id2, 0);
            UiLayoutFrameRectsMaybe_28bbb0(w, 0x6E, 0x62);
            id3 = (u16)(i + 0x7542);
            UiSetWidgetPos_290f60(D_004E95C0, id3, x + 0x77, 0xB1);
            UiSetWidgetColor_2905b0(D_004E95C0, id0, 0.6f, 0.6f, 0.6f, 1.0f);
            UiSetWidgetColor_2905b0(D_004E95C0, id1, 0.6f, 0.6f, 0.6f, 1.0f);
            UiSetWidgetColor_2905b0(D_004E95C0, id2, 0.6f, 0.6f, 0.6f, 1.0f);
            UiSetWidgetColor_2905b0(D_004E95C0, id3, 0.6f, 0.6f, 0.6f, 1.0f);
            UiSetWidgetTextColor_2907d0(D_004E95C0, id0, 0xFF202020, 1);
            m = InvGetCageItem_3c8040(*(s32 *)(d + 0x18), i);
            if (m == 0) {
                continue;
            }
            for (k = 0; k < 5; k++) {
                D_00483540[i][k] = 0;
                UiSetTextString_28f510(D_004E95C0, id0, 0, k);
            }
            *(s16 *)(w + 0x8C) = 0;
            *(s16 *)(w + 0x84) = 0;
            n = InsectRecSlotCountItems_3cfb80(m);
            if (n < 5) {
                UiSetWidgetColor_2905b0(D_004E95C0, id0, 1.0f, 1.0f, 1.0f, 1.0f);
                UiSetWidgetColor_2905b0(D_004E95C0, id1, 1.0f, 1.0f, 1.0f, 1.0f);
                UiSetWidgetColor_2905b0(D_004E95C0, id2, 1.0f, 1.0f, 1.0f, 1.0f);
                UiSetWidgetColor_2905b0(D_004E95C0, id3, 1.0f, 1.0f, 1.0f, 1.0f);
                UiSetWidgetTextColor_2907d0(D_004E95C0, id0, 0xFF303030, 1);
            }
            *(s16 *)(fp + 0xC) = i;
            if (D_0047FF50 < 0 && n < 5) {
                D_0047FF50 = InsectRecSlotCountItems_3cfb80(m);
                *(s16 *)(fp + 0x14) = i;
            }
            for (j = 0; j < n; j++) {
                e = InsectRecSlotGetItem_3cfb30(m, j);
                if (e == 0) {
                    continue;
                }
                D_00483540[i][j] = 1;
                UiSetTextString_28f510(D_004E95C0, id0, e->f68(0), j);
            }
        }
        v = 0x78D;
        D_00483520 = (f32)v + D_004504F0[D_00483560][0];
        D_00483524 = 1904.0f + D_004504F4[D_00483560][0];
        D_00483564 = *(s16 *)(fp + 0x14);
    }
    r = MenuGridCursorInput_28e170(D_004E95E0, D_004B2570, 0, 0);
    p = UiEntryListGetCurrentData_28ec60(D_004E95E0);
    if (r == 1) {
        d = GetGameData_1fede0();
        kk = *(s16 *)(p + 0x10);
        D_0048351C = InvGetCageItem_3c8040(*(s32 *)(d + 0x18), kk);
        if (D_0048351C != 0) {
            q = GetSelectedInsectEntryMaybe_206ad0();
            if (q == 0) {
                return 0;
            }
            if (*(s32 *)(q + 4) == 0) {
                return 0;
            }
            CageRecUnplace_3d0a70(*(s32 *)(q + 4));
            InsectItemCreateFromCageCatch_3cfea0(D_0048351C, *(s32 *)(q + 4));
            v = InsectRecSlotGetItem_3cfb30(D_0048351C, D_0047FF50)->f68(0);
            UiSetTextString_28f510(D_004E95C0, (u16)(kk + 0x753F), v, InsectRecSlotCountItems_3cfb80(D_0048351C) - 1);
            StateMachineSetState_28ede0(&D_004834F0, 0x753E, 0);
        }
    } else if (r == 2) {
        UiFadeWidgetAlpha_290690(D_004E95C0, 0x7538, 0.0f, -0.1f, -1.0f);
        StateMachineSetState_28ede0(&D_004834F0, 0x7539, 0);
    }
    return 1;
}
