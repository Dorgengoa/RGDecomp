#include "types.h"

typedef unsigned __int128 u128;

typedef struct {
    f32 x, y, z, w;
} V4_35F470;

typedef struct {
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
} BF35F470;

class C35F470 {
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
    virtual u8 *f26(s16);
};

class G35F470 {
    u8 pad[0xC0];
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
    virtual void f48(f32);
};

extern "C" {
extern s32 Sprintf_1343b8(char *, const char *, ...);
extern void *memset(void *, s32, u32);
extern void VecNormalize_13bd90(void *, void *);
extern void MemStackReset_14d830(s32);
extern void CameraSetLag_177170(G35F470 *, f32, f32);
extern void LoaderQueueAppendSeparator_1cd670(s32);
extern s32 LoaderRequestFile_1cd870(s32, char *, s32);
extern s32 GetLoaderMgr_1f59d0(void);
extern u8 *GetGameData_1fede0(void);
extern u8 *GetWorldDataMgr_1fedf0(void);
extern u8 *UiEntryListFindByTag_28ea40(s32, s32);
extern void StateMachineSetState_28ede0(s32, s32, s32);
extern s32 UiGetWidgetTextWidth_28f400(void *, s32, s32);
extern void UiSetTextString_28f510(void *, s32, u8 *, s32);
extern void UiSetTextX_28f590(void *, s32, s32, s32);
extern void UiSetWidgetSubItemValue_291250(void *, s32, s32, s32);
extern void MenuCatalogSaveTabCursor_35ee20(u8 *, s32);
extern void MenuCatalogTabSetup_360590(u8 *);
extern u8 *IterNext_370040(void *);
extern void IterInit_370170(void *, void *);
extern u8 *InvFindByCategoryIndex_3c86e0(s32, s32, s32, s32, s32, s32);
extern void InvViewCtorFromOwner_3cec70(void *, u8 *, s32, s32, s32, s32);
extern s32 InvIdGetMidIndex_3d52b0(s32);
extern s32 InvIdGetMinorIndex_3d5440(s32);
extern u8 *DataTableFindRowById_3fd770(s32, s32);
extern void MenuResReleaseThunk_299280(u8 *);
extern u8 D_00462C60[];
extern char D_00462CB0[];
extern char D_00462CD0[];
extern char D_00462CF0[];
extern char D_00462D10[];
extern f32 D_0047F860 __attribute__((section(".sdata")));
extern f32 D_0047F870 __attribute__((section(".sdata")));
extern f32 D_0047F864 __attribute__((section(".sdata")));
extern f32 D_0047F868 __attribute__((section(".sdata")));
extern f32 D_0047F86C __attribute__((section(".sdata")));
extern f32 D_0047F874 __attribute__((section(".sdata")));
extern f32 D_0047F878 __attribute__((section(".sdata")));
extern f32 D_0047F87C __attribute__((section(".sdata")));

extern s32 D_00482338;
extern s16 D_004823B0;
extern G35F470 *D_004823D4;
extern u8 D_004DB1D0[];
extern char D_004E8F60[];
}

