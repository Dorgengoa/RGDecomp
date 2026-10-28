/* rgp:protos */
#line 1
#include "types.h"

extern "C" {
typedef struct V4 { f32 x, y, z, w; } __attribute__((aligned(16))) V4;
typedef struct Ent {
    u16 flags;
    u8 pad2[0xC2];
    s16 hC4;
    s16 id;
    u8 padC8[2];
    s16 state;
    u8 padCC[8];
    f32 dist;
    u8 padD8[8];
} Ent;
typedef struct Mgr {
    u8 pad0[4];
    Ent *ents;
    s16 count;
    u8 padA[2];
    Ent *list[0x80];
    s16 nlist;
    u8 pad20E[2];
    f32 range;
    u8 pad214[4];
    s16 x218;
    u8 pad21A[2];
    Ent *sel;
    s16 flags;
} Mgr;
typedef struct Obj {
    s16 id;
    u8 pad2[0x36];
    f32 x, y, z;
    u8 pad44[4];
    s32 w48;
    u8 pad4C[0xA];
    u8 b56;
} Obj;
typedef struct Iter { s32 a; s32 b; } Iter;
typedef struct Qry { s32 w[8]; } Qry;
typedef struct Ctx { u8 pad[0x4344]; s32 cam; } Ctx;
extern Ctx *GetStaticScene_1c6c70(void);
extern s32 GetGameData_1fede0(void);
extern void NpcViewCtor_41c210(Qry *, s32, s32, s32, s32);
extern void IterInit_370170(Iter *, Qry *, int, int);
extern Obj *IterNext_370040(Iter *);
extern f32 VecDistance_13d3d0(V4 *, V4 *);
extern s32 NpcObjFindByMarkId_2fb620(Mgr *, s32);
extern Ent *NpcObjTableFindFree_2fb5d0(Mgr *);
extern void NpcObjBindMark_2fbaa0(Ent *, s32);
extern void NpcObjReleaseRes_2fba00(Ent *, s32);
extern void NpcObjTableCharaLoadUpdate_2faac0(Mgr *);
extern void NpcObjUpdate_2fc450(Ent *);
}

class Cam {
public:
    u8 pad[0xC0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v39(V4 * a0) { VCM(void, (void *, V4 *), 0xA4, a0); }
    void v40(V4 * a0) { VCM(void, (void *, V4 *), 0xA8, a0); }
};

extern "C" Cam *ObjRecGetLiveObject_1c3bc0(Ctx *, s32);

extern "C" void NpcObjTableStepMaybe_2fae50(Mgr *m)
{
    s32 np;
    s32 j;
    s32 id;
    s32 si;
    s32 sj;
    Iter it __attribute__((aligned(16)));
    V4 va __attribute__((aligned(16)));
    V4 vb __attribute__((aligned(16)));
    V4 p __attribute__((aligned(16)));
    s16 ids[0x80] __attribute__((aligned(16)));
    f32 dists[0x80] __attribute__((aligned(16)));
    Qry q __attribute__((aligned(16)));
    s32 pend[4] __attribute__((aligned(16)));
    Ctx *c;
    s32 me;
    Cam *cam;
    s16 n;
    Obj *o;
    f32 d;
    Ent *e;
    bool del;
    Ent *e2;
    s32 k;
    s32 last;
    s32 *pp;
    Ent **lp;
    Ent *a;
    Ent *b;
    Ent **L;
    Ent **pi;
    Ent **pj;
    s32 i;
    s32 i4;
    Ent *e4;
    s32 i3;
    s32 found;
    Ent *e3;
    s32 j1;

    if (m->flags & 4) return;
    c = GetStaticScene_1c6c70();
    me = GetGameData_1fede0();
    cam = ObjRecGetLiveObject_1c3bc0(c, c->cam);
    cam->v39(&va);
    cam->v40(&vb);
    n = 0;
    NpcViewCtor_41c210(&q, me, -1, 1, 0);
    IterInit_370170(&it, &q, 0, 0);
    while (o = IterNext_370040(&it), o != 0) {
        if (!(o->b56 & 1)) continue;
        if (!(o->w48 & 1)) continue;
        va.w = 1.0f;
        p.x = o->x;
        p.y = o->y;
        p.z = o->z;
        p.w = 1.0f;
        d = VecDistance_13d3d0(&p, &vb);
        if (d <= m->range) {
            ids[n] = o->id;
            dists[n] = d;
            n++;
            if (n >= m->count) break;
        }
    }
    e = m->ents;
    for (me = 0; me < m->count; me++, e++) {
        if (!(e->flags & 1)) continue;
        found = 0;
        for (j1 = 0; j1 < n; j1++) {
            if (e->id == ids[j1]) {
                found = 1;
                e->dist = dists[j1];
                break;
            }
        }
        if (found) continue;
        del = true;
        if (e == m->sel && (u32)(e->state - 2) < 2) del = false;
        if (del) {
            NpcObjReleaseRes_2fba00(e, 0);
            if (e == m->sel) {
                m->x218 = 0;
                m->sel = 0;
            }
        }
    }
    np = 0;
    for (j = 0; j < n; j++) {
        id = ids[j];
        d = dists[j];
        if (NpcObjFindByMarkId_2fb620(m, id) != 0) continue;
        e2 = NpcObjTableFindFree_2fb5d0(m);
        if (e2 == 0) {
            pend[np++] = j;
            break;
        }
        NpcObjBindMark_2fbaa0(e2, id);
        e2->dist = d;
    }
    if (np > 0 && m->nlist >= m->count) {
        k = m->count - np;
        last = m->count - 1;
        if (k < 0) k = 0;
        for (pp = pend; k <= last; k++, pp++) {
            e = m->list[k];
            if (e->hC4 >= 0) continue;
            NpcObjReleaseRes_2fba00(e, 0);
            if (e == m->sel) {
                m->x218 = 0;
                m->sel = 0;
            }
            i = *pp;
            NpcObjBindMark_2fbaa0(e, ids[i]);
            e->dist = dists[i];
        }
    }
    e3 = m->ents;
    lp = m->list;
    m->nlist = 0;
    for (i3 = 0; i3 < m->count; i3++, e3++) {
        if (e3->flags & 1) {
            *lp++ = e3;
            m->nlist++;
        }
    }
    *lp = 0;
    L = m->list;
    for (si = 0; si < m->nlist; si++) {
        for (sj = si + 1; sj < m->nlist; sj++) {
            if (!(L[si]->dist <= L[sj]->dist)) {
                a = L[si];
                b = L[sj];
                L[sj] = a;
                L[si] = b;
            }
        }
    }
    NpcObjTableCharaLoadUpdate_2faac0(m);
    e4 = m->ents;
    for (i4 = 0; i4 < m->count; e4++, i4++) {
        NpcObjUpdate_2fc450(e4);
    }
}
