#include "types.h"


struct V3 { f32 x, y, z; };
struct St { f32 f; s32 i; };

struct ObjBase {
    u8 p0[0x32];
    s16 h32;
    u8 p1[0x68 - 0x34];
};
struct Node;
class Obj : public ObjBase {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5(f32);
    u8 p2[0x94 - 0x6C];
    Node *nodes;
    u8 p3[0x114 - 0x98];
    u8 sub[0x2C];
    s32 flag;
};
struct Node {
    Node *next;
    u8 p0[0xC];
    Obj *o;
};
struct Box {
    f32 mx[3];
    u8 pC[4];
    f32 mn[3];
    u8 p1C[4];
    s32 used;
    s32 mode;
    Node *nodes;
    u8 p2C[4];
};
struct Grp {
    s32 a;
    s32 b;
    s32 c;
    Node *nodes;
};
struct Pair {
    s32 n;
    Obj **objs;
};
struct Ent {
    s32 on;
    u8 p4[0xBC];
};
struct Self {
    u8 p0[0x2A4];
    Node *list;
    s32 ngr;
    Grp gr[37];
    u8 p1[8];
    Pair tbl[10];
    s32 f554;
    u8 p2[8];
    u8 s560[0x20];
    s32 cnt[3];
    Obj **lst[3];
    s32 nbox;
    u8 p3[4];
    Box box[24];
    s32 nA;
    u8 p4[0xC];
    Ent ent[16];
    u8 p5[8];
    u8 f1638;
    u8 p6[0x1664 - 0x1639];
    u8 s1664[0x14];
    s32 f1678;
};

extern "C" {
s32 BoundsInViewStub_15cd10(u8 *);
u8 *GetDrawCtxCamera_15de60();
void ClothWriteMeshVerts_1850f0(Obj *);
void FadeSnap_186d80(u8 *, s16);
f32 TimeOfDayGetHour_18d920(Self *);
void FuncDataTableUpdateTimeWindow_190000(u8 *, s32, St *);
void FuncDataTableUpdateTimeWindow_190110(u8 *, s32, St *);
s32 NodeObjIsInViewUnoccludedMaybe_194100(Obj *, Ent *, s32);
s32 NodeObjIsInView_194200(Obj *);
void OcclusionPlaneBuildFrustumMaybe_1971d0(Ent *, u8 *);
extern f32 D_0047E060;
extern f32 D_0047E064;
extern f32 D_0047E068;
}
#define ISEMPTY(g) ((u8)(((g)->a != 0) ^ 1))
extern "C" {
s32 MapAreaModelUpdateVisibility_1886b0(Self *self, f32 *pos);
}