extern "C" void MenuMobPreviewRequest_35f470(u8 *o) {
    u8 itA8[8];
    u8 itA0[8];
    u8 buf[0x20];
    V4_35F470 v70;
    V4_35F470 v60;
    u8 *d;
    f32 *pf;
    f32 *pa;
    f32 *pb;
    u8 *q;
    s32 id;
    s32 s1;
    s32 s0;
    u8 *e;
    u8 *n;
    u8 *w;
    s32 a;
    s32 b;
    s32 k;
    u8 *r;
    u8 *t;
    s32 h;
    G35F470 *g;

    d = GetGameData_1fede0();
    q = UiEntryListFindByTag_28ea40(*(s32 *)(o + 0x278), 0x24) + 4;
    id = 0;
    if (*(s32 *)(o + 0x284) == 0) {
        UiSetTextString_28f510(D_004DB1D0, 9, D_00462C60, 0);
        UiSetTextString_28f510(D_004DB1D0, 9, D_00462C60, 1);
        UiSetWidgetSubItemValue_291250(D_004DB1D0, 0xA, 0, 0);
        InvViewCtorFromOwner_3cec70(buf, d, 6, -1, -1, -1);
        IterInit_370170(itA8, buf);
        s1 = *(s16 *)(q + 0x10);
        s0 = *(s16 *)(q + 0x12) + *(s16 *)(q + 0x16);
        e = InvFindByCategoryIndex_3c86e0(*(s32 *)(d + 0x18), 6, 0, s1, s0, 0);
        if (e == 0) {
            return;
        }
        if (*(u8 *)(*(u8 **)(d + 0x20) + 0x24C) & 1) {
            D_004823B0 = 0x4E20;
            StateMachineSetState_28ede0(*(s32 *)(o + 0x27C), 4, 1);
            return;
        }
        UiSetTextString_28f510(D_004DB1D0, 9, *(u8 **)(*(u8 **)(e + 0x10) + 0xC), 0);
        UiSetTextString_28f510(D_004DB1D0, 9, *(u8 **)(*(u8 **)(e + 0x10) + 0x30), 1);
        id = *(s16 *)(*(u8 **)(e + 0x10) + 6);
        *(s32 *)(o + 0x240) = id;
        t = DataTableFindRowById_3fd770(*(s32 *)(*(u8 **)(*(u8 **)(d + 0x8) + 0x94) + 0xC), id);
        if (t != 0) {
            UiSetWidgetSubItemValue_291250(D_004DB1D0, 0xA, 0, *(u16 *)(t + 0x10));
        }
        *(u8 *)(o + 0x244) = ((BF35F470 *)(t + 0x1C))->b2;
        *(s16 *)(o + 0x246) = -1;
        while ((n = IterNext_370040(itA8)) != 0) {
            a = InvIdGetMinorIndex_3d5440(*(s16 *)(n + 6));
            b = InvIdGetMidIndex_3d52b0(*(s16 *)(n + 6));
            if (s1 == a && s0 == b) {
                break;
            }
        }
        *(s16 *)(o + 0x246) = *(s16 *)(itA8 + 6);
    } else if (*(s32 *)(o + 0x284) == 1) {
        UiSetTextString_28f510(D_004DB1D0, 8, D_00462C60, 0);
        w = *(u8 **)(*(u8 **)(*(u8 **)(d + 0x8) + 0x94) + 0xC);
        if (w != 0) {
            w += 0x88;
        }
        IterInit_370170(itA0, w);
        s0 = *(s16 *)(q + 0x12) + *(s16 *)(q + 0x16);
        n = 0;
        s1 = -1;
        while (s1 < s0) {
            n = IterNext_370040(itA0);
            if (n == 0) {
                return;
            }
            if (!(*(u8 *)(n + 0x1C) & 1)) {
                s1++;
            }
        }
        if (!((BF35F470 *)(n + 0x1C))->b1) {
            return;
        }
        if (*(u8 *)(*(u8 **)(d + 0x20) + 0x24C) & 1) {
            D_004823B0 = 0x4E20;
            StateMachineSetState_28ede0(*(s32 *)(o + 0x27C), 4, 1);
            return;
        }
        id = *(s16 *)(n + 8);
        *(s32 *)(o + 0x240) = id;
        *(u8 *)(o + 0x244) = ((BF35F470 *)(n + 0x1C))->b2;
        r = (*(C35F470 **)(*(u8 **)(GetWorldDataMgr_1fedf0() + 0x64) + 0xC))->f26(id);
        if (r != 0) {
            UiSetTextString_28f510(D_004DB1D0, 8, *(u8 **)(r + 4), 0);
            k = UiGetWidgetTextWidth_28f400(D_004DB1D0, 8, 0);
            UiSetTextX_28f590(D_004DB1D0, 8, 0xCD - k / 2, 0);
        }
    }
    MenuResReleaseThunk_299280(o);
    *(u8 *)(o + 0x270) = 1;
    r = *(u8 **)((*(C35F470 **)(*(u8 **)(GetWorldDataMgr_1fedf0() + 0x64) + 0xC))->f26(id) + 0x20);
    memset(D_004E8F60, 0, 0x20);
    if (*(s32 *)(o + 0x240) == 0x2FC9) {
        Sprintf_1343b8(D_004E8F60, D_00462CB0);
    } else if (*(s32 *)(o + 0x240) == 0x2FD8 && *(u8 *)(o + 0x244) == 0) {
        Sprintf_1343b8(D_004E8F60, D_00462CD0);
    } else if (*(s32 *)(o + 0x240) == 0x34B8) {
        Sprintf_1343b8(D_004E8F60, D_00462CF0);
    } else {
        Sprintf_1343b8(D_004E8F60, D_00462D10, *(s32 *)(r + 0xC));
    }
    h = GetLoaderMgr_1f59d0();
    *(s32 *)(o + 0x238) = -1;
    *(s32 *)(o + 0x23C) = 0;
    if (D_004823D4 != 0) {
        pf = (f32 *)&v70;
        pf[0] = D_0047F860;
        pf[1] = D_0047F864;
        pf[2] = D_0047F868;
        pf[3] = D_0047F86C;
        pf = (f32 *)&v60;
        pf[0] = D_0047F870;
        pf[1] = D_0047F874;
        pf[2] = D_0047F878;
        pf[3] = D_0047F87C;
        *(f32 *)(o + 0x25C) = 150.0f;
        if (*(s32 *)(o + 0x240) == 0x2EE1) {
            v60.y = 36.0f;
            v60.z = 572.0f;
            v70.y = 36.0f;
            *(f32 *)(o + 0x25C) = 572.0f;
        }
        *(s32 *)(o + 0x258) = 0;
        VecNormalize_13bd90(o + 0x260, &v60);
        g = D_004823D4;
        *(u128 *)((u8 *)g + 0xE0) = *(u128 *)&v70;
        *(u128 *)((u8 *)g + 0xF0) = *(u128 *)&v60;
        CameraSetLag_177170(g, 1.0f, -1.0f);
        D_004823D4->f48(-1.0f);
    }
    MenuCatalogSaveTabCursor_35ee20(o, *(s32 *)(o + 0x284));
    if (*(s32 *)(o + 0x284) == 0) {
        *(s32 *)(o + 0x284) = 3;
    } else if (*(s32 *)(o + 0x284) == 1) {
        *(s32 *)(o + 0x284) = 4;
    }
    MenuCatalogTabSetup_360590(o);
    MemStackReset_14d830(D_00482338);
    *(s32 *)(o + 0x238) = k = LoaderRequestFile_1cd870(h, D_004E8F60, 0);
    if (k != -1) {
        LoaderQueueAppendSeparator_1cd670(h);
    }
}
