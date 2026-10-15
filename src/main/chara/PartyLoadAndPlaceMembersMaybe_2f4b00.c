#include "types.h"
#pragma optimization_level 3

typedef unsigned __int128 u128;

typedef struct V4 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} V4;

typedef struct Pt3 {
    f32 a;
    f32 b;
    f32 c;
} Pt3;

typedef struct Cam {
    s16 m0;
    u8 pad2[0xC - 2];
    f32 mC;
    f32 m10;
    f32 m14;
    f32 m18;
    u8 pad1C[4];
    Pt3 m20[2];
    u8 pad38[0x40 - 0x38];
    f32 m40;
    f32 m44;
    f32 m48;
    f32 m4C;
    f32 m50;
    f32 m54;
} Cam;

typedef struct Slot {
    u8 pad0[0x10];
    f32 m10;
    f32 m14;
    f32 m18;
    f32 m1C;
} Slot;

typedef struct Obj {
    u8 pad0[0x50];
    u128 m50;
    u128 m60;
    u8 pad70[0xE0 - 0x70];
    u128 mE0;
    u128 mF0;
    u8 pad100[0x1C0 - 0x100];
    V4 m1C0;
} Obj;

typedef struct Ent {
    u8 pad0[0x464];
    s32 m464;
    u8 m468;
} Ent;

typedef struct Sub18 {
    u8 pad0[0x18E];
    s16 m18E;
} Sub18;

typedef struct Sys {
    u8 pad0[0x18];
    Sub18 *m18;
} Sys;

typedef struct Mgr {
    u8 pad0[0x4344];
    s32 m4344;
} Mgr;

extern void DelayThread_117618(s32);
extern f32 Cosf_128d30(f32);
extern f32 Sinf_128fd0(f32);
extern Cam *SysGetModeMsg_1c39b0(void);
extern Obj *ObjRecGetLiveObject_1c3bc0(Mgr *, s32);
extern Ent *ObjRecGetLiveObject_1c4a90(Mgr *, s32);
extern void MatFromRotPos_1caf90(V4 *, V4 *, V4 *);
extern void MatMulVec4Args_1cb7f0(V4 *, V4 *, f32, f32, f32, f32);
extern void VecScale_1cbca0(V4 *, V4 *, f32);
extern void VecSub_1cbd00(V4 *, V4 *, V4 *);
extern void VecCopy_1cbe30(V4 *, V4 *);
extern s32 LoaderCountQueued_1cd620(s32);
extern s32 GetLoaderMgr_1f59d0(void);
extern Mgr *GetCurrentScene_1f5be0(void);
extern void TaskLoadChara_1fb4c0(void);
extern void PartyUpdateLeaderFlags_1fc3c0(void);
extern s32 GetActionMgr_1fdb50(void);
extern Sys *GetGameData_1fede0(void);
extern void CharaSetYaw_2138f0(s32, f32);
extern void CharaSetPos_213a40(s32, V4 *);
extern s32 ActionMgrFindById_233b50(s32, s32);
extern void CharaSavePlacedPosMaybe_238270(s32);
extern void EffectMgrLoadPollGlobal_2d8880(void);
extern void PartySyncCharaResMaybe_2f4100(void);
extern void PartyLoadSlotReset_2f5830(void *);
extern void LoaderTickGlobal_2f74c0(void);
extern s32 PartyCountMembers_3c2010(Sub18 *, s32, s32);
extern s32 PartyGetMemberId_3c2490(Sub18 *, s32);
extern s32 PartyCountExcludingLeader_3c2610(Sub18 *, s32, s32);
extern s32 PartyGetNonLeaderId_3c2750(Sub18 *, s32);
extern void sceVu0CopyVector(V4 *, V4 *);
extern f32 D_0047D404;
extern f32 D_0047DCE0;
extern f32 D_0047DCE4;
extern f32 D_0047DCE8;
extern f32 D_0047EF80;
extern f32 D_0047EF84;
extern f32 D_0047EF88;
extern f32 D_0047EF8C;
extern u8 D_004E6480[][0x88];

