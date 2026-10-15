#include "types.h"

typedef struct { f32 x, y, z, w; } V4;
typedef struct { u8 pad0[0x448]; f32 f448; u8 pad44C[0x774 - 0x44C]; s32 f774; } Obj;
typedef struct { u8 pad0[4]; f32 f4; u8 pad8[4]; f32 fC; u8 pad10[2]; s16 f12; s16 f14; } Ent;
typedef struct { u8 pad0[0x30]; V4 f30; u8 pad40[0x30]; V4 f70; u8 pad80[0x100]; V4 f180; V4 f190; } Anm;
typedef struct { s16 f0; } Tag;
typedef struct { u8 pad0[0x18]; Tag *f18; } Grp;
typedef struct { u8 pad0[0x238]; Grp *f238; } Pty;
typedef struct { u8 pad0[0xA]; s16 fA; u8 padC[0x18E - 0xC]; s16 f18E; } Ldr;
typedef struct { u8 pad0[0x18]; Ldr *f18; u8 pad1C[4]; Pty *f20; } Game;
typedef struct { u8 pad0[0x4344]; s32 f4344; } World;
class Cam {
public:
    u8 pad0[0xC0];
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
    virtual void GetPos(V4 *);
};

extern "C" {
World *GetCurrentScene_1f5be0(void);
s32 GetDrawCtx_15de80(void);
Game *GetGameData_1fede0(void);
s32 GetMapMgr_201a90(void);
Cam *ObjRecGetLiveObject_1c3bc0(World *, s32);
s32 EvtCurIsRunning_26abf0(void);
s32 GetGameMode_1f59c0(void);
s32 ReturnZero_207f40(void);
s32 ObjRecIsDrawableMaybe_1c48b0(World *, s32);
s32 ObjRecGetValue_1c3d30(World *, s32, s32);
Obj *ObjRecGetLiveObject_1c4a90(World *, s32);
Ent *ParamTableGetRec_1cfbc0(World *, s32);
s32 ObjGetNthAttachPointPosSafe_23b0c0(Obj *, s32, s32, V4 *);
s32 ModelGetRootFrame_1511a0(Obj *);
void FrameGetWorldPos_148f30(s32, V4 *);
f32 ModelObjGetScaledRadius_23b140(Obj *);
s32 IsInBattle_288420(void);
f32 VecDist_1cb420(V4 *, V4 *);
f32 VecDistXZ_1cb3f0(V4 *, V4 *);
s32 AttackChainGetPhase_382eb0(void *);
Anm *MapGetAreaLightSetById_1e54d0(s32, s32, s32);
s32 IsInBattleMode_288380(void);
void VecCopy_1cbe30(V4 *, V4 *);
void VecLerp_1cbb20(V4 *, V4 *, V4 *, f32);
void MtxCopy_1cbde0(V4 *, V4 *);
s32 ObjRecGetFlags_1c3d90(World *, s32, s32);
void Character2LightBlendSetTarget_1aebe0(Obj *, s32, V4 *, V4 *, V4 *, V4 *, u8);
extern V4 D_0047E4D0 __attribute__((section(".sdata")));
extern f32 D_0045B080[];
extern u8 D_004B86C0[];
extern s32 D_00481A90;

static inline s32 SlotOf(s32 i) {
    if (!(i >= 12)) {
        return -1;
    }
    if (i >= 0x3C) {
        return -1;
    }
    return (i - 12) >> 2;
}

#define SLOT(i) (((i) >= 12 && (i) < 0x3C) ? ((i) - 12) >> 2 : -1)
static inline s32 Slot2(s32 i) { return (i >= 12 && i < 0x3C) ? (i - 12) >> 2 : -1; }
static inline s32 Slot3(s32 i) { s32 r = -1; if (i >= 12 && i < 0x3C) r = (i - 12) >> 2; return r; }
void TaskDrawCharaPre_1f8ba0(void) {
    V4 cam;
    V4 pos;
    V4 m1[4];
    V4 m2[4];
    V4 c1;
    V4 c2;
    World *w;
    Game *g;
    s32 fp;
    Cam *c;
    u8 flag;
    f32 r;
    s32 leader;
    f32 dd;
    f32 v;
    s32 i;
    s32 t;
    Obj *o;
    Ent *e;
    s32 k;
    bool sp;
    f32 d;
    Tag *x;
    Grp *q;
    Obj *o2;
    f32 scale;
    f32 k1;
    f32 lo;
    f32 k2;
    Ent *e2;
    s32 s6;
    s32 s7;
    s32 n;
    Anm *a;
    Anm *b2;
    s32 fl;

    w = GetCurrentScene_1f5be0();
    GetDrawCtx_15de80();
    g = GetGameData_1fede0();
    fp = GetMapMgr_201a90();
    cam = D_0047E4D0;
    c = ObjRecGetLiveObject_1c3bc0(w, w->f4344);
    if (c != 0) {
        c->GetPos(&cam);
    }
    {
        s32 t_ = (EvtCurIsRunning_26abf0() != 0) ^ 1;
        if (t_) t_ = GetGameMode_1f59c0() != 10;
        if (t_) t_ = GetGameMode_1f59c0() != 9;
        if (t_) t_ = (ReturnZero_207f40() != 0) ^ 1;
        flag = t_;
    }
    scale = 1.0f;
    if (g->f18->fA == 700 || g->f18->fA == 0x6A4) {
        scale = 0.5f;
    }
    leader = g->f18->f18E;
    i = 0;
    k1 = 0.25f * D_0045B080[0];
    k2 = 1.25f * D_0045B080[0];
    for (; i < 0xE0; i++) {
        if (ObjRecIsDrawableMaybe_1c48b0(w, i) == 0) {
            continue;
        }
        switch (ObjRecGetValue_1c3d30(w, 1, i)) {
        case 9:
        case 7:
        case 4:
            continue;
        }
        if (GetGameMode_1f59c0() == 15 && !(i < 0x80) && i < 0x9C) {
            continue;
        }
        o = ObjRecGetLiveObject_1c4a90(w, i);
        if (o == 0) {
            continue;
        }
        e = ParamTableGetRec_1cfbc0(w, i);
        if (e == 0) {
            continue;
        }
        if (ObjGetNthAttachPointPosSafe_23b0c0(o, 0, 0, &pos) == 0) {
            FrameGetWorldPos_148f30(ModelGetRootFrame_1511a0(o), &pos);
        }
        k = i;
        sp = 0;
        if (i >= 12 && i < 0x3C) {
            k = (i >= 12 && i < 0x3C) ? (i - 12) >> 2 : -1;
            sp = 1;
        }
        r = ModelObjGetScaledRadius_23b140(o);
        if (IsInBattle_288420() != 0) {
            q = GetGameData_1fede0()->f20->f238;
            x = (q != 0) ? q->f18 : 0;
            if (x != 0) {
                if (k == 0x82 && x->f0 == 0x271B) {
                    k = 0;
                    sp = 1;
                }
                if (k == 0x80 && x->f0 == 0x40A && pos.y < cam.y) {
                    r *= 2.0f;
                    pos.y = cam.y;
                }
            }
        }
        e->fC = VecDist_1cb420(&cam, &pos);
        if (!(k < 0xC0) && k < 0xE0) {
            if (!(e->f4 <= scale)) {
                e->f4 = scale;
            }
        }
        if (sp) {
            if (flag) {
                o2 = ObjRecGetLiveObject_1c4a90(w, k);
                if (o2 != 0) {
                    v = o2->f448;
                    if (!(v <= e->f4)) {
                        v = e->f4;
                    }
                    o->f448 = v;
                }
            }
        } else if (flag) {
            lo = r + k1;
            d = e->f4;
            dd = e->fC;
            r = r + k2;
            if (w->f4344 == 3) {
                if (leader == k) {
                    dd = VecDistXZ_1cb3f0(&cam, &pos);
                    if (dd < 1.0f) {
                        dd = 0.0f;
                    }
                } else {
                    dd = 2.0f * r;
                }
            }
            if (dd < lo) {
                d = 0.0f;
            }
            if (dd < r) {
                d = (dd - lo) / (r - lo);
            }
            if (!(d <= e->f4)) {
                d = e->f4;
            }
            o->f448 = d;
        }
        if (o->f448 <= 0.0f) {
            continue;
        }
        e2 = ParamTableGetRec_1cfbc0(w, k);
        if (e2 == 0) {
            continue;
        }
        m1[0].x = 0.0f; m1[0].y = 1.0f; m1[0].z = 0.0f; m1[0].w = 0.0f;
        m1[1].x = 0.0f; m1[1].y = 1.0f; m1[1].z = 0.0f; m1[1].w = 0.0f;
        m1[2].x = 0.0f; m1[2].y = 1.0f; m1[2].z = 0.0f; m1[2].w = 0.0f;
        m1[3].x = 0.0f; m1[3].y = 1.0f; m1[3].z = 0.0f; m1[3].w = 0.0f;
        m2[0].x = 0.0f; m2[0].y = 0.0f; m2[0].z = 0.0f; m2[0].w = 128.0f;
        m2[1].x = 0.0f; m2[1].y = 0.0f; m2[1].z = 0.0f; m2[1].w = 128.0f;
        m2[2].x = 0.0f; m2[2].y = 0.0f; m2[2].z = 0.0f; m2[2].w = 128.0f;
        m2[3].x = 0.0f; m2[3].y = 0.0f; m2[3].z = 0.0f; m2[3].w = 128.0f;
        c1.x = 0.0f; c1.y = 0.0f; c1.z = 0.0f; c1.w = 128.0f;
        c2.x = 0.0f; c2.y = 0.0f; c2.z = 0.0f; c2.w = 128.0f;
        s6 = e2->f12;
        s7 = e2->f14;
        n = 0;
        if (GetGameMode_1f59c0() == 9 && AttackChainGetPhase_382eb0(D_004B86C0) >= 2) {
            c2.x = 143.0f; c1.x = 143.0f;
            c2.y = 147.0f; c1.y = 147.0f;
            c2.z = 152.0f; c1.z = 152.0f;
            c2.w = 128.0f; c1.w = 128.0f;
        } else {
            if (GetGameMode_1f59c0() == 10) {
                s7 = 0;
            }
            a = MapGetAreaLightSetById_1e54d0(fp, s6, s7);
            if (a != 0) {
                if (s7 >= 0) {
                    n = s7 + s6 * 100;
                } else {
                    n = -1;
                }
                if (IsInBattleMode_288380() == 0) {
                    VecCopy_1cbe30(&c1, &a->f180);
                    VecCopy_1cbe30(&c2, &a->f190);
                } else {
                    b2 = MapGetAreaLightSetById_1e54d0(fp, s6, 0);
                    VecLerp_1cbb20(&c1, &a->f180, &b2->f180, 0.5f);
                    VecLerp_1cbb20(&c2, &a->f190, &b2->f190, 0.5f);
                    n += 50;
                }
                MtxCopy_1cbde0(m1, &a->f30);
                MtxCopy_1cbde0(m2, &a->f70);
            }
        }
        fl = ObjRecGetFlags_1c3d90(w, 1, k);
        if (D_00481A90 >= 0 && (fl & 0x4000000)) {
            if (D_00481A90 % 4 >= 2) {
                c2.x = 250.0f; c1.x = 250.0f;
                c2.y = 118.0f; c1.y = 118.0f;
                c2.z = 80.0f; c1.z = 80.0f;
                c2.w = 128.0f; c1.w = 128.0f;
            }
            Character2LightBlendSetTarget_1aebe0(o, n, m1, m2, &c1, &c2, 0);
        } else {
            {
                s32 t_ = o->f774 > 0;
                if (t_) t_ = n > 0;
                Character2LightBlendSetTarget_1aebe0(o, n, m1, m2, &c1, &c2, t_);
            }
        }
    }
}
}
