#include "types.h"
typedef unsigned __int128 u128;

typedef struct {
    f32 x, y, z, w;
} Vec4;

struct Node {
    s8 _0[0xC];
    Node *next;
};

struct Anim {
    s8 _0[8];
    Node *nodes;
    s8 _c[0x22];
    s16 x2E;
};

struct ActorBase {
    u8 _0[0x180];
    Vec4 pos;
    u8 _190[0x20];
};

class ActorV : public ActorBase {
public:
    virtual void p00(); virtual void p01(); virtual void p02(); virtual void p03();
    virtual void p04(); virtual void p05(); virtual void p06(); virtual void p07();
    virtual void p08(); virtual void p09(); virtual void p10(); virtual void p11();
    virtual void p12(); virtual void p13(); virtual void p14();
    virtual void v44(f32);
    u8 _1b4[0x1F0 - 0x1B4];
    u8 x1F0[0x790 - 0x1F0];
    s16 *x790;
    Anim *x794;
    f32 x798;
    s32 x79C;
};

struct CamBase {
    u8 d[0xC0];
};

class CamV : public CamBase {
public:
    virtual void p00(); virtual void p01(); virtual void p02(); virtual void p03();
    virtual void p04(); virtual void p05(); virtual void p06(); virtual void p07();
    virtual void p08(); virtual void p09(); virtual void p10(); virtual void p11();
    virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15();
    virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19();
    virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23();
    virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27();
    virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31();
    virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35();
    virtual void p36(); virtual void p37(); virtual void p38();
    virtual void vA4(Vec4 *);
};

struct Tgt {
    s8 _0[0x10];
    Vec4 pos;
    s32 x20;
    f32 x24;
    f32 x28;
    u8 x2C;
    u8 x2D;
};

struct Hit {
    u8 d[0x60];
};


#define A(o, off, T) (*(T *)((u8 *)(o) + (off)))

extern "C" {
void FrameTreeSetAlpha_1493d0(Node *, f32);
s32 MeshRaycastWrapper_16f610(Hit *, s32, Vec4 *, Vec4 *, Vec4 *, s32, s32);
s32 MotionListIsFinished_171d90(void *, s32);
void ModelObjPlayMotionByName_1867a0(ActorV *, void *, s32);
CamV *ObjRecGetLiveObject_1c3bc0(u8 *, s32);
u8 *ObjRecGetLiveObject_1c4a90(u8 *, s32);
f32 VecDistSqXZ_1cb390(Vec4 *, Vec4 *);
f32 VecDist_1cb420(Vec4 *, Vec4 *);
void VecCopy_1cbe30(Vec4 *, Vec4 *);
s32 CollTriGetAttr_1ce5b0(Hit *);
s32 MapDataCollectCollTrisMaybe_1e6c80(s32, Hit *, s32, Vec4 *);
u8 *GetCurrentScene_1f5be0(void);
u8 *GetGameData_1fede0(void);
s32 IsInBattle_288420(void);
s32 PartyGetMemberId_3c2490(s32, s32);
s32 SavePointIsActivated_426510(s16 *);
extern f32 D_0045B078[];
extern f32 D_0045B080[];
extern u8 D_0045B448[];
extern u8 D_0045B468[];
void MapEntryUpdateMaybe_1e0cd0(ActorV *self, Tgt *tgt, s32 map);
}

