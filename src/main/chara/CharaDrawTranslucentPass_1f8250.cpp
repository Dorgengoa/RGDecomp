#include "types.h"

typedef unsigned __int128 u128;

struct Vec4 {
    f32 x, y, z, w;
};

struct PadC0 {
    u8 pad0[0xC0];
};

class Cam : public PadC0 {
public:
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
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual void d34();
    virtual void d35();
    virtual void d36();
    virtual void d37();
    virtual void d38();
    virtual void vA4(Vec4 *);
};

struct Pad1B0 {
    u8 pad0[0x180];
    u128 x180;
    u8 pad190[0x20];
};

class Actor : public Pad1B0 {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void v18(f32);
    virtual void d5();
    virtual void d6();
    virtual void v24();
};

struct ActorX : public Actor {
    u8 pad1C0[0x448 - 0x1C0];
    f32 x448;
};

struct Rec {
    u8 pad0[0xC];
    f32 xC;
};

struct Game {
    u8 pad0[0x4344];
    s32 x4344;
};

struct W18 {
    u8 pad0[0x18E];
    s16 x18E;
};

struct World {
    u8 pad0[0x18];
    W18 *x18;
};

extern "C" {
Game *GetCurrentScene_1f5be0(void);
void *GetDrawCtx_15de80(void);
World *GetGameData_1fede0(void);
Cam *ObjRecGetLiveObject_1c3bc0(Game *, s32);
s32 ObjRecIsDrawableMaybe_1c48b0(Game *, s32);
s32 ObjRecGetValue_1c3d30(Game *, s32, s32);
struct ActorX;
ActorX *ObjRecGetLiveObject_1c4a90(Game *, s32);
f32 VecDistSqXZ_1cb390(Vec4 *, Vec4 *);
s32 ObjRecGetFlags_1c3d90(Game *, s32, s32);
Rec *ParamTableGetRec_1cfbc0(Game *, s32);
void DrawListAddTexLoad_1418c0(void *, s32, f32);
void Character2LightBlendStep_1ae820(ActorX *);
void *ActionMgrFindById_233b50(void *, s32);
s32 EventObjMgrIsRunning_27af20(void);
void CharaGetTintColor_213fe0(void *, Vec4 *);
f32 CharaGetTintLevel_213ff0(void *);
void Character2DrawTintedMaybe_1ae620(ActorX *, f32, f32, f32, f32);
void ObjRecClearFlags_1c3dc0(Game *, s32, s32, s32);
void RefractionCaptureFrame_13ffd0(void *, s32);
void RefractionPassEndMaybe_13ffb0(void *);
s32 ObjRecHasFlags6_1c3eb0(Game *, s32, s32);
void GameSceneCBlurProcessMaybe_1cf800(Game *);
}

extern u8 D_004B8680[];
struct Tri {
    f32 a, b, c;
};
extern Vec4 D_0047E4E0 __attribute__((section(".sdata")));
extern Tri D_0047E4F0 __attribute__((section(".sdata")));

#define ZERO16(d) { u8 *p_ = (u8 *)(d); u32 n_ = 0x10; if (p_ != 0) while (n_) { *p_ = 0; n_--; p_++; } }

static inline s32 conv(s32 i) {
    if (i < 12) return -1;
    if (i >= 60) return -1;
    return (i - 12) >> 2;
}
static inline s32 conv2(s32 i, s32 lo) {
    return (!lo && i < 60) ? (i - 12) >> 2 : -1;
}

