#include "types.h"
#pragma opt_propagation off

class VObj {
public:
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
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
    virtual s16 *f(s16);
};

struct Game {
    u8 pad0[0x270];
    u8 m270;
    u8 pad271[3];
    s32 m274;
    s32 m278;
    s32 m27C;
    u8 pad280[4];
    s32 m284;
};

extern "C" {
extern s32 PadIsTriggered_1839f0(u8 *, s32);
extern u8 *GetGameData_1fede0(void);
extern u8 *GetWorldDataMgr_1fedf0(void);
extern s32 ReturnZero_207fe0(void);
extern void PlayMenuSe_289ef0(s32);
extern void UiEntryListSelectByTag_28ea90(s32, s32, s32);
extern void UiEntryListGetCurrentData_28ec60(s32);
extern void StateMachineSetState_28ede0(s32, s32, s32);
extern void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
extern void MenuResLoad_299400(void);
extern void IterInit_370170(void *, void *);
extern u8 *IterNext_370040(void *);
extern void InvViewCtorFromOwner_3cec70(void *, u8 *, s32, s32, s32, s32);
extern u8 *DataTableFindRowById_3fd770(u8 *, s32);
extern s32 MenuGridCursorInput_28e170(s32, u8 *, s32, s32);
extern void MenuCatalogSaveCursor_35ed80(Game *);
extern void MenuCatalogSaveTabCursor_35ee20(Game *, s32);
extern void MenuMobPreviewRelease_35f390(Game *);
extern void MenuMobPreviewRequest_35f470(Game *);
extern void BestiaryCountSetMaybe_3c3280(s32, s32, s32);
extern u8 D_0047F810;
extern Game *D_00482388;
extern s32 D_00482FE8;
extern u8 D_004B2570[];
}

static inline bool modeA(s32 *p) {
    if (*p == 0) {
        return true;
    }
    if (*p == 1) {
        return 1;
    }
    if (*p == 2) {
        return 1;
    }
    return false;
}

static inline bool modeB(s32 *p) {
    if (*p == 3) {
        return true;
    }
    if (*p == 4) {
        return true;
    }
    return false;
}

extern "C" s32 MenuCatalogListSelectState_35c1e0(s32 pad0, s32 arg1) {
    s32 it1[2];
    s32 it2[2];
    u8 q[0x20];
    u8 *g;
    u8 *h;
    u8 *e;
    u8 *t;
    s16 *r;
    u8 *p;
    s32 res;
    s32 mode;
    s32 *p2;

    if (arg1 != 0) {
        UiEntryListSelectByTag_28ea90(D_00482388->m278, 0x24, 0);
        if (D_00482388->m284 == 0) {
            UiSetWidgetsVisibleById_291110(D_00482388->m274, 0x1F6, 1, 1);
        }
    }
    if (ReturnZero_207fe0() != 0 && PadIsTriggered_1839f0(D_004B2570, 0x100) != 0) {
        g = GetGameData_1fede0();
        h = GetWorldDataMgr_1fedf0();
        InvViewCtorFromOwner_3cec70(q, g, 6, -1, -1, -1);
        IterInit_370170(it1, q);
        while ((e = IterNext_370040(it1)) != 0) {
            u8 *lst;
            u8 *d = *(u8 **)(e + 0x10);
            lst = *(u8 **)(*(u8 **)(*(u8 **)(g + 8) + 0x94) + 0xC);
            t = DataTableFindRowById_3fd770(lst, *(s16 *)(d + 6));
            if (t == 0) {
                continue;
            }
            r = (*(VObj **)(*(u8 **)(h + 0x64) + 0xC))->f(*(s16 *)(t + 8));
            if (r == 0) {
                continue;
            }
            BestiaryCountSetMaybe_3c3280(*(s32 *)(g + 0x18), *r, 1);
        }
        p = *(u8 **)(*(u8 **)(*(u8 **)(g + 8) + 0x94) + 0xC);
        if (p != 0) {
            p += 0x88;
        }
        IterInit_370170(it2, p);
        while ((e = IterNext_370040(it2)) != 0) {
            if (*(u8 *)(e + 0x1C) & 1) {
                continue;
            }
            r = (*(VObj **)(*(u8 **)(h + 0x64) + 0xC))->f(*(s16 *)(e + 8));
            if (r == 0) {
                continue;
            }
            BestiaryCountSetMaybe_3c3280(*(s32 *)(g + 0x18), *r, 0x3E7);
        }
    }
    mode = 0;
    if (D_00482388->m284 == 0) {
        mode = 2;
    } else {
        if (D_00482388->m284 == 3) {
            goto one;
        }
        if (D_00482388->m284 != 4) {
            goto done;
        }
    one:
        mode = 1;
    }
done:
    res = MenuGridCursorInput_28e170(D_00482388->m278, D_004B2570, mode, 0);
    UiEntryListGetCurrentData_28ec60(D_00482388->m278);
    if (res == 2 && modeA(p2 = &D_00482388->m284)) {
        MenuCatalogSaveTabCursor_35ee20(*(Game *volatile *)&D_00482388, *p2);
        MenuCatalogSaveCursor_35ed80(D_00482388);
        D_00482FE8 = 0;
        StateMachineSetState_28ede0(D_00482388->m27C, 0xA5, 0);
        if (D_00482388->m270 != 0) {
            MenuResLoad_299400();
            D_0047F810 = 0;
        } else {
            D_0047F810 = 1;
        }
    } else if (res == 2 && modeB(&D_00482388->m284)) {
        PlayMenuSe_289ef0(6);
        MenuMobPreviewRelease_35f390(D_00482388);
    } else if (res == 1) {
        if (D_00482388->m284 == 1) {
            goto call;
        }
        if (D_00482388->m284 != 0) {
            goto skip;
        }
    call:
        MenuMobPreviewRequest_35f470(D_00482388);
    skip:;
    }
    return 1;
}
