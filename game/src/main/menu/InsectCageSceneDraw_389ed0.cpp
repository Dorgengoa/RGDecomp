/* rgp:protos */
#line 1
#pragma optimization_level 3
#include "types.h"
typedef rg_u128 u128;

union V4 { u128 q; struct { f32 x, y, z, w; } f; };
struct Sub { u8 pad[0x68]; };
struct St { u8 p0[0x30]; Sub a; Sub b; s32 m100; u8 p104[0xC]; Sub c; f32 f178; u8 p17C[0x14]; };
struct EntA { u8 pad[0x9D0]; };
struct Key { s16 m0; u8 pad[2]; };
struct Cam_B { u8 pad[0xC0]; };
struct Cam : Cam_B {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void getPos(V4 * a0) { VCM(void, (void *, V4 *), 0xA8, a0); }
};
struct Ent_B { u8 pad[0x1B0]; };
struct Ent : Ent_B {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f48() { VCM0(void, 0x48); }
    u8 p1B4[0x970 - 0x1B4];
    s32 m970;
    u8 p974[0x11];
    s8 m985;
    u8 m986[1];
};

extern "C" s32 D_0047FC50;
extern "C" s32 D_0047FC60;
extern "C" f32 D_0047FC68;
extern "C" s32 D_0047FC70;
extern "C" s32 D_0048335C;
extern "C" s8 *D_00483298;
extern "C" s8 D_0048329C;
extern "C" u8 *D_004832AC;
extern "C" s32 D_004832D8;
extern "C" s32 D_00483308;
extern "C" s32 D_0048330C;
extern "C" s32 D_00483318;
extern "C" s32 D_0048331C;
extern "C" s16 D_00483360;
extern "C" s8 D_004833F8;
extern "C" f32 D_004E94CC[];
extern "C" u8 D_004E94C0[];
extern "C" u8 D_004E9510[];
extern "C" u8 D_004E9530[];

extern "C" {
void DrawScreenFillRect_38a4b0(void *);
void MapMgrGetAuxAreaFwd_389e40(void);
void MapRenderAuxAreaAtCamera_200b20(void);
s32 GetDrawCtx_15de80(void);
Cam *GetCurrentSceneCamera_389d40(void);
s32 DrawEnvGetVsyncInterval_144130(s32);
void BitArray16Ctor_3842e0(Key *);
s32 BitArrayTest_384320(void *, s32);
void DrawListAddTexLoad_1418c0(s32, s32, f32);
void NameTableNodeCtor_15ae50(Sub *);
void PlaneShadowDescInit_156a70(St *);
void NameTableCopyNode_15ad70(Sub *, s32);
void DrawListBeginPlaneShadowPass_147b80(s32, St *);
void PlaneShadowDescSetPlane_156a20(St *, void *, V4 *, void *);
void DrawListAddPlaneShadowMtxPkt_147ae0(s32, St *);
void DrawListEndPlaneShadowPass_146cc0(s32);
f32 VecDistanceXZ_13d390(V4 *, V4 *);
void MenuObjDrawHighlightMaybe_386de0(Ent *);
void MenuObjSetDraw_384f20(s32);
void TaskDrawGlare_2f6b20(void);
void InsectCageUnitMarkersDraw_3888e0(void);
void InsectCageStatusPanelDraw_3884b0(void);
void InsectCageItemIconDraw_385d80(void *);
void InsectCageButtonHintDraw_388ee0(void);
void MenuCursorObjDrawModel_3860c0(void *);
void UiDrawWidgets_291910(s32);
void InsectCagePreviewModelDraw_389340(void);
void TextEntryDraw_436610(s8 *);
}