void MapEntryUpdateMaybe_1e0cd0(ActorV *self, Tgt *tgt, s32 map) {
    Vec4 c;
    Vec4 d;
    Vec4 e;
    Vec4 box[2];
    Hit hits[0x100];
    Vec4 p;
    Vec4 q;
    Vec4 w;
    Vec4 s;
    s16 *m;

    m = self->x790;
    if (m == 0) {
        return;
    }
    if (!(*(s32 *)((u8 *)m + 0x40) & 1)) {
        return;
    }
    if (self->x79C < 0 && map != 0) {
        f32 h = 0.5f * D_0045B080[0];
        f32 v = 2.0f * D_0045B080[0];
        s32 n;
        s32 idx;
        *(u128 *)&c = *(u128 *)&self->pos;
        VecCopy_1cbe30(&d, &c);
        box[0].x = c.x + h;
        box[0].y = c.y + v;
        box[0].z = c.z + h;
        box[0].w = 1.0f;
        box[1].x = c.x - h;
        box[1].y = c.y - v;
        box[1].z = c.z - h;
        box[1].w = 1.0f;
        d.y -= v;
        c.y += v;
        n = MapDataCollectCollTrisMaybe_1e6c80(map, hits, 0x100, box);
        idx = MeshRaycastWrapper_16f610(hits, n, &c, &d, &e, 1, -1);
        if (idx >= 0) {
            self->x79C = CollTriGetAttr_1ce5b0(&hits[idx]);
        }
    }
    if (IsInBattle_288420()) {
        self->x798 -= 1.0f / (0.5f * D_0045B078[0]);
        f32 t = self->x798;
        if (t < 0.0f) {
            self->x798 = 0.0f;
        }
    } else {
        bool near;
        *(u128 *)&p = *(u128 *)&self->pos;
        near = false;
        if (!(self->x798 < 0.375f)) {
            if (tgt->x20 != *self->x790) {
                u8 *a = GetGameData_1fede0();
                u8 *b = GetCurrentScene_1f5be0();
                s32 i = 0;
                f32 rng = 10.0f * D_0045B080[0];
                f32 r2 = D_0045B080[0] * D_0045B080[0];
                for (; i < 3; i++) {
                    u8 *o = ObjRecGetLiveObject_1c4a90(b, PartyGetMemberId_3c2490(*(s32 *)(a + 0x18), i));
                    if (o == 0) {
                        continue;
                    }
                    *(u128 *)&q = *(u128 *)(o + 0x180);
                    if (q.y < p.y - 1.0f) {
                        continue;
                    }
                    if (!(q.y <= p.y + rng)) {
                        continue;
                    }
                    if (VecDistSqXZ_1cb390(&q, &p) <= r2) {
                        near = true;
                        break;
                    }
                }
            }
        }
        if (near) {
            self->x798 -= 1.0f / (0.5f * D_0045B078[0]);
            f32 t = self->x798;
            if (t < 0.375f) {
                self->x798 = 0.375f;
            }
        } else {
            self->x798 += 1.0f / (0.5f * D_0045B078[0]);
            f32 t = self->x798;
            if (!(t <= 1.0f)) {
                self->x798 = 1.0f;
            }
        }
        {
            u8 *g = GetCurrentScene_1f5be0();
            CamV *cam = ObjRecGetLiveObject_1c3bc0(g, *(s32 *)(g + 0x4344));
            if (cam != 0) {
                f32 lo;
                f32 hi;
                f32 dd;
                cam->vA4(&w);
                w.y -= D_0045B080[0];
                lo = 1.5f * D_0045B080[0];
                hi = 2.5f * D_0045B080[0];
                dd = VecDist_1cb420(&w, &p);
                if (dd < hi) {
                    if (dd < lo) {
                        *(s32 *)&self->x798 = 0;
                    } else {
                        self->x798 = (dd - lo) / (hi - lo);
                    }
                }
            }
        }
    }
    if (SavePointIsActivated_426510(self->x790)) {
        if (MotionListIsFinished_171d90(self->x1F0, -1)) {
            if (*self->x790 == tgt->x20) {
                ModelObjPlayMotionByName_1867a0(self, D_0045B468, 4);
            } else {
                ModelObjPlayMotionByName_1867a0(self, D_0045B448, 4);
            }
        }
    }
    if (tgt->x2C == 0) {
        f32 dy;
        *(u128 *)&s = *(u128 *)&self->pos;
        f32 lim;
        dy = s.y - tgt->pos.y;
        lim = D_0045B080[0];
        if (dy < 0.0f) {
            dy = -dy;
        }
        if (dy < 6.0f * lim) {
            f32 r = tgt->x28;
            if (VecDistSqXZ_1cb390(&s, &tgt->pos) < r * r) {
                tgt->x2C = 1;
            }
        }
    }
    self->v44(tgt->x24);
    {
        Anim *an = self->x794;
        f32 k;
        Node *nd;
        if (an == 0) {
            return;
        }
        k = self->x798 * ((f32)an->x2E / 16384.0f);
        for (nd = an->nodes; nd != 0; nd = nd->next) {
            FrameTreeSetAlpha_1493d0(nd, k);
        }
        if (!(k <= 0.0f) && k < 1.0f) {
            tgt->x2D = 1;
        }
    }
}