extern "C" void CharaDrawTranslucentPass_1f8250(void) {
    s32 kk;
    s32 j2;
    Game *g;
    void *snd;
    u8 *base;
    World *w;
    s32 n;
    s32 i3;
    void *h;
    s32 cur;
    s32 i;
    s32 t;
    ActorX *a;
    s32 r;
    Rec *p;
    s32 j;
    s32 k;
    f32 tf;
    s32 id;
    Cam *c;
    s32 kind;
    s32 order[4];
    s16 ids[0xE0];
    f32 dist[0xE0];
    Vec4 cpos;
    Vec4 ap;
    Vec4 col;

    g = GetCurrentScene_1f5be0();
    snd = GetDrawCtx_15de80();
    base = D_004B8680;
    w = GetGameData_1fede0();
    cpos = D_0047E4E0;
    n = 0;
    c = ObjRecGetLiveObject_1c3bc0(g, g->x4344);
    if (c != 0) c->vA4(&cpos);
    cur = w->x18->x18E;
    for (i = 0; i < 0xE0; i++) {
        if (ObjRecIsDrawableMaybe_1c48b0(g, i) == 0) continue;
        t = ObjRecGetValue_1c3d30(g, 1, i);
        if (t == 4 || t == 7 || t == 9) continue;
        a = ObjRecGetLiveObject_1c4a90(g, i);
        if (a == 0) continue;
        r = i;
        { s32 lo = i < 12; if (!lo && i < 60) r = conv2(i, lo); }
        if (cur == r && g->x4344 == 3) {
            *(u128 *)&ap = a->x180;
            if (VecDistSqXZ_1cb390(&ap, &cpos) < 1.0f) continue;
        }
        if (a->x448 <= 0.0f) continue;
        if (!(ObjRecGetFlags_1c3d90(g, 1, r) & 0x1000)) {
            if (!(a->x448 < 1.0f)) continue;
        }
        p = ParamTableGetRec_1cfbc0(g, i);
        if (p == 0) continue;
        ids[n] = i;
        dist[n] = p->xC;
        n++;
    }
    for (j = 1; j < n; j++) {
        for (k = 0; k < j; k++) {
            if (dist[k] < dist[j]) {
                tf = dist[k];
                dist[k] = dist[j];
                dist[j] = tf;
                tf = ids[k];
                ids[k] = ids[j];
                ids[j] = tf;
            }
        }
    }
    for (i3 = 0; i3 < n; i3++) {
        id = ids[i3];
        a = ObjRecGetLiveObject_1c4a90(g, id);
        ParamTableGetRec_1cfbc0(g, id);
        DrawListAddTexLoad_1418c0(snd, *(s32 *)((u8 *)a + 0x4DC), 1.0f);
        a->v18(1.0f);
        Character2LightBlendStep_1ae820(a);
        {
            s32 lo = id < 12;
            if (!lo && id < 60) {
                h = ActionMgrFindById_233b50(base, conv2(id, lo));
            } else {
                h = ActionMgrFindById_233b50(base, id);
            }
        }
        ZERO16(&col);
        if (h != 0 && EventObjMgrIsRunning_27af20() != 0) {
            CharaGetTintColor_213fe0(h, &col);
            col.w = CharaGetTintLevel_213ff0(h);
        }
        *(s32 *)((u8 *)a + 0x450) = 1;
        Character2DrawTintedMaybe_1ae620(a, col.x, col.y, col.z, col.w);
        ObjRecClearFlags_1c3dc0(g, 1, id, 0x40000);
    }
    *(Tri *)order = D_0047E4F0;
    for (kk = 0; (kind = *(s32 *)((u32)&order[kk])) >= 0; kk++) {
        kind = (s32)(u32)kind;
        if (kind == 7) RefractionCaptureFrame_13ffd0(snd, 8);
        for (j2 = 0; j2 < 0xE0; j2++) {
            if (ObjRecHasFlags6_1c3eb0(g, 1, j2) == 0) continue;
            if (kind != ObjRecGetValue_1c3d30(g, 1, j2)) continue;
            if (ObjRecIsDrawableMaybe_1c48b0(g, j2) == 0) continue;
            a = ObjRecGetLiveObject_1c4a90(g, j2);
            if (a == 0) continue;
            DrawListAddTexLoad_1418c0(snd, *(s32 *)((u8 *)a + 0x4DC), 1.0f);
            a->v18(1.0f);
            a->v24();
        }
        if (kind == 7) RefractionPassEndMaybe_13ffb0(snd);
    }
    GameSceneCBlurProcessMaybe_1cf800(g);
}
