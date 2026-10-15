#include "types.h"

typedef struct { f32 x, y, z, w; } V4;
typedef struct { u8 pad0[0x4A]; u16 id; u8 pad4C[0x14]; } Hit;
typedef struct { s32 f0; s32 f4; s32 f8; } Res;
typedef struct {
    u8 pad0[4];
    s16 f4;
    u8 pad6[0xA];
    char *f10;
    char *f14;
    char *f18;
    char *f1C[3];
    s32 f28;
    s32 f2C;
    s32 f30;
    s32 f34;
    s32 f38;
    s32 f3C;
    s32 f40[3];
    s32 f4C;
    s32 f50;
    s32 f54;
} Mdl;
typedef struct { u8 pad0[4]; Mdl *f4; u8 pad8[4]; s16 fC; } Ent;
typedef struct { u8 pad0[0x30]; V4 f30; u8 pad40[0x150]; V4 f190; } Pt;
typedef struct { u8 pad0[0x78]; s32 f78; } Sub;
typedef struct { u8 pad0[8]; Sub *f8; } Game;
typedef struct {
    f32 x;
    f32 y;
    f32 z;
    u8 padC[0x14];
    s16 f20;
    s16 f22;
    s16 f24;
    s16 f26;
    s16 f28;
    s16 f2A;
    s16 f2C;
    u8 pad2E[2];
    s32 f30;
    s16 f34;
    u8 pad36[2];
    V4 f38;
    V4 f48;
    f32 f58;
    f32 f5C;
    f32 f60;
    f32 f64;
    Ent *f68;
    u8 pad6C[4];
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
    u8 b3 : 1;
    u8 b4 : 1;
    u8 b5 : 1;
    u8 b6 : 2;
} Obj;

extern "C" {
extern char *strcpy(char *, const char *);
extern char *strcat(char *, const char *);
extern f32 Sinf_128fd0(f32);
extern s32 FrameFindByName_149ed0(s32, char *);
extern s32 ModelGetRootFrame_1511a0(s32);
extern s32 MeshRaycastWrapper_16f610(Hit *, s32, V4 *, V4 *, s32 *, s32, s32);
extern s32 SoundNextPlayHandle_1b81c0(void);
extern void SoundPlayScaledVolume_1b9520(s32, s32, s32, f32);
extern Res *MapGetAreaTreasureBoxSlotById_1e25e0(s32, s32, s32);
extern s32 MapFindBlockAtPos_1e3a00(s32, Obj *, f32);
extern Pt *MapGetAreaLightSetAtPos_1e5490(s32, Obj *, s32);
extern s32 MapDataIsLoaded_1e79d0(s32);
extern Game *GetGameData_1fede0(void);
extern s32 MapEvCollectCollPolysMaybe_1ff270(Hit *, s32, V4 *, s32);
extern s32 GetMapMgr_201a90(void);
extern s32 SceneSoundGetSlot0HandleCur_207df0(void);
extern s32 GetTreasureBoxPool_3389b0(void);
extern void TreasureBoxPoolSetCollEnabled_338be0(s32, s32);
extern u8 TreasureBoxIsOpened_33a240(Obj *);
extern Ent *GroupGetRecordById_426dc0(s32, s32, s32);
extern f32 D_0047D904;
extern f32 D_0047DA0C;
extern f32 D_0047DC58;
extern f32 D_0047DC5C;
extern f32 D_0047DC60;
extern f32 D_0047DC64;
extern f32 D_0047DC68;
extern f32 D_0047DC6C;
extern f32 D_0047DC70;
extern f32 D_0047DC74;
extern f32 D_0047DC78;
extern f32 D_0047DC7C;
}

static inline f32 Sq(f32 t, f32 t0, f32 s) {
    f32 d = t - t0;
    return d * (s * d);
}

