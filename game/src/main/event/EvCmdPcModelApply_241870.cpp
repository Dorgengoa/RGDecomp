#include "types.h"

typedef struct {
    s32 a, b, c, d, e, f, g, h, i, j, k, l, m, n;
} Msg;

typedef struct {
    u8 pad0[0x10];
    s16 *unk10;
} Info;

class Unit {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    Info * v3C4() { return VCM0(Info *, 0x3C4); }
};

typedef struct {
    u8 pad0[0x14];
    s32 unk14;
} Glob;

typedef struct {
    u8 pad0[0x4DC];
    s32 unk4DC;
} Ev;

extern "C" {
extern void DrawCtxVif1HandlerStop_15dc40(void);
extern Ev *ObjRecGetLiveObject_1c4a90(s32, s32);
extern void LoaderReleaseById_1cd340(s32, s32);
extern void CharaDataReleaseSubRecsByKey_1ed750(s32, s32, s32);
extern void CharaDataMgrUpdate_1ed9e0(s32);
extern void CharaDataLoadSubRecById_1eda70(s32, Msg *);
extern s32 GetLoaderMgr_1f59d0(void);
extern s32 GetCharaDataMgr_1fdb70(void);
extern Glob *GetGameData_1fede0(void);
extern Unit *CharaMgrPoolFindByDataId_3a8a70(s32, s32, s32, s32, s32, s32, s32);
extern s32 D_0047E8B0;
extern s32 D_0047E8B4;
extern s32 *gEventContext;
}

extern "C" s32 EvCmdPcModelApply_241870(void)
{
    Msg m __attribute__((aligned(16)));
    s32 id;
    Unit *u;
    Info *inf;
    s16 *p;
    Ev *ev;
    s32 h;

    id = GetCharaDataMgr_1fdb70();
    u = CharaMgrPoolFindByDataId_3a8a70(GetGameData_1fede0()->unk14, 0x2AF9, 1, 1, 0, 0, 0);
    if (u == 0) {
        return 0;
    }
    inf = u->v3C4();
    if (inf == 0) {
        return 0;
    }
    p = inf->unk10;
    if (p == 0) {
        return 0;
    }
    ev = ObjRecGetLiveObject_1c4a90(*gEventContext, 0);
    if (ev == 0) {
        return 0;
    }
    CharaDataReleaseSubRecsByKey_1ed750(id, 0x3E9, 1);
    m.g = 0;
    m.c = -1;
    m.d = -1;
    m.e = -1;
    m.f = -1;
    m.h = -1;
    m.i = 0;
    m.j = -1;
    m.m = -1;
    m.k = 0;
    m.l = 0;
    m.n = 0;
    m.a = 0x3E9;
    m.b = 0;
    m.h = ev->unk4DC;
    m.f = 0x3E9;
    m.c = 1;
    m.d = 1;
    m.e = *p;
    m.m = D_0047E8B0;
    m.n = 1;
    CharaDataLoadSubRecById_1eda70(id, &m);
    CharaDataReleaseSubRecsByKey_1ed750(id, 0x3E9, 5);
    m.a = 0x3E9;
    m.f = 0x3E9;
    m.c = 5;
    m.j = 7;
    m.d = 5;
    m.b = 0;
    m.m = D_0047E8B4;
    CharaDataLoadSubRecById_1eda70(id, &m);
    DrawCtxVif1HandlerStop_15dc40();
    CharaDataMgrUpdate_1ed9e0(id);
    h = GetLoaderMgr_1f59d0();
    LoaderReleaseById_1cd340(h, D_0047E8B0);
    LoaderReleaseById_1cd340(h, D_0047E8B4);
    D_0047E8B0 = -1;
    return 1;
}
