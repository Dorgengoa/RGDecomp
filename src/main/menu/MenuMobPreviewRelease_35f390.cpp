/* MATCH (s41m). Stale pre-match note follows -- PARK: length 0xDC vs retail 0xD4 (8 over) after 1 round. Not re-tried. */
#include "types.h"
#pragma optimization_level 3
#pragma opt_common_subs off
extern "C" {

extern void MemStackReset_14d830(s32 arg0);
extern void NameTableFreeGroup_158ac0(s32 arg0, s32 arg1);
extern void DrawCtxVif1HandlerStop_15dc40(void);
extern s32 GetDrawCtxNameTable_15de40(void);
extern void ModelObjExEffectsStopAll_1b0870(void *arg0);
extern void LoaderReleaseById_1cd340(s32 arg0, s32 arg1);
extern s32 GetLoaderMgr_1f59d0(void);
extern void MenuCatalogTabSetup_360590(void *arg0);
extern s32 D_00482338;

class VC_0 {
public:
    u8 pad[0x1B0];
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void f();
};
void MenuMobPreviewRelease_35f390(void *arg0)
{
    s32 temp_3;
    void *temp_4;

    if (*(s32 *)((u8 *)arg0 + 0x238) != -1) {
        LoaderReleaseById_1cd340(GetLoaderMgr_1f59d0(), *(s32 *)((u8 *)arg0 + 0x238));
    }
    if (D_00482338 != 0) {
        if (*(void **)((u8 *)arg0 + 0x250) != NULL) {
            DrawCtxVif1HandlerStop_15dc40();
            ModelObjExEffectsStopAll_1b0870(*(void **)((u8 *)arg0 + 0x250));
            temp_4 = *(void **)((u8 *)arg0 + 0x250);
            ((VC_0 *)(temp_4))->f();
            NameTableFreeGroup_158ac0(GetDrawCtxNameTable_15de40(), 0x209);
            *(void **)((u8 *)arg0 + 0x250) = NULL;
        }
        MemStackReset_14d830(D_00482338);
    }
    temp_3 = *(s32 *)((u8 *)arg0 + 0x284);
    if (temp_3 == 3) {
        *(s32 *)((u8 *)arg0 + 0x284) = 0;
    } else if (temp_3 == 4) {
        *(s32 *)((u8 *)arg0 + 0x284) = 1;
    }
    MenuCatalogTabSetup_360590(arg0);
}

}
