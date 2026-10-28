/* rgp:protos */
#line 1
#define KD 1
#define KF 1
#define KS 0
#include "types.h"
#ifndef KA
#define KA 0
#endif
#ifndef KB
#define KB 0
#endif
#ifndef KD
#define KD 0
#endif
#ifndef KG
#define KG 0
#endif
#if KS
#define obj ((s32)sys)
#endif
#ifndef KF
#define KF 0
#endif

struct Vec4 { f32 x, y, z, w; };
struct Info {
    Vec4 a;
    Vec4 b;
    s32 e0;
    f32 e4;
    f32 e8;
    u8 ec;
    u8 ed;
};

#define V4 virtual void
class Actor {
public:
    u8 pad[0xC0];
    VC_VPTR_MEMBER;         
             
             
            
    void getPos(void *out) { VCM(void, (void *, void *), 0xA4, out); }
};
static inline void GetPos(Actor *a, void *v) { if (a != 0) a->getPos(v); }

extern "C" {
Actor *ObjRecGetLiveObject_1c3bc0(u8 *, s32);
s32 CollTriGetAttr_1ce5b0(s32);
f32 GameSceneGetTimeStep_1ceba0(u8 *);
s32 MapAreaGetGroundTypeMaybe_1dceb0(s32);
void MapMgrSlotsUpdateEntriesMaybe_1e16b0(u8 *, Info *);
void MapTickAnims_1e1ac0(u8 *);
s32 MapFindObjInAreaByName_1e4470(u8 *, void *, void *);
s32 MapSlotsFindById_1e4b90(u8 *, s32, s32);
s32 MapGetFirstAreaSlot_1e5760(u8 *);
s32 MapDataFindObjByName_1e71d0(s32, void *);
s32 MapDataHasKujeSky_1e7a60(s32);
s32 MapDataHasDesertSandstorm_1e7a70(s32);
s32 MapDataIsSkyOff_1e7ad0(s32);
s32 MapDataHasLeafSunlight_1e7af0(s32);
s32 MapDataHasLensFlare_1e7b10(s32);
u8 *GetCurrentScene_1f5be0(void);
s32 GetActionMgr_1fdb50(void);
u8 *GetGameData_1fede0(void);
u8 *GetMapNodeFadeMaybe_201a10(void);
u8 *GetMapNodeSpinFadeMaybe_201a20(void);
u8 *GetLensFlareMgr_201a40(void);
s32 GetMapSunaKemu_201a60(void);
s32 GetMapSequencer_201a80(void);
u8 *GetMapMgr_201a90(void);
u8 *ActionMgrFindById_233b50(s32, s32);
s32 CharaGetGroundTri_238410(u8 *, s32);
void CharaGetPos_2388a0(u8 *, Vec4 *);
void TaskMoveBefore_27bf50(void *, void *);
void MapNodeFadeUpdateMaybe_2d9120(u8 *, Vec4 *, s32, void *);
void MapNodeSpinFadeUpdateMaybe_2d9260(u8 *, Vec4 *, s32, void *);
void LensFlareFadeUpdate_2edf90(u8 *);
void MapSequencerUpdate_2f9f60(s32);
void SunaKemuUpdate_33b610(s32);
void SunaKemuStart_33baa0(s32, void *);
void SunaKemuClear_33bb00(s32);
s32 StateFlagTest_3ccd70(s32, s32);
extern u8 D_0045B080[0x400];
extern u8 D_0045C010[];
extern u8 D_0045C028[];
extern u8 D_0045C040[];
extern u8 D_0045C058[];
extern u8 D_0045C068[];
extern u8 D_0045C078[];
extern u8 D_0045C088[];
extern u8 D_0045C090[];
extern u8 D_0045C098[];
extern f32 D_0047E540;
extern f32 D_0047E544;
extern f32 D_0047E548;
extern f32 D_0047E54C;
extern f32 D_0047E550;
extern f32 D_0047E554;
extern f32 D_0047E558;
extern f32 D_0047E55C;
extern u8 D_00481AFC;
extern u8 D_00481B04;
extern s32 D_00481B2C;
}

extern "C" void TaskStepMap_200d70(void)
{
    Info info __attribute__((aligned(16)));
    Vec4 pb __attribute__((aligned(16)));
    Vec4 pa __attribute__((aligned(16)));
#if KD == 1
    bool flag2;
    s32 r2;
    s32 r;
    u8 *w;
    f32 f;
    bool flag;
    u8 *game;
    s32 snd;
    u8 *chr;
    u8 *ui;
    s32 ev;
    s32 obj;
    u8 *sys;
    Actor *actor;
#else
    u8 *sys;
    Actor *actor;
    u8 *game;
    u8 *chr;
    u8 *ui;
    s32 ev;
#if !KS
    s32 obj;
#endif
    s32 snd;
    u8 *w;
    f32 f;
    s32 r;
    bool flag;
    bool flag2;
    s32 r2;
#endif

    sys = GetCurrentScene_1f5be0();
    actor = ObjRecGetLiveObject_1c3bc0(sys, *(s32 *)(sys + 0x4344));
    game = GetGameData_1fede0();
    chr = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), *(s16 *)(*(u8 **)(game + 0x18) + 0x18E));
    MapSequencerUpdate_2f9f60(GetMapSequencer_201a80());
    ui = GetMapMgr_201a90();
    MapTickAnims_1e1ac0(ui);
    info.a.x = 0.0f;
    info.a.y = 0.0f;
    info.a.z = 0.0f;
    info.a.w = 1.0f;
    info.b.w = 1.0f;
    info.b.x = 0.0f;
    info.b.y = 0.0f;
    info.b.z = 0.0f;
