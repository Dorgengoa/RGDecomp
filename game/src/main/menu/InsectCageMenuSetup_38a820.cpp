/* rgp:protos */
#line 1
#include "types.h"
typedef rg_u128 u128;

struct V4f { f32 x, y, z, w; };
union V4 { u128 q; V4f f; };
struct S20 { u8 pad[0x20]; };
struct S40 { s8 m0; u8 pad[0x3F]; };
struct S24 { u8 pad[0x24]; };
struct Cam_B { u8 pad[0xC0]; };
struct Cam : Cam_B {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    f32 f78() { return VCM0(f32, 0x78); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void fC8(f32 a0) { VCM(void, (void *, f32), 0xC8, a0); }
    u8 padC4[0x1C];
    u128 mE0;
    u128 mF0;
};

extern "C" V4f D_0047FC30 __attribute__((section(".sdata")));
extern "C" V4f D_0047FC40 __attribute__((section(".sdata")));
extern "C" u8 *D_004832A8;
extern "C" s32 D_004832B8;
extern "C" s32 D_004832E4;
extern "C" s16 D_004832E8;
extern "C" s32 D_00483308;
extern "C" s32 D_00483310;
extern "C" s32 D_00483350;
extern "C" s32 D_00483354;
extern "C" f32 D_00483358;
extern "C" u8 D_004833EC;
extern "C" u8 D_004E9380[];
extern "C" u8 D_004E93E0[];
extern "C" u8 D_004E94E0[];

extern "C" {
s32 LoadHandlesPollAllReady_28b000(s32, s32);
void MemStackReset_14d830(void *);
void InsectCageCollectCollTris_389da0(void *);
void InsectCageMenuGetCurCageItem_391030(void);
void InsectCageBuildCbRootPath_38acb0(S24 *);
s32 LoadHandleFindByName_28af30(void *, s32, s32);
s32 LoadHandleGetData_28b270(s32, s32 *);
void PlacePointTableParse_386680(void *, void *, s32, s32);
s32 InsectCageGetType_3910c0(void);
s32 InsectCageMenuGetCageInsect_390f00(s32, s32);
void InsectCharaPathFormat_390de0(S40 *, s32, int, int);
void PlacePointInit_3869f0(S20 *);
s32 InsectCageGetCollTris_389d70(s32 *);
s32 MenuObjFindFree_390d80(s32 *);
void MenuObjLoadFromCfg_387930(s32, s32, s32, u8 *, s32);
void MenuObjBuildRandomRoute_3871a0(s32, void *, s32);
void InsectPlaceAtRandomSpotMaybe_38acf0(s32, S20 *, S20 *, s32);
void MenuObjWalkUpdateMaybe_387390(s32, s32, s32);
void InsectCageMenuBuildObjList_3909a0();
void LoadHandleArrayFree_28b0f0(s32, s32);
void InsectCageMenuTitleSet_3881b0(void);
void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
Cam *GetCurrentSceneCamera_389d40(void);
void CameraSetLag_177170(Cam *, f32, f32);
void UiEntryListSelectByTag_28ea90(void *, s32, s32);
}

extern "C" s32 InsectCageMenuSetup_38a820(void)
{
    s32 s29C;
    s32 s298;
    s32 s294;
    S24 s270 __attribute__((aligned(16)));
    s32 s250[5] __attribute__((aligned(16)));
    S40 a110[5] __attribute__((aligned(16)));
    S20 a70[5] __attribute__((aligned(16)));
    volatile V4 v60 __attribute__((aligned(16)));
    V4 v50 __attribute__((aligned(16)));
    s32 r;
    s32 x;
    s32 i;
    s32 *p;
    s32 v;
    s32 m;
    s32 j;
    s32 w;
    s32 k;
    s32 n;
    Cam *o;

    if (((unsigned char)LoadHandlesPollAllReady_28b000(D_004832E4, D_004832E8)) == 0) {
        return 0;
    }
    MemStackReset_14d830(D_004E93E0);
    InsectCageCollectCollTris_389da0(D_004E9380);
    InsectCageMenuGetCurCageItem_391030();
    InsectCageBuildCbRootPath_38acb0(&s270);
    r = LoadHandleFindByName_28af30(&s270, D_004832E4, D_004832E8);
    if (r != 0) {
        x = LoadHandleGetData_28b270(r, &s29C);
        PlacePointTableParse_386680(&D_004832B8, D_004E93E0, x, s29C);
    }
    for (i = 0; i < 5; i++) {
        s250[i] = InsectCageMenuGetCageInsect_390f00(((signed char)InsectCageGetType_3910c0()), i);
        InsectCharaPathFormat_390de0(&a110[i], s250[i], 0, 0);
    }
    PlacePointInit_3869f0(&a70[0]);
    PlacePointInit_3869f0(&a70[1]);
    PlacePointInit_3869f0(&a70[2]);
    PlacePointInit_3869f0(&a70[3]);
    PlacePointInit_3869f0(&a70[4]);
    m = InsectCageGetCollTris_389d70(&s298);
    for (j = 0; j < 5; j++) {
        if (a110[j].m0 != 0) {
            r = LoadHandleFindByName_28af30(&a110[j], D_004832E4, D_004832E8);
            if (r != 0) {
                x = LoadHandleGetData_28b270(r, &s29C);
                w = MenuObjFindFree_390d80(&s294);
                k = s294;
                MenuObjLoadFromCfg_387930(w, x, k + 0x263, D_004832A8 + k * 0x58, s250[j]);
                MenuObjBuildRandomRoute_3871a0(w, &D_004832B8, 4);
                InsectPlaceAtRandomSpotMaybe_38acf0(w, &a70[j], &a70[0], -1);
                for (n = 0; n < 6; n++) {
                    MenuObjWalkUpdateMaybe_387390(w, m, s298);
                }
            }
        }
    }
    InsectCageMenuBuildObjList_3909a0();
    LoadHandleArrayFree_28b0f0(D_004832E4, 7);
    InsectCageMenuTitleSet_3881b0();
    UiSetWidgetsVisibleById_291110(D_00483308, 0x753A, 1, 1);
    D_00483310 = 0;
    *(f32 *)&D_00483350 = 7.5f;
    D_00483354 = 0;
    v60.f.x = D_0047FC30.x;
    v60.f.y = D_0047FC30.y;
    v60.f.z = D_0047FC30.z;
    v60.f.w = D_0047FC30.w;
    v60.f.y = 6.0f + *(f32 *)&D_00483350;
    { f32 *pf = (f32 *)&v50; pf[0] = D_0047FC40.x; pf[1] = D_0047FC40.y; pf[2] = D_0047FC40.z; pf[3] = D_0047FC40.w; }
    o = GetCurrentSceneCamera_389d40();
    o->mE0 = v50.q;
    o->mF0 = *(u128 *)&v60;
    CameraSetLag_177170(o, 1.0f, -1.0f);
    o->fC8(-1.0f);
    D_00483358 = o->f78();
    if (D_004833EC != 0) {
        UiEntryListSelectByTag_28ea90(D_004E94E0, 0x7530, 0);
    } else {
        UiEntryListSelectByTag_28ea90(D_004E94E0, 0x7531, 1);
    }
    return 1;
}
