#include "types.h"

typedef unsigned __int128 u128;

typedef struct V4 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} V4;

typedef struct Ent {
    V4 v;
    s32 x10;
    s32 x14;
    s32 x18;
    s32 x1C;
} Ent;

typedef struct Hit {
    u8 pad0[0x42];
    s16 x42;
    u8 pad44[0x1C];
} Hit;

typedef struct Ex {
    f32 x0;
    u8 pad4[0xC];
    s16 x10;
    s16 x12;
    s16 x14;
} Ex;

typedef struct Chr {
    u8 pad0[0x180];
    u128 x180;
    u8 pad190[0x2B8];
    f32 x448;
} Chr;

typedef struct Actor {
    u8 pad0[0x3D8];
    s32 x3D8;
} Actor;

typedef struct Grp {
    u8 pad0[0x42];
    s16 x42;
} Grp;

typedef struct Unit {
    u8 pad0[0x30];
    s16 x30;
} Unit;

typedef struct Game {
    u8 pad0[0x18];
    Unit *x18;
} Game;

extern void FrameGetWorldPos_148f30(s32, V4 *);
extern void ModelSetPos_151110(Chr *, V4 *);
extern s32 ModelGetRootFrame_1511a0(Chr *);
extern s32 ObjRecGetValue_1c3d30(s32, s32, s32);
extern s32 ObjRecGetFlags_1c3d90(s32, s32, s32);
extern void ObjRecClearFlags_1c3dc0(s32, s32, s32, s32);
extern void ObjRecSetFlags_1c3e00(s32, s32, s32, s32);
extern s32 ObjRecIsActiveMaybe_1c4830(s32, s32);
extern Chr *ObjRecGetLiveObject_1c4a90(s32, s32);
extern s32 CollRaycastNearest_1c86e0(Hit *, s32, s32, Ent *, V4 *, f32 *);
extern f32 VecDistSqXZ_1cb390(Ent *, V4 *);
extern void VecMin_1cb590(V4 *, V4 *, void *);
extern void VecMax_1cb5b0(V4 *, V4 *, void *);
extern void VecLerp_1cbb20(V4 *, V4 *, V4 *, f32);
extern void VecCopy_1cbe30(void *, void *);
extern s16 CollTriGetAttr_1ce5b0(Hit *);
extern void ParamTableStepFade_1cfa70(s32, s32);
extern f32 ParamTableGetAlpha_1cfb40(s32, s32);
extern Ex *ParamTableGetRec_1cfbc0(s32, s32);
extern s32 MapFindSmallestBlockContaining_1e3810(s32, V4 *, f32);
extern s32 MapFindBlockOrAreaAtPos_1e39a0(s32, V4 *, f32);
extern s32 MapSlotsFindBlockById_1e49b0(s32, s32, s32);
extern s32 MapGetFirstAreaSlot_1e5760(s32);
extern s16 MapGetActiveAreaId_1e57b0(s32);
extern void MapDataGetColorVec4_1e7610(s32, V4 *);
extern s32 MapDataIsLoaded_1e79d0(s32);
extern s16 MapDataGetParentId_1e7bb0(s32);
extern s16 MapDataGetId_1e7bd0(s32);
extern s32 GetGameMode_1f59c0(void);
extern s32 GetCurrentScene_1f5be0(void);
extern void AreaColorFadeStepMaybe_1fdb80(void *);
extern void AreaColorFadeSetMaybe_1fdc70(void *, s16, V4 *, s32);
extern Game *GetGameData_1fede0(void);
extern s32 MapEvCollectCollTrisNearMaybe_1ff130(Hit *, s32, V4 *, V4 *, s32, f32);
extern s32 GetMapMgr_201a90(void);
extern s32 CharaGetAttachParentId_213890(Actor *);
extern s16 CharaGetAreaId_213c90(Actor *);
extern f32 CharaGetEffectiveSpeedScale_213dd0(Actor *);
extern Actor *ActionMgrFindById_233b50(void *, s32);
extern s16 CharaGetGroundAttr_238310(Actor *);
extern Grp *CharaGetGroundTri_238410(Actor *, s32);
extern s32 ObjGetNthAttachPointPosSafe_23b0c0(Chr *, s32, s32, V4 *);
extern f32 D_0045B080[];
extern s32 D_00481A90;
extern Chr *D_00481A94;
extern u8 D_004B6980[];
extern u8 D_004B8680[];