s32 MapAreaModelUpdateVisibility_1886b0(Self *self, f32 *pos) {
    s32 i; Box *bx; s32 i2; Grp *gr; s32 i3; s32 j; s32 k; s32 m; s32 q; s32 cnt; s32 n; s32 lim; s32 r; u8 *t; Obj **lst; s32 *pc; Pair *pr; Obj **objs; Obj *o; Obj *o2; Obj *o3; Node *nd; Node *nd3; Node *n2; Node *n4; Node *n5; St st; V3 arr; Ent *e; u8 *ep; s32 *ip; u8 *ap;

    if (self->f554 != 0 && BoundsInViewStub_15cd10(self->s560) == 0) {
        for (i = 0; i < 3; i++) {
            self->cnt[i] = 0;
        }
        return 0;
    }
    cnt = 0;
    t = GetDrawCtxCamera_15de60();
    for (k = 0; k < self->nA; k++) {
        e = &self->ent[k];
        if (self->ent[k].on != 0) {
            OcclusionPlaneBuildFrustumMaybe_1971d0(e, t + 0xB0);
            cnt++;
        }
    }
    st.f = 0.0f;
    st.f = TimeOfDayGetHour_18d920(self);
    st.i = self->f1678;
    FuncDataTableUpdateTimeWindow_190000(self->s1664, 2, &st);
    FuncDataTableUpdateTimeWindow_190000(self->s1664, 0xA, &st);
    FuncDataTableUpdateTimeWindow_190000(self->s1664, 3, &st);
    FuncDataTableUpdateTimeWindow_190110(self->s1664, 4, &st);
    FuncDataTableUpdateTimeWindow_190000(self->s1664, 1, &st);
    arr.x = D_0047E060;
    arr.y = D_0047E064;
    arr.z = D_0047E068;
    for (m = 0; m < 3; m++) {
        lst = self->lst[m];
        pc = &self->cnt[m];
        self->cnt[m] = 0;
        if (lst == 0) {
            return 0;
        }
        ip = (s32 *)((u32)&((s32 *)&arr)[m]);
        pr = &self->tbl[*ip];
        objs = pr->objs;
        n = pr->n;
        for (i = 0; i < n; i++) {
            o = objs[i];
            if (o != 0) {
                o->flag = 1;
            }
        }
        bx = self->box;
        for (i2 = 0; i2 < self->nbox; i2++, bx++) {
            if (bx->used != 0) {
                if (bx->mode == 0) {
                    if (pos[0] < bx->mn[0]) continue;
                    if (pos[1] < bx->mn[1]) continue;
                    if (pos[2] < bx->mn[2]) continue;
                    if (!(pos[0] <= bx->mx[0])) continue;
                    if (!(pos[1] <= bx->mx[1])) continue;
                    if (!(pos[2] <= bx->mx[2])) continue;
                } else {
                    if (!(pos[0] <= bx->mn[0]) && !(pos[1] <= bx->mn[1]) && !(pos[2] <= bx->mn[2]) &&
                        pos[0] < bx->mx[0] && pos[1] < bx->mx[1] && pos[2] < bx->mx[2]) continue;
                }
                for (nd = bx->nodes; nd != 0; nd = nd->next) {
                    if (nd->o != 0) {
                        nd->o->flag = 0;
                    }
                }
            }
        }
        lim = self->ngr;
        gr = self->gr;
        for (i3 = 0; i3 < lim; i3++, gr++) {
            if (ISEMPTY(gr)) continue;
            if (gr->c != 0 || gr->b != 0) {
                for (nd3 = gr->nodes; nd3 != 0; nd3 = nd3->next) {
                    if (nd3->o != 0) {
                        nd3->o->flag = 0;
                    }
                }
                gr->c = 0;
            }
        }
        for (j = 0; j < n; j++) {
            o2 = objs[j];
            if (o2 == 0) continue;
            if (o2->h32 == 0) continue;
            if (o2->flag == 0) {
                r = 0;
            } else if (cnt > 0) {
                r = NodeObjIsInViewUnoccludedMaybe_194100(o2, self->ent, self->nA);
            } else {
                r = NodeObjIsInView_194200(o2);
            }
            if (r != 0) {
                lst[*pc] = o2;
                *pc = *pc + 1;
                o2->v5(1.0f);
                FuncDataTableUpdateTimeWindow_190000(o2->sub, 2, &st);
                FuncDataTableUpdateTimeWindow_190000(o2->sub, 3, &st);
                FuncDataTableUpdateTimeWindow_190000(o2->sub, 1, &st);
                FuncDataTableUpdateTimeWindow_190110(o2->sub, 4, &st);
            } else {
                for (n2 = o2->nodes; n2 != 0; n2 = n2->next) {
                    FadeSnap_186d80((u8 *)n2->o + 0x3C, n2->o->h32);
                }
            }
        }
        if (self->f1638 != 0) {
            for (q = 0; q < *pc; q++) {
                o3 = lst[q];
                if (o3 == 0) continue;
                FadeSnap_186d80((u8 *)o3 + 0x3C, o3->h32);
                for (n4 = o3->nodes; n4 != 0; n4 = n4->next) {
                    FadeSnap_186d80((u8 *)n4->o + 0x3C, n4->o->h32);
                }
                o3->v5(1.0f);
            }
        }
    }
    self->f1638 = 0;
    for (n5 = self->list; n5 != 0; n5 = n5->next) {
        if (n5->o != 0) {
            ClothWriteMeshVerts_1850f0(n5->o);
        }
    }
    return 1;
}