#pragma opt_common_subs off
extern "C" void InsectCageSceneDraw_389ed0(void)
{
    Key key __attribute__((aligned(16)));
    V4 pos __attribute__((aligned(16)));
    St st __attribute__((aligned(16)));
    V4 v60 __attribute__((aligned(16)));
    V4 v50 __attribute__((aligned(16)));
    s32 w;
    Cam *cam;
    f32 sc;
    s32 i;
    s32 off;
    Ent *e;
    s32 r;
    s32 g;
    s8 *p;

    DrawScreenFillRect_38a4b0(&D_0047FC50);
    MapMgrGetAuxAreaFwd_389e40();
    MapRenderAuxAreaAtCamera_200b20();
    w = GetDrawCtx_15de80();
    cam = GetCurrentSceneCamera_389d40();
    if (cam != 0) {
        cam->getPos(&pos);
    } else {
        pos.q = 0;
        pos.f.w = 1.0f;
    }
    r = DrawEnvGetVsyncInterval_144130(w);
    sc = 1.0f;
    if (r == 1) {
        sc = 0.5f;
    }
    BitArray16Ctor_3842e0(&key);
    key.m0 = D_00483360;
    if (BitArrayTest_384320(&D_0048335C, 1) != 0 && D_004833F8 != 0) {
        D_004E94CC[0] = 2.0f;
    } else {
        D_004E94CC[0] = 0.0f;
    }
    if (BitArrayTest_384320(&D_0048335C, 7) == 0) {
        DrawListAddTexLoad_1418c0(w, 0x320, 1.0f);
        NameTableNodeCtor_15ae50(&st.a);
        NameTableNodeCtor_15ae50(&st.b);
        NameTableNodeCtor_15ae50(&st.c);
        PlaneShadowDescInit_156a70(&st);
        st.f178 = 0.5f;
        NameTableCopyNode_15ad70(&st.a, D_00483318);
        NameTableCopyNode_15ad70(&st.c, D_0048331C);
        st.m100 = 1;
        DrawListBeginPlaneShadowPass_147b80(w, &st);
        for (i = 0; i < 5; i++) {
            e = (Ent *)D_004832AC;
            off = i * 0x9D0;
            e = (Ent *)((u8 *)e + off);
            if (e->m985 != 0 && BitArrayTest_384320(e->m986, 7) == 0) {
                e = (Ent *)&((EntA *)D_004832AC)[i];
                v60.q = *(u128 *)((u8 *)e + 0x180);
                v60.f.y -= 8.0f;
                if (e->m970 != 0x7DF) {
                    D_0047FC68 = 0.0f;
                } else {
                    D_0047FC68 = 1.0f;
                }
                PlaneShadowDescSetPlane_156a20(&st, &D_0047FC60, &v60, &D_0047FC70);
                DrawListAddPlaneShadowMtxPkt_147ae0(w, &st);
                ((Ent *)(D_004832AC + off))->f48();
            }
        }
        DrawListEndPlaneShadowPass_146cc0(w);
    }
    for (i = 0; i < 5; i++) {
        if (BitArrayTest_384320(&key, 7) != 0) {
            v50.q = *(u128 *)(D_004832AC + i * 0x9D0 + 0x180);
            if (VecDistanceXZ_13d390(&v50, &pos) < 10.0f) {
                continue;
            }
        }
        MenuObjDrawHighlightMaybe_386de0((Ent *)(D_004832AC + i * 0x9D0));
    }
    MenuObjSetDraw_384f20(D_004832D8);
    TaskDrawGlare_2f6b20();
    InsectCageUnitMarkersDraw_3888e0();
    InsectCageStatusPanelDraw_3884b0();
    InsectCageItemIconDraw_385d80(D_004E9510);
    InsectCageItemIconDraw_385d80(D_004E9530);
    InsectCageButtonHintDraw_388ee0();
    MenuCursorObjDrawModel_3860c0(D_004E94C0);
    if ((g = D_00483308) != 0) {
        UiDrawWidgets_291910(g);
        InsectCagePreviewModelDraw_389340();
    }
    if ((g = D_0048330C) != 0) {
        UiDrawWidgets_291910(g);
    }
    if (D_0048329C >= 4 && (p = D_00483298) != 0) {
        TextEntryDraw_436610(p);
    }
}
