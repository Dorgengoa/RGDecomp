#include "types.h"

typedef struct V4 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} V4;

typedef struct Ex {
    u8 pad0[0x4];
    f32 x4;
    u8 pad8[0x4];
    f32 xC;
    s16 x10;
    s16 x12;
    s16 x14;
} Ex;

typedef struct Src {
    u8 pad0[0x30];
    u8 x30[0x40];
    u8 x70[0x110];
    V4 x180;
    V4 x190;
} Src;

class Cam {
public:
    u8 pad0[0xC0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void SetCol(V4 * a0) { VCM(void, (void *, V4 *), 0xA4, a0); }
};

class Chr {
public:
    u8 pad0[0x1B0];
    VC_VPTR_MEMBER;
    
    
    
    void SetA(f32 a0) { VCM(void, (void *, f32), 0x18, a0); }
    u8 pad1B4[0x294];
    f32 x448;
    u8 pad44C[0x90];
    s32 x4DC;
    u8 pad4E0[0x294];
    s32 x774;
};

typedef struct Game {
    u8 pad0[0x4344];
    s32 x4344;
} Game;

extern "C" {
extern Game *GetCurrentScene_1f5be0(void);
extern s32 GetDrawCtx_15de80(void);
extern void GetGameData_1fede0(void);
extern s32 GetMapMgr_201a90(void);
extern Cam *ObjRecGetLiveObject_1c3bc0(Game *, s32);
extern s32 GetGameMode_1f59c0(void);
extern s32 ReturnZero_207f40(void);
extern s32 ObjRecIsDrawableMaybe_1c48b0(Game *, s32);
extern s32 ObjRecGetValue_1c3d30(Game *, s32, s32);
extern Chr *ObjRecGetLiveObject_1c4a90(Game *, s32);
extern Ex *ParamTableGetRec_1cfbc0(Game *, s32);
extern s32 ObjGetNthAttachPointPosSafe_23b0c0(Chr *, s32, s32, V4 *);
extern s32 ModelGetRootFrame_1511a0(Chr *);
extern void FrameGetWorldPos_148f30(s32, V4 *);
extern f32 VecDist_1cb420(V4 *, V4 *);
extern f32 ModelObjGetScaledRadius_23b140(Chr *);
extern Src *MapGetAreaLightSetById_1e54d0(s32, s32, s32);
extern s32 IsInBattleMode_288380(void);
extern void VecCopy_1cbe30(V4 *, V4 *);
extern void VecLerp_1cbb20(V4 *, V4 *, V4 *, f32);
extern void MtxCopy_1cbde0(V4 *, void *);
extern s32 ObjRecGetFlags_1c3d90(Game *, s32, s32);
extern void Character2LightBlendSetTarget_1aebe0(Chr *, s32, V4 *, V4 *, V4 *, V4 *, u8);
extern void DrawListAddTexLoad_1418c0(s32, s32, f32);
extern void Character2LightBlendStep_1ae820(Chr *);
extern void *ActionMgrFindById_233b50(u8 *, s32);
extern void CharaGetTintColor_213fe0(void *, V4 *);
extern f32 CharaGetTintLevel_213ff0(void *);
extern void Character2DrawTintedMaybe_1ae620(Chr *, f32, f32, f32, f32);
extern void ObjRecClearFlags_1c3dc0(Game *, s32, s32, s32);
extern f32 D_0047E500;
extern f32 D_0047E504;
extern f32 D_0047E508;
extern f32 D_0047E50C;
extern f32 D_0045B080[];
extern u8 D_004B8680[];

}

extern "C" void TaskDrawChara3_1f7ab0(void) {
    V4 col __attribute__((aligned(16)));
    s16 ids[0xE0] __attribute__((aligned(16)));
    f32 dist[0xE0] __attribute__((aligned(16)));
    V4 pos __attribute__((aligned(16)));
    V4 m0[4] __attribute__((aligned(16)));
    V4 m1[4] __attribute__((aligned(16)));
    V4 v110 __attribute__((aligned(16)));
    V4 v100 __attribute__((aligned(16)));
    V4 buf __attribute__((aligned(16)));
    s32 i3;
    s32 id;
    Chr *obj3;
    void *act;
    Game *h;
    s32 snd;
    s32 area;
    u8 *tbl;
    Cam *cam;
    s32 n;
    u8 fl;
    f32 hi2;
    f32 lo2;
    s32 i;
    Chr *obj;
    Ex *e;
    s32 idx;
    s32 lt;
    Chr *o2;
    f32 x;
    f32 a;
    f32 b;
    f32 d;
    Ex *e2;
    s32 gid;
    s32 sub;
    Src *p;
    Src *p2;
    s32 k;
    s32 fl2;
    s32 j;
    s32 m;
    f32 t;

    h = GetCurrentScene_1f5be0();
    snd = GetDrawCtx_15de80();
    GetGameData_1fede0();
    area = GetMapMgr_201a90();
    tbl = D_004B8680;
    {
        V4 *cp = (V4 *)(u32)&col;
        cp->x = D_0047E500;
        cp->y = D_0047E504;
        cp->z = D_0047E508;
        cp->w = D_0047E50C;
    }
    cam = ObjRecGetLiveObject_1c3bc0(h, h->x4344);
    if (cam != 0) {
        cam->SetCol(&col);
    }
    n = 0;
    fl = GetGameMode_1f59c0() != 11 && GetGameMode_1f59c0() != 10 && GetGameMode_1f59c0() != 9 && !ReturnZero_207f40();
    i = 0;
    lo2 = 0.25f * D_0045B080[0];
    hi2 = 1.25f * D_0045B080[0];
    for (; i < 0xE0; i++) {
        if (ObjRecIsDrawableMaybe_1c48b0(h, i) == 0) {
            continue;
        }
        if (ObjRecGetValue_1c3d30(h, 1, i) != 9) {
            continue;
        }
        obj = ObjRecGetLiveObject_1c4a90(h, i);
        if (obj == 0) {
            continue;
        }
        e = ParamTableGetRec_1cfbc0(h, i);
        if (e == 0) {
            continue;
        }
        if (ObjGetNthAttachPointPosSafe_23b0c0(obj, 0, 0, &pos) == 0) {
            FrameGetWorldPos_148f30(ModelGetRootFrame_1511a0(obj), &pos);
        }
        e->xC = VecDist_1cb420(&col, &pos);
        lt = i < 12;
        idx = i;
        if (!lt && i < 60) {
            idx = (!lt && i < 60) ? (i - 12) >> 2 : -1;
        }
        if (GetGameMode_1f59c0() != 15) {
            if (!(i < 12) && i < 60) {
                if (fl) {
                    o2 = ObjRecGetLiveObject_1c4a90(h, idx);
                    if (o2 != 0) {
                        x = o2->x448;
                        a = e->x4;
                        if (!(x <= a)) {
                            x = a;
                        }
                        obj->x448 = x;
                    }
                }
            } else if (fl) {
                x = e->x4;
                a = ModelObjGetScaledRadius_23b140(obj) + lo2;
                b = ModelObjGetScaledRadius_23b140(obj) + hi2;
                d = e->xC;
                if (d < a) {
                    x = 0.0f;
                }
                if (d < b) {
                    x = (d - a) / (b - a);
                }
                a = e->x4;
                if (!(x <= a)) {
                    x = a;
                }
                obj->x448 = x;
            }
        }
        if (obj->x448 <= 0.0f) {
            continue;
        }
        e2 = ParamTableGetRec_1cfbc0(h, idx);
        if (e2 == 0) {
            continue;
        }
        m0[0].x = 0.0f;
        m0[0].y = 1.0f;
        k = 0;
        m0[0].z = 0.0f;
        m0[0].w = 0.0f;
        m0[1].x = 0.0f;
        m0[1].y = 1.0f;
        m0[1].z = 0.0f;
        m0[1].w = 0.0f;
        m0[2].x = 0.0f;
        m0[2].y = 1.0f;
        m0[2].z = 0.0f;
        m0[2].w = 0.0f;
        m0[3].x = 0.0f;
        m0[3].y = 1.0f;
        m0[3].z = 0.0f;
        m0[3].w = 0.0f;
        m1[0].x = 0.0f;
        m1[0].y = 0.0f;
        m1[0].z = 0.0f;
        m1[0].w = 128.0f;
        m1[1].x = 0.0f;
        m1[1].y = 0.0f;
        m1[1].z = 0.0f;
        m1[1].w = 128.0f;
        m1[2].x = 0.0f;
        m1[2].y = 0.0f;
        m1[2].z = 0.0f;
        m1[2].w = 128.0f;
        m1[3].x = 0.0f;
        m1[3].y = 0.0f;
        m1[3].z = 0.0f;
        m1[3].w = 128.0f;
        v110.x = 0.0f;
        v110.y = 0.0f;
        v110.z = 0.0f;
        v110.w = 128.0f;
        v100.w = 128.0f;
        v100.x = 0.0f;
        v100.y = 0.0f;
        v100.z = 0.0f;
        gid = e2->x12;
        sub = e2->x14;
        if (GetGameMode_1f59c0() == 10 || GetGameMode_1f59c0() == 9) {
            sub = 0;
        }
        p = MapGetAreaLightSetById_1e54d0(area, gid, sub);
        if (p != 0) {
            if (sub >= 0) {
                k = sub + gid * 100;
            } else {
                k = -1;
            }
            if (IsInBattleMode_288380() != 0) {
                VecCopy_1cbe30(&v110, &p->x180);
                VecCopy_1cbe30(&v100, &p->x190);
            } else {
                p2 = MapGetAreaLightSetById_1e54d0(area, gid, 0);
                VecLerp_1cbb20(&v110, &p->x180, &p2->x180, 0.5f);
                VecLerp_1cbb20(&v100, &p->x190, &p2->x190, 0.5f);
                k += 50;
            }
            MtxCopy_1cbde0(m0, p->x30);
            MtxCopy_1cbde0(m1, p->x70);
        }
        fl2 = ObjRecGetFlags_1c3d90(h, 1, idx);
        Character2LightBlendSetTarget_1aebe0(obj, k, m0, m1, &v110, &v100, (s32)(obj->x774 > 0 && k > 0));
        if (obj->x448 < 1.0f) {
            continue;
        }
        if (fl2 & 0x1000) {
            continue;
        }
        ids[n] = i;
        dist[n] = e->xC;
        n++;
    }
    for (j = 1; j < n; j++) {
        for (m = 0; m < j; m++) {
            if (dist[m] < dist[j]) {
                t = dist[m];
                dist[m] = dist[j];
                dist[j] = t;
                t = ids[m];
                ids[m] = ids[j];
                ids[j] = t;
            }
        }
    }
    for (i3 = 0; i3 < n; i3++) {
        id = ids[i3];
        obj3 = ObjRecGetLiveObject_1c4a90(h, id);
        ParamTableGetRec_1cfbc0(h, id);
        DrawListAddTexLoad_1418c0(snd, obj3->x4DC, 1.0f);
        obj3->SetA(1.0f);
        Character2LightBlendStep_1ae820(obj3);
        lt = id < 12;
        if (!lt && id < 60) {
            act = ActionMgrFindById_233b50(tbl, (!lt && id < 60) ? (id - 12) >> 2 : -1);
        } else {
            act = ActionMgrFindById_233b50(tbl, id);
        }
        {
            u8 *p_ = (u8 *)&buf;
            u32 n_ = 16;
            if (p_ != 0) {
                while (n_ != 0) {
                    *p_ = 0;
                    n_--;
                    p_++;
                }
            }
        }
        if (act != 0) {
            CharaGetTintColor_213fe0(act, &buf);
            buf.w = CharaGetTintLevel_213ff0(act);
        }
        Character2DrawTintedMaybe_1ae620(obj3, buf.x, buf.y, buf.z, buf.w);
        ObjRecClearFlags_1c3dc0(h, 1, id, 0x40000);
    }
}