extern "C" s32 TreasureBoxUpdate_3398c0(Obj *o) {
    char nA[0x20];
    char nB[0x20];
    V4 box[2];
    Hit hits[0x40];
    V4 a;
    V4 b;
    s32 c[4];
    Game *g;
    s32 w;
    Mdl *m;
    Res *res;
    s32 obj;
    s32 i;
    s32 lib;
    s32 lock;
    s32 n;
    s32 idx;
    s32 id;
    Pt *pt;
    s32 st;
    s32 mode;
    s32 busy;
    bool big;
    s16 k;
    f32 t;
    f32 r0;
    f32 r1;
    f32 r2;
    f32 r3;
    f32 r4;
    f32 d;
    s32 snd;

    if (o->f68 == 0) {
        return 0;
    }
    if (!o->b0 && o->f26 == 0) {
        return 0;
    }
    g = GetGameData_1fede0();
    if (g == 0) {
        return 0;
    }
    o->f68 = GroupGetRecordById_426dc0(g->f8->f78, o->f20, o->f22);
    if (o->f68 == 0) {
        return 0;
    }
    w = GetMapMgr_201a90();
    if (w == 0) {
        return 0;
    }
    m = o->f68->f4;
    if (m == 0) {
        return 0;
    }
    if (m->f28 == 0) {
        res = MapGetAreaTreasureBoxSlotById_1e25e0(w, o->f24, m->f4);
        if (res == 0) {
            return 0;
        }
        m->f28 = res->f0;
        if (m->f28 == 0) {
            return 0;
        }
        m->f30 = res->f8;
        m->f2C = m->f28 + 0x270;
        obj = ModelGetRootFrame_1511a0(m->f28);
        m->f34 = obj;
        if (obj != 0) {
            m->f38 = FrameFindByName_149ed0(obj, m->f10);
            m->f3C = FrameFindByName_149ed0(obj, m->f14);
            for (i = 0; i < 3; i++) {
                m->f40[i] = FrameFindByName_149ed0(obj, m->f1C[i]);
            }
        }
        lib = res->f4;
        m->f4C = lib;
        if (lib != 0) {
            if (m->f10 != 0) {
                strcpy(nA, m->f10);
                if (m->f18 != 0) {
                    strcat(nA, m->f18);
                }
                m->f50 = FrameFindByName_149ed0(lib, nA);
            }
            if (m->f14 != 0) {
                strcpy(nB, m->f14);
                if (m->f18 != 0) {
                    strcat(nB, m->f18);
                }
                m->f54 = FrameFindByName_149ed0(lib, nB);
            }
        }
    }
    if (o->f30 == 0) {
        o->f30 = MapFindBlockAtPos_1e3a00(w, o, 0.0f);
    }
    if (o->f30 != 0 && MapDataIsLoaded_1e79d0(o->f30) != 0 && o->f34 < 0 && o->f34 != -999) {
        lock = GetTreasureBoxPool_3389b0();
        if (lock != 0) {
            TreasureBoxPoolSetCollEnabled_338be0(lock, 0);
        }
        o->f34 = -999;
        box[0].x = o->x + 20.0f;
        box[0].y = o->y + 20.0f;
        box[0].z = o->z + 20.0f;
        box[0].w = 1.0f;
        box[1].x = o->x - 20.0f;
        box[1].y = o->y - 20.0f;
        box[1].z = o->z - 20.0f;
        box[1].w = 1.0f;
        n = MapEvCollectCollPolysMaybe_1ff270(hits, 0x40, box, -1);
        if (n > 0) {
            a.x = o->x;
            a.y = o->y + 20.0f;
            a.z = o->z;
            a.w = 1.0f;
            b.x = o->x;
            b.y = o->y - 20.0f;
            b.z = o->z;
            b.w = 1.0f;
            c[0] = 0;
            c[1] = 0;
            c[2] = 0;
            c[3] = 0;
            idx = MeshRaycastWrapper_16f610(hits, n, &a, &b, c, 1, -1);
            if (idx >= 0) {
                id = hits[idx].id;
                if (id >= 0) {
                    pt = MapGetAreaLightSetAtPos_1e5490(w, o, id);
                    if (pt != 0) {
                        o->f34 = id;
                        o->f38 = pt->f30;
                        o->f48 = pt->f190;
                    }
                }
            }
        }
        if (lock != 0) {
            TreasureBoxPoolSetCollEnabled_338be0(lock, 1);
        }
    }
    k = o->f26;
    o->f58 = 1.0f;
    st = k & 0x18;
    mode = k & 3;
    if (st == 8) {
        if (o->f2C > 0) {
            o->f58 = D_0047D904 * (15.0f - (f32)o->f2C);
            o->f2C--;
        }
    } else if (st == 0x10) {
        if (o->f2C > 0) {
            o->f58 = D_0047D904 * (f32)o->f2C;
            o->f2C--;
        }
    }
    if (o->f2C <= 0) {
        o->f2C = 0;
        o->f26 &= ~0x18;
    }
    if (++o->f2A >= 300.0f) {
        o->f2A = 0;
    }
    busy = TreasureBoxIsOpened_33a240(o);
    k = o->f68->fC;
    big = 0;
    if (k == 1 || k == 2 || k == 3 || k == 0xB) {
        big = 1;
    }
    if (mode == 1) {
        r0 = 4.5f;
        r1 = 19.5f;
        if (!big) {
            r0 = 0.0f;
            r1 = r0;
        }
        r2 = 16.5f + r1;
        r3 = 16.5f + r2;
        r4 = 60.0f + r3;
        snd = -1;
        if (big && o->f28 == 0) {
            snd = 0x1F;
        }
        if (o->f28 == (s32)r1) {
            snd = 0x21;
        }
        if (snd != -1) {
            SoundPlayScaledVolume_1b9520(SceneSoundGetSlot0HandleCur_207df0(), snd, SoundNextPlayHandle_1b81c0(), 1.0f);
        }
        t = o->f28;
        if (t <= r0) {
            o->f5C = t * t * (D_0047DC58 / (r0 * r0));
            o->f28++;
        } else if (t <= r1) {
            o->f5C = D_0047DC58;
            o->f28++;
        } else if (t <= r2) {
            d = t - r1;
            o->f5C = D_0047DC58 + D_0047DC5C * (d * d);
            o->f28++;
        } else if (t <= r3) {
            d = t - r2;
            o->f5C = D_0047DC64 + (1.0f - d / 16.5f) * (D_0047DC58 * Sinf_128fd0(D_0047DC60 * d));
            o->f28++;
        } else if (t <= r4) {
            o->f5C = D_0047DC64;
            o->f28++;
        } else {
            o->f26 &= ~3;
        }
    } else if (mode == 2) {
        t = o->f28;
        if (t <= 15.0f) {
            t = Sq(t, 0.0f, 1.0f);
            o->f5C = D_0047DC64 + t * D_0047DC68;
            o->f28++;
        } else if (t <= 30.0f) {
            d = t - 15.0f;
            o->f5C = D_0047DC6C + (1.0f - d / 15.0f) * (D_0047DC74 * Sinf_128fd0(d * D_0047DC70));
            o->f28++;
        } else {
            o->f5C = D_0047DC6C;
            o->f26 &= ~3;
        }
    } else if (busy) {
        o->f5C = D_0047DC6C;
    } else if (o->b5) {
        o->f5C = D_0047DC64;
    } else {
        o->f5C = 0.0f;
    }
    o->f60 = 0.0f;
    if (busy == 0) {
        if (mode == 1) {
            t = o->f28;
            if (t < 9.0f) {
                o->f60 = 1.0f - D_0047DC78 * t;
            } else {
                o->f60 = 0.0f;
            }
        } else if (mode == 2) {
            o->f60 = 0.0f;
        } else if (o->b5) {
            o->f60 = 0.0f;
        } else {
            o->f60 = 1.0f;
        }
    } else {
        o->f60 = 0.0f;
    }
    o->f64 = 0.0f;
    t = o->f2A;
    if (t < 150.0f) {
        o->f64 = D_0047DA0C + D_0047DC7C * t;
    } else {
        t = 300.0f - t;
        o->f64 = D_0047DA0C + D_0047DC7C * t;
    }
    return 0;
}