#pragma opt_dead_assignments off
void TaskCharaInfo_1f9c70(void) {
    f32 out;
    Ent ents[64];
    V4 lo;
    V4 hi;
    V4 pos;
    s32 sel[64];
    V4 mx;
    V4 mn;
    V4 cen;
    V4 mid;
    Hit buf[0x80];
    V4 hdr;
    V4 tmp;
    V4 q;
    Ent *e1;
    s32 h;
    s32 t;
    s32 cnt;
    s32 i;
    s32 j1;
    s32 fl;
    Ex *e;
    Ex *p;
    Actor *a;
    s32 k;
    Ent *en;
    f32 base;
    f32 k2;
    f32 r2;
    f32 k5;
    f32 r;
    f32 km5;
    s32 j;
    Ent *c;
    s32 j2;
    s32 n;
    f32 w;
    f32 h2;
    s32 nh;
    s32 m;
    Chr *obj;
    Ex *ex;
    s32 r3;
    u8 *tbl;
    s32 lt;

    tbl = D_004B8680;
    h = GetCurrentScene_1f5be0();
    t = GetMapMgr_201a90();
    cnt = 0;
    for (i = 0; i < 0xE0; i++) {
        ObjRecClearFlags_1c3dc0(h, 1, i, 0x1000000);
        if (D_00481A90 < 0) {
            ObjRecClearFlags_1c3dc0(h, 1, i, 0x4000000);
        }
        D_00481A94 = ObjRecGetLiveObject_1c4a90(h, i);
        if (D_00481A94 == 0) {
            continue;
        }
        if (ObjRecGetValue_1c3d30(h, 1, i) & 5) {
            continue;
        }
        ParamTableStepFade_1cfa70(h, i);
        D_00481A94->x448 = ParamTableGetAlpha_1cfb40(h, i);
        fl = ObjRecGetFlags_1c3d90(h, 1, i);
        if (!(fl & 0x4000) && ObjRecIsActiveMaybe_1c4830(h, i) == 0) {
            continue;
        }
        e = ParamTableGetRec_1cfbc0(h, i);
        if (e == 0) {
            continue;
        }
        lt = i < 12;
        if (!lt && i < 60) {
            p = ParamTableGetRec_1cfbc0(h, (!lt && i < 60) ? ((i - 12) >> 2) : -1);
            if (p != 0) {
                e->x12 = p->x12;
                e->x14 = p->x14;
            }
            continue;
        }
        e->x12 = -1;
        e->x14 = -1;
        e->x10 = 0;
        e->x0 = 1.0f;
        a = ActionMgrFindById_233b50(tbl, i);
        if (a != 0) {
            p = ParamTableGetRec_1cfbc0(h, CharaGetAttachParentId_213890(a));
            if (p != 0) {
                e->x12 = p->x12;
                e->x14 = p->x14;
                e->x0 = p->x0;
                continue;
            }
            if (GetGameMode_1f59c0() != 11 && GetGameMode_1f59c0() != 10 && GetGameMode_1f59c0() != 9 && GetGameMode_1f59c0() != 15) {
                e->x12 = CharaGetAreaId_213c90(a);
                e->x14 = CharaGetGroundAttr_238310(a);
                e->x0 = CharaGetEffectiveSpeedScale_213dd0(a);
                if (a->x3D8 & 4) {
                    e->x10 = CharaGetGroundTri_238410(a, 0)->x42;
                }
                continue;
            }
        }
        if (ObjGetNthAttachPointPosSafe_23b0c0(D_00481A94, 1, 0, &pos) == 0) {
            FrameGetWorldPos_148f30(ModelGetRootFrame_1511a0(D_00481A94), &pos);
        }
        if (GetGameMode_1f59c0() != 11 && GetGameMode_1f59c0() != 10 && GetGameMode_1f59c0() != 9 && GetGameMode_1f59c0() != 15) {
            k = MapFindBlockOrAreaAtPos_1e39a0(t, &pos, 0.0f);
            if (k != 0 && MapDataIsLoaded_1e79d0(k) == 0) {
                continue;
            }
        } else {
            k = MapFindSmallestBlockContaining_1e3810(t, &pos, 0.0f);
        }
        if (k == 0 || MapDataIsLoaded_1e79d0(k) == 0) {
            e->x12 = (k != 0) ? MapDataGetParentId_1e7bb0(k) : MapGetActiveAreaId_1e57b0(t);
            continue;
        }
        e->x12 = MapDataGetId_1e7bd0(k);
        if (fl & 0x2000) {
            e->x14 = 0;
        }
        if ((fl & 0xC000) || !(fl & 0x2000) || ((fl & 0x100000) && (fl & 0x600000))) {
            if (cnt == 0) {
                VecCopy_1cbe30(&lo, &pos);
                VecCopy_1cbe30(&hi, &pos);
            } else {
                VecMax_1cb5b0(&lo, &lo, &pos);
                VecMin_1cb590(&hi, &hi, &pos);
            }
            en = &ents[cnt];
            VecCopy_1cbe30(en, &pos);
            en->x10 = i;
            cnt++;
            en->x14 = 0;
            en->x18 = e->x12;
        }
    }
    if (cnt > 0) {
        base = D_0045B080[0];
        r = 4.0f * base;
        k2 = 2.0f * base;
        k5 = 5.0f * base;
        r2 = r * r;
        km5 = -5.0f * base;
        for (;;) {
            sel[0] = -1;
            for (e1 = ents, j1 = 0; j1 < cnt; j1++, e1++) {
                if (e1->x14 == 0) {
                    sel[0] = j1;
                    e1->x14 = 1;
                    break;
                }
            }
            if (sel[0] < 0) {
                break;
            }
            n = 1;
            c = &ents[sel[0]];
            VecCopy_1cbe30(&cen, c);
            VecCopy_1cbe30(&mn, c);
            VecCopy_1cbe30(&mx, c);
            for (en = ents, j2 = 0; j2 < cnt; j2++, en++) {
                if (en->x14 != 0) {
                    continue;
                }
                if (en->x18 != c->x18) {
                    continue;
                }
                if (!(VecDistSqXZ_1cb390(en, &cen) <= r2)) {
                    continue;
                }
                VecMax_1cb5b0(&mn, &mn, en);
                VecMin_1cb590(&mx, &mx, en);
                en->x14 = 1;
                sel[n] = j2;
                n++;
            }
            mn.x += 5.0f;
            mn.y += k2;
            mn.z += 5.0f;
            mx.x -= 5.0f;
            mx.y -= k5;
            mx.z -= 5.0f;
            VecLerp_1cbb20(&mid, &mn, &mx, 0.5f);
            h2 = mid.z; h2 = mn.z - h2;
            w = mid.x; w = mn.x - w;
            w = (w > h2) ? w : h2;
            nh = MapEvCollectCollTrisNearMaybe_1ff130(buf, 0x80, &mn, &mid, -1, w);
            if (nh <= 0) {
                continue;
            }
            {
                u8 *p_ = (u8 *)&hdr;
                u32 n_ = 16;
                if (p_ != 0) {
                    while (n_ != 0) {
                        *p_ = 0;
                        n_--;
                        p_++;
                    }
                }
            }
            hdr.y = km5;
            for (m = 0; m < n; m++) {
                c = &ents[sel[m]];
                fl = ObjRecGetFlags_1c3d90(h, 1, c->x10);
                obj = ObjRecGetLiveObject_1c4a90(h, c->x10);
                ex = ParamTableGetRec_1cfbc0(h, c->x10);
                c->v.y += k2;
                r3 = CollRaycastNearest_1c86e0(buf, nh, 0xC, c, &hdr, &out);
                if (r3 < 0) {
                    continue;
                }
                if (fl & 0xC000) {
                    *(u128 *)&tmp = obj->x180;
                    if (GetGameMode_1f59c0() == 11 || GetGameMode_1f59c0() == 10 || GetGameMode_1f59c0() == 9) {
                        tmp.y = tmp.y + (k2 + out * hdr.y);
                    } else {
                        tmp.y = c->v.y + out * hdr.y;
                    }
                    ModelSetPos_151110(obj, &tmp);
                }
                if (!(fl & 0x2000)) {
                    ex->x14 = CollTriGetAttr_1ce5b0(&buf[r3]);
                }
                if ((fl & 0x100000) && (fl & 0x600000)) {
                    ex->x10 = buf[r3].x42;
                }
                if (fl & 0x4000) {
                    ObjRecSetFlags_1c3e00(h, 1, c->x10, 0x20000000);
                }
                ObjRecClearFlags_1c3dc0(h, 1, c->x10, 0x4000);
            }
        }
    }
    k = MapSlotsFindBlockById_1e49b0(t, GetGameData_1fede0()->x18->x30, 0);
    if (k == 0 || MapDataIsLoaded_1e79d0(k) == 0) {
        k = MapGetFirstAreaSlot_1e5760(t);
    }
    if (k != 0 && MapDataIsLoaded_1e79d0(k) != 0) {
        MapDataGetColorVec4_1e7610(k, &q);
        AreaColorFadeSetMaybe_1fdc70(D_004B6980, MapDataGetId_1e7bd0(k), &q, 0xF);
    }
    AreaColorFadeStepMaybe_1fdb80(D_004B6980);
}
