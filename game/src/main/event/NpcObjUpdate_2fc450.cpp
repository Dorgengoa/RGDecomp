/* rgp:protos */
#line 1
#include "types.h"
#include "vec.h"

typedef struct { s32 v[6]; } Tbl6_002fc450;

typedef struct Node_002fc450 {
    Vec4 pos;                           /* 0x00 */
    f32 speed;                          /* 0x10 */
    u8 pad14[0x20 - 0x14];
    struct Node_002fc450 *next;         /* 0x20 */
    s16 wait;                           /* 0x24 */
    s16 type;                           /* 0x26 */
} Node_002fc450;

typedef struct {
    s16 id;
    u8 pad2[2];
    u8 flags;
} Info_002fc450;

typedef struct {
    u8 pad0[0xC];
    Info_002fc450 *info;                /* 0x0C */
    u8 pad10[0x4C - 0x10];
    Node_002fc450 *start;               /* 0x4C */
    Node_002fc450 *cur;                 /* 0x50 */
    s16 count;                          /* 0x54 */
} Route_002fc450;

class Actor_002fc450 {
public:
    u8 pad0[0x180];
    Vec4 pos;                           /* 0x180 */
    u8 pad190[0x1B0 - 0x190];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v44(f32 a0) { VCM(void, (void *, f32), 0x44, a0); }
    u8 pad1B4[0x1F0 - 0x1B4];
    u8 sub1F0[0x464 - 0x1F0];           /* 0x1F0 */
    s32 unk464;                         /* 0x464 */
    u8 unk468;                          /* 0x468 */
};

typedef struct {
    u8 pad0[0x6C];
    s32 unk6C;
} Sys8_002fc450;

typedef struct {
    u8 pad0[0x18E];
    s16 unk18E;
} Sys18_002fc450;

typedef struct {
    u8 pad0[0x8];
    Sys8_002fc450 *unk8;
    u8 padC[0x18 - 0xC];
    Sys18_002fc450 *unk18;
} Sys_002fc450;

typedef struct {
    u16 flags;                          /* 0x00 */
    u8 pad02[0x10 - 0x2];
    u8 sub10[0x4C - 0x10];              /* 0x10 */
    s16 unk4C;                          /* 0x4C */
    s16 unk4E;                          /* 0x4E */
    u8 pad50[0xA0 - 0x50];
    Vec4 pos;                           /* 0xA0 */
    Vec4 rot;                           /* 0xB0 */
    u8 padC0[0xC4 - 0xC0];
    s16 unkC4;                          /* 0xC4 */
    s16 unkC6;                          /* 0xC6 */
    s16 unkC8;                          /* 0xC8 */
    s16 unkCA;                          /* 0xCA */
    s16 unkCC;                          /* 0xCC */
    s16 unkCE;                          /* 0xCE */
    s8 unkD0;                           /* 0xD0 */
    u8 unkD1;                           /* 0xD1 */
    u8 padD2[0xD4 - 0xD2];
    f32 unkD4;                          /* 0xD4 */
    u8 padD8[0xDC - 0xD8];
    f32 unkDC;                          /* 0xDC */
} Obj_002fc450;

extern "C" {
extern f32 D_0047D3FC;
extern f32 D_0047D1FC;
extern f32 D_0047D278;
extern f32 D_0047F0A0;
extern f32 D_0047F0A4;
extern f32 D_0047F0A8;
extern f32 D_0047F0AC;
extern char *D_00451D80[];
extern s32 D_00451DA0[];
extern s32 D_00451DC0[];
extern char D_00461E18[];
}

extern "C" {
extern s32 GetStaticScene_1c6c70(void);
extern s32 GetCharaResMgr_1fdb60(void);
extern Sys_002fc450 *GetGameData_1fede0(void);
extern Route_002fc450 * GroupGetRecordById_41c2a0(s32, long long, long long, s32);
extern void NpcObjLoadMarkPos_2fb990(Obj_002fc450 *);
extern void NpcObjSaveMarkPos_2fb920(Obj_002fc450 *);
extern void NpcObjReleaseCharaData_2fb820(Obj_002fc450 *);
extern Actor_002fc450 *ObjRecGetLiveObject_1c4a90(s32, s32);
extern void ModelObjPlayMotionByName_1867a0(Actor_002fc450 *, char *, s32);
extern s32 MotionListIsFinished_171d90(void *, s32);
extern f32 VecDistance_13d3d0(Vec4 *, Vec4 *);
extern f32 VecDistanceXZ_13d390(Vec4 *, Vec4 *);
extern void sceVu0SubVector(Vec4 *, Vec4 *, Vec4 *);
extern void sceVu0Normalize(Vec4 *, Vec4 *);
extern f32 Atan2f_1291a8(f32, f32);
extern f32 AngleStepToward_13c150(f32, f32, f32, s32);
extern void sceVu0UnitMatrix(Mtx4 *);
extern void sceVu0RotMatrixY(Mtx4 *, Mtx4 *, f32);
extern void MtxMulVec4_10a8c0(Vec4 *, Mtx4 *, Vec4 *);
extern void sceVu0ScaleVector(Vec4 *, Vec4 *, f32);
extern void sceVu0AddVector(Vec4 *, Vec4 *, Vec4 *);
extern s32 CharaResRequestNpc_1f2bb0(s32, s32, s32, s32, s32);
extern s32 CharaResGetStatusById_1f04c0(s32, s32);
extern void CharaResReleaseById_1f1160(s32, s32, s32);
extern void ObjRecSetFlags_1c3e00(s32, s32, s32, s32);
extern void ObjRecClearFlags_1c3dc0(s32, s32, s32, s32);
extern void HeadLookBindNodes_1c5b70(void *, s32, long long, char *);
extern void ModelSetPos_151110(Actor_002fc450 *, Vec4 *);
extern void ModelSetRot_151080(Actor_002fc450 *, Vec4 *);
}