#define BZERO(d, n) { u8 *p_ = (u8 *)(d); u32 n_ = (n); if (p_) while (n_) { *p_ = 0; n_--; p_++; } }

void PartyLoadAndPlaceMembersMaybe_2f4b00(void)
{
    V4 pos;
    V4 rot;
    V4 a[2];
    V4 b[2];
    V4 rv;
    V4 c130;
    V4 c120;
    V4 mtx[4];
    V4 out;
    V4 cC0;
    V4 t;
    V4 vA0;
    V4 v90;
    s32 i;
    s32 w;
    Cam *cam;
    f32 x;
    Sys *sys;
    s32 lst;
    Mgr *mgr;
    s32 o;
    Obj *ob;
    s32 n;
    s32 k;
    s32 id;
    Slot *sl;
    Ent *e;
    s32 k2;
    s32 id2;
    s32 o2;

    for (i = 0; i < 3; i++) {
        PartyLoadSlotReset_2f5830(D_004E6480[i]);
    }
    PartySyncCharaResMaybe_2f4100();
    PartyUpdateLeaderFlags_1fc3c0();
    w = GetLoaderMgr_1f59d0();
    for (;;) {
        LoaderTickGlobal_2f74c0();
        TaskLoadChara_1fb4c0();
        EffectMgrLoadPollGlobal_2d8880();
        if (LoaderCountQueued_1cd620(w) <= 0) {
            break;
        }
        DelayThread_117618(0xA);
    }
    cam = SysGetModeMsg_1c39b0();
    pos.x = D_0047EF80;
    pos.y = D_0047EF84;
    pos.z = D_0047EF88;
    pos.w = D_0047EF8C;
    BZERO(&rot, 0x10);
    for (i = 0; i < 2; i++) {
        x = 0.0f;
        if (i == 0) {
            x = 20.0f;
        } else if (i == 1) {
            x = -20.0f;
        }
        a[i].x = x;
        a[i].y = 0.0f;
        a[i].z = -20.0f;
        a[i].w = 1.0f;
        b[i].x = 0.0f;
        b[i].y = 0.0f;
        b[i].z = 0.0f;
        b[i].w = 0.0f;
    }
    switch (cam->m0) {
    case 5:
        pos.x = cam->mC;
        pos.y = cam->m10;
        pos.z = cam->m14;
        pos.w = 1.0f;
        rot.x = 0.0f;
        rot.y = cam->m18;
        rot.z = 0.0f;
        rot.w = 0.0f;
        for (i = 0; i < 2; i++) {
            a[i].x = cam->m20[i].a;
            a[i].z = cam->m20[i].b;
            b[i].y = cam->m18;
        }
        break;
    case 6:
        pos.x = cam->m20[0].a;
        pos.y = cam->m20[0].b;
        pos.z = cam->m20[0].c;
        pos.w = 1.0f;
        rot.x = 0.0f;
        rot.y = 0.0f;
        rot.z = 0.0f;
        rot.w = 0.0f;
        break;
    case 0:
        pos.w = 1.0f;
        pos.x = D_0047DCE0;
        rot.x = 0.0f;
        rot.z = 0.0f;
        pos.y = D_0047DCE4;
        pos.z = D_0047DCE8;
        rot.w = 0.0f;
        rot.y = D_0047D404;
        for (i = 0; i < 2; i++) {
            b[i].y = D_0047D404;
        }
        break;
    case 2:
        pos.x = cam->m10;
        pos.y = cam->m14;
        pos.z = cam->m18;
        pos.w = 1.0f;
        rot.y = D_0047D404;
        rot.x = 0.0f;
        rot.z = 0.0f;
        rot.w = 0.0f;
        break;
    case 4:
        pos.x = cam->mC;
        pos.y = cam->m10;
        pos.z = cam->m14;
        pos.w = 1.0f;
        rot.x = 0.0f;
        rot.y = cam->m18;
        rot.z = 0.0f;
        rot.w = 0.0f;
        break;
    case 1:
    case 3:
        break;
    }
    sys = GetGameData_1fede0();
    lst = GetActionMgr_1fdb50();
    mgr = GetCurrentScene_1f5be0();
    switch (cam->m0) {
    case 0:
    case 2:
    case 4:
    case 5:
    case 6:
        o = ActionMgrFindById_233b50(lst, sys->m18->m18E);
        if (o == 0) {
            return;
        }
        rv.x = Sinf_128fd0(rot.y);
        rv.y = 0.0f;
        rv.z = Cosf_128d30(rot.y);
        rv.w = 0.0f;
        CharaSetYaw_2138f0(o, rot.y);
        CharaSetPos_213a40(o, &pos);
        CharaSavePlacedPosMaybe_238270(o);
        ob = ObjRecGetLiveObject_1c3bc0(mgr, mgr->m4344);
        if (ob != 0) {
            VecCopy_1cbe30(&c120, &pos);
            VecScale_1cbca0(&c130, &rv, 120.0f);
            VecSub_1cbd00(&c130, &c120, &c130);
            c130.y += 30.0f;
            sceVu0CopyVector(&ob->m1C0, &c120);
            ob->m60 = *(u128 *)&c130;
            ob->m50 = *(u128 *)&c120;
            ob->mF0 = *(u128 *)&c130;
            ob->mE0 = *(u128 *)&c120;
        }
        ObjRecGetLiveObject_1c4a90(mgr, sys->m18->m18E);
        MatFromRotPos_1caf90(mtx, &rot, &pos);
        n = PartyCountExcludingLeader_3c2610(sys->m18, 1, 1);
        for (k = 0; k < n; k++) {
            id = PartyGetNonLeaderId_3c2750(sys->m18, k);
            o = ActionMgrFindById_233b50(lst, id);
            if (o != 0) {
                MatMulVec4Args_1cb7f0(&out, mtx, a[k].x, 0.0f, a[k].z, 1.0f);
                VecCopy_1cbe30(&cC0, &b[k]);
                CharaSetYaw_2138f0(o, cC0.y);
                CharaSetPos_213a40(o, &out);
                CharaSavePlacedPosMaybe_238270(o);
                ObjRecGetLiveObject_1c4a90(mgr, id);
            }
        }
        break;
    case 1:
        n = PartyCountMembers_3c2010(sys->m18, 1, 1);
        for (k2 = 0; k2 < n; k2++) {
            id2 = PartyGetMemberId_3c2490(sys->m18, k2);
            o2 = ActionMgrFindById_233b50(lst, id2);
            if (o2 != 0) {
                sl = (Slot *)((u8 *)cam + k2 * 16);
                t.x = sl->m10;
                t.y = sl->m14;
                t.z = sl->m18;
                t.w = 1.0f;
                CharaSetYaw_2138f0(o2, sl->m1C);
                CharaSetPos_213a40(o2, &t);
                CharaSavePlacedPosMaybe_238270(o2);
                e = ObjRecGetLiveObject_1c4a90(mgr, id2);
                if (e != 0) {
                    e->m464 = 0x1F;
                    e->m468 = 0;
                }
            }
        }
        ob = ObjRecGetLiveObject_1c3bc0(mgr, mgr->m4344);
        if (ob != 0) {
            vA0.x = cam->m40;
            vA0.y = cam->m44;
            vA0.z = cam->m48;
            vA0.w = 1.0f;
            v90.x = cam->m4C;
            v90.y = cam->m50;
            v90.z = cam->m54;
            v90.w = 1.0f;
            sceVu0CopyVector(&ob->m1C0, &v90);
            ob->m60 = *(u128 *)&vA0;
            ob->m50 = *(u128 *)&v90;
            ob->mF0 = *(u128 *)&vA0;
            ob->mE0 = *(u128 *)&v90;
        }
        break;
    case 3:
        break;
    }
}