#if KG == 2
    GetPos(actor, &info.a);
#else
    if (actor != 0) actor->getPos(&info.a);
#endif
    if (chr != 0) CharaGetPos_2388a0(chr, &info.b);
    info.e0 = D_00481B2C;
    info.e4 = GameSceneGetTimeStep_1ceba0(sys);
    f = *(f32 *)D_0045B080;
    info.ec = 0;
    info.ed = 0;
    info.e8 = 10.0f * f;
    MapMgrSlotsUpdateEntriesMaybe_1e16b0(ui, &info);
    D_00481B04 = info.ec;
    if (info.ed != 0) {
        TaskMoveBefore_27bf50(D_0045C010, D_0045C028);
    } else {
        TaskMoveBefore_27bf50(D_0045C010, D_0045C040);
    }
    ev = MapGetFirstAreaSlot_1e5760(ui);
#if KS
    sys = (u8 *)MapSlotsFindById_1e4b90(
#else
    obj = MapSlotsFindById_1e4b90(
#endif
        ui, *(s16 *)(*(u8 **)(game + 0x18) + 0x30), 0);
    snd = GetMapSunaKemu_201a60();
    if (D_00481AFC == 0) {
        if (ev != 0 && ((short)MapAreaGetGroundTypeMaybe_1dceb0(ev)) == 2 && obj != 0 && ((unsigned char)MapDataHasDesertSandstorm_1e7a70(obj)) != 0) {
            SunaKemuStart_33baa0(snd, D_0045C058);
            D_00481AFC = 1;
        }
    } else if (ev == 0 || ((short)MapAreaGetGroundTypeMaybe_1dceb0(ev)) != 2 || obj == 0 || ((unsigned char)MapDataHasDesertSandstorm_1e7a70(obj)) == 0) {
        SunaKemuClear_33bb00(snd);
        D_00481AFC = 0;
    }
    SunaKemuUpdate_33b610(snd);
    w = GetLensFlareMgr_201a40();
    if (obj != 0 && ((unsigned char)MapDataHasLensFlare_1e7b10(obj)) != 0) {
        *(s32 *)(w + 0x148) = 0;
    } else {
        *(s32 *)(w + 0x148) = 1;
    }
    LensFlareFadeUpdate_2edf90(w);
    {
        Vec4 *pv = &pb;
        pv->x = D_0047E540;
        pv->y = D_0047E544;
        pv->z = D_0047E548;
        pv->w = D_0047E54C;
        if (actor != 0) {
            actor->getPos(pv);
            pb.y -= f;
        }
    }
    flag = false;
    r = 0;
    if (ev != 0) {
        r = MapDataFindObjByName_1e71d0(ev, D_0045C068);
        if (r != 0 && StateFlagTest_3ccd70(*(s32 *)(game + 0x10), 0x7CF) == 0 && obj != 0 &&
            ((unsigned char)MapDataHasLeafSunlight_1e7af0(obj)) != 0 && chr != 0 && (*(s32 *)(chr + 0x3D8) & 4) &&
            ((unsigned short)CollTriGetAttr_1ce5b0(CharaGetGroundTri_238410(chr, 0))) >= 8) {
            flag = true;
        }
    }
    w = GetMapNodeSpinFadeMaybe_201a20();
#if KF
    if (flag) {
        *(s32 *)(w + 4) = 0;
    } else {
        *(s32 *)(w + 4) = 1;
    }
#else
    if (!flag) {
        *(s32 *)(w + 4) = 1;
    } else {
        *(s32 *)(w + 4) = 0;
    }
#endif
    MapNodeSpinFadeUpdateMaybe_2d9260(w, &pb, r, D_0045C078);
    {
        Vec4 *pv = &pa;
        pv->x = D_0047E550;
        pv->y = D_0047E554;
        pv->z = D_0047E558;
        pv->w = D_0047E55C;
        if (actor != 0) actor->getPos(pv);
    }
    flag2 = false;
    r2 = MapFindObjInAreaByName_1e4470(ui, D_0045C088, D_0045C090);
    if (r2 != 0 && obj != 0 && ((unsigned char)MapDataHasKujeSky_1e7a60(obj)) != 0) {
        flag2 = true;
    }
    w = GetMapNodeFadeMaybe_201a10();
#if KF
    if (flag2) {
        *(s32 *)(w + 4) = 0;
    } else {
        *(s32 *)(w + 4) = 1;
    }
#else
    if (!flag2) {
        *(s32 *)(w + 4) = 1;
    } else {
        *(s32 *)(w + 4) = 0;
    }
#endif
    MapNodeFadeUpdateMaybe_2d9120(w, &pa, r2, D_0045C098);
    {
        s32 v_;
        v_ = (obj != 0 && ((unsigned char)MapDataIsSkyOff_1e7ad0(obj)) != 0) ? (*(s32 *)(ui + 0x60) | 2) : (*(s32 *)(ui + 0x60) & ~2);
        *(s32 *)(ui + 0x60) = v_;
    }
}