extern "C" void NpcObjUpdate_2fc450(Obj_002fc450 *p)
{
    s32 world;
    s32 mgr;
    Sys_002fc450 *sys;
    Route_002fc450 *route;
    s32 near;
    s32 idle;
    Actor_002fc450 *actor;
    s32 voice[6] __attribute__((aligned(16)));
    s32 loop[6] __attribute__((aligned(16)));
    Vec4 fwd __attribute__((aligned(16)));
    Mtx4 m __attribute__((aligned(16)));
    Vec4 tpos __attribute__((aligned(16)));
    Vec4 dir __attribute__((aligned(16)));
    s32 flags;
    s32 idx;
    Node_002fc450 *node;
    f32 speed;
    Actor_002fc450 *ta;
    s32 sel;
    s32 attached;
    s32 r;
    f32 t;
    f32 lim;

    if (!(p->flags & 1)) {
        return;
    }
    t = p->unkDC + D_0047D3FC;
    lim = D_0047D1FC;
    p->unkDC = t;
    if (t > lim) {
        p->unkDC = t - lim;
    }
    world = GetStaticScene_1c6c70();
    mgr = GetCharaResMgr_1fdb60();
    sys = GetGameData_1fede0();
    route = GroupGetRecordById_41c2a0(sys->unk8->unk6C, (long long)(p->unkC6), (long long)(-1), 1);
    if (route == 0) {
        return;
    }
    p->unkD1 = 0;
    near = 0;
    idle = 1;
    NpcObjLoadMarkPos_2fb990(p);
    if (p->unkC4 != -1 && p->unkCA == 5) {
        actor = ObjRecGetLiveObject_1c4a90(world, p->unkC4);
        if (actor != 0) {
            p->pos = actor->pos;
        }
    }
    *(Tbl6_002fc450 *)voice = *(Tbl6_002fc450 *)D_00451DA0;
    *(Tbl6_002fc450 *)loop = *(Tbl6_002fc450 *)D_00451DC0;
    if (p->unkCC == 1) {
        NpcObjSaveMarkPos_2fb920(p);
        return;
    }
    if (p->unkCC == 0) {
        p->unkCC = -1;
        idle = 0;
        if (p->unkC4 != -1) {
            actor = ObjRecGetLiveObject_1c4a90(world, p->unkC4);
            if (actor != 0) {
                idx = p->unkD0;
                flags = 0;
                if (loop[idx]) {
                    flags |= 2;
                }
                ModelObjPlayMotionByName_1867a0(actor, D_00451D80[idx], flags);
            }
        }
    }
    node = 0;
    fwd.x = D_0047F0A0;
    fwd.y = D_0047F0A4;
    fwd.z = D_0047F0A8;
    fwd.w = D_0047F0AC;
    if (route != 0) {
        node = route->cur;
    }
    if (node != 0) {
        switch (node->type) {
        case 4:
            if (node->wait == 0) {
                if (route->count < 6) {
                    route->count++;
                    idle = 0;
                }
                break;
            }
            if (route->count < 6) {
                idle = 0;
            }
            route->count++;
            if (route->count >= node->wait) {
                route->count = node->wait;
                if (p->unkC4 != -1) {
                    actor = ObjRecGetLiveObject_1c4a90(world, p->unkC4);
                    if (actor != 0 && MotionListIsFinished_171d90(actor->sub1F0, -1) != 0) {
                        route->cur = node->next;
                        route->count = 0;
                    }
                }
            }
            break;
        case 1:
            p->unkCE = 1;
        case 0:
            if (node->wait == 0) {
                if (route->count < 6) {
                    route->count++;
                    idle = 0;
                }
                break;
            }
            if (route->count < 6) {
                idle = 0;
            }
            route->count++;
            if (route->count >= node->wait) {
                route->cur = node->next;
                route->count = 0;
            }
            break;
        case 2:
        case 3:
            speed = D_0047D278 * node->speed;
            if (p->unkC4 != 0) {
                ta = ObjRecGetLiveObject_1c4a90(world, sys->unk18->unk18E);
                if (ta != 0) {
                    tpos = ta->pos;
                    if (VecDistance_13d3d0(&tpos, &p->pos) <= 40.0f) {
                        near = 1;
                        break;
                    }
                    if (node->type == 3) {
                        if (VecDistance_13d3d0(&tpos, &p->pos) <= 70.0f) {
                            near = 2;
                            speed = 1.0f;
                        }
                    }
                }
            }
            idle = 0;
            sceVu0SubVector(&dir, &node->pos, &p->pos);
            sceVu0Normalize(&dir, &dir);
            t = Atan2f_1291a8(dir.x, dir.z);
            if (node->type == 2 || near == 2) {
                p->rot.y = AngleStepToward_13c150(p->rot.y, t, 15.0f, 1);
            } else {
                p->rot.y = AngleStepToward_13c150(p->rot.y, t, D_0047D3FC, 0);
            }
            p->pos.y += dir.y * speed;
            sceVu0UnitMatrix(&m);
            sceVu0RotMatrixY(&m, &m, p->rot.y);
            MtxMulVec4_10a8c0(&dir, &m, &fwd);
            sceVu0ScaleVector(&dir, &dir, speed);
            sceVu0AddVector(&p->pos, &p->pos, &dir);
            if (VecDistanceXZ_13d390(&node->pos, &p->pos) <= 10.0f) {
                route->cur = node->next;
                route->count = 0;
            }
            break;
        case 5:
            if (route != 0) {
                route->cur = route->start;
                route->count = 0;
            }
            break;
        }
    }
    sel = 0;
    attached = 0;
    switch (p->unkCA) {
    case 2:
        if (CharaResRequestNpc_1f2bb0(mgr, world, p->unkC4, p->unkC6, 1) != 0) {
            p->unkCA = 3;
        } else {
            p->unkCA = 1;
            p->unkC4 = -1;
        }
        break;
    case 3:
        r = ((short)CharaResGetStatusById_1f04c0(mgr, p->unkC4));
        if (r == 4) {
            CharaResReleaseById_1f1160(mgr, world, p->unkC4);
            NpcObjReleaseCharaData_2fb820(p);
            p->unkCA = 1;
            p->unkC4 = -1;
        } else if (r == 3) {
            p->unkCA = 5;
            p->flags |= 4;
            if (p->unkCE != 0) {
                sel = 1;
            } else {
                sel = 0;
            }
            actor = ObjRecGetLiveObject_1c4a90(world, p->unkC4);
            if (actor != 0) {
                flags = 4;
                if (loop[sel]) {
                    flags |= 2;
                }
                ModelObjPlayMotionByName_1867a0(actor, D_00451D80[sel], flags);
            }
            ObjRecSetFlags_1c3e00(world, 1, p->unkC4, 0x4000);
            attached = 1;
            idle = 0;
            if (route != 0 && route->info != 0) {
                p->unkC8 = route->info->id;
            }
            HeadLookBindNodes_1c5b70(p->sub10, world, (long long)(p->unkC4), D_00461E18);
            p->unk4C = 2;
            p->unk4E = 0;
            p->flags &= ~8;
        }
        break;
    case 5:
        if (node != 0) {
            sel = node->type;
            actor = ObjRecGetLiveObject_1c4a90(world, p->unkC4);
            if (near == 1) {
                if (p->unkCE != 0) {
                    sel = 1;
                } else {
                    sel = 0;
                }
            }
            if (near == 2) {
                sel = 2;
            }
            flags = 0;
            if (loop[sel]) {
                flags |= 2;
            }
            if (actor != 0) {
                ModelObjPlayMotionByName_1867a0(actor, D_00451D80[sel], flags);
            }
        }
        if (!(p->flags & 8) && actor != 0 && route != 0 && route->info != 0 && (route->info->flags & 1)) {
            actor->unk464 = 0x1F;
            actor->unk468 = 1;
            actor->v44(1.0f);
            p->flags |= 8;
        }
        break;
    case 0:
    case 1:
    case 4:
    case 7:
        break;
    case 6:
        if (p->unkC4 != -1) {
            CharaResReleaseById_1f1160(mgr, world, p->unkC4);
        }
        p->unkCA = 7;
        p->unkC4 = -1;
        break;
    }
    p->unkD0 = sel;
    if (p->unkC4 != -1 && node != 0 && voice[sel]) {
        ObjRecSetFlags_1c3e00(world, 1, p->unkC4, 0x4000);
    }
    if (p->unkC4 != -1) {
        if (p->unkD4 > 160.0f && idle) {
            ObjRecSetFlags_1c3e00(world, 1, p->unkC4, 8);
            p->unkD1 = 1;
        } else {
            ObjRecClearFlags_1c3dc0(world, 1, p->unkC4, 8);
            p->unkD1 = 0;
        }
    }
    if (p->unkC4 >= 0) {
        actor = ObjRecGetLiveObject_1c4a90(world, p->unkC4);
        if (actor != 0) {
            ModelSetPos_151110(actor, &p->pos);
            ModelSetRot_151080(actor, &p->rot);
            if (attached) {
                actor->unk464 = 1;
                actor->unk468 = 0;
            }
        }
    }
    NpcObjSaveMarkPos_2fb920(p);
}
