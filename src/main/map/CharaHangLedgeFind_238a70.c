#pragma optimization_level 3
#include "types.h"

typedef unsigned __int128 u128;
typedef struct { f32 x, y, z, w; } __attribute__((aligned(16))) V4;
typedef struct { V4 r[4]; } M4;

typedef struct {
    V4 v[3];
    V4 n;
    u8 pad40[6];
    s16 flags;
    u8 pad48[0x18];
} Tri;

typedef struct {
    V4 v[7];
    f32 x, y, z;
    s32 flags;
} Out;

typedef struct {
    u8 pad0[0x180];
    V4 pos;
    V4 rot;
    u8 pad1A0[0x4C8 - 0x1A0];
    f32 m4C8;
} Obj;

typedef struct { V4 *a; V4 *b; s32 pad[2]; } Edge;
typedef struct { s32 v[3][2]; } Idx;
typedef struct { s8 v[3][2]; } Pr;

extern s32 D_0044BAB0[];
extern s8 D_0047E780[6];
typedef struct { f32 x, y, z, w; } V4u;
extern V4u D_0047E750 __attribute__((section(".sdata")));
extern V4u D_0047E760 __attribute__((section(".sdata")));
extern V4u D_0047E770 __attribute__((section(".sdata")));
extern V4u D_0047E790 __attribute__((section(".sdata")));
extern V4u D_0047E7A0 __attribute__((section(".sdata")));

typedef struct {
    V4 *a;
    V4 *b;
    u8 pad8[8];
    V4 n;
    f32 d;
    u8 pad24[0xC];
} Cand;

extern s32 ModelFindFrameIndexByName_151220(Obj *, s32);
extern void *ModelGetFrame_1511f0(Obj *, s32);
extern void FrameGetWorldPos_148f30(void *, V4 *);
extern s32 IsInBattle_288420(void);
extern s32 CollRaycastNearestFiltered_1c8500(Tri *, s32, s32, V4 *, V4 *, s32 *, f32, f32);
extern void ClosestPointOnSegmentXZ_1c9e60(V4 *, V4 *, V4 *, V4 *);
extern void MatRotY_1cb200(M4 *, f32);
extern f32 VecDistSqXZ_1cb390(V4 *, V4 *);
extern f32 VecDistSq_1cb3c0(V4 *, V4 *);
extern f32 VecLengthXZ_1cb490(V4 *);
extern void VecScaleToLength_1cb510(V4 *, V4 *, f32);
extern void MatMulPoint_1cb8e0(V4 *, M4 *, V4 *);
extern void VecNegate_1cb9a0(V4 *, V4 *);
extern void VecSubCross_1cb9c0(V4 *, V4 *, V4 *, V4 *);
extern void VecCross_1cb9f0(V4 *, V4 *, V4 *);
extern f32 VecDot3_1cba90(V4 *, V4 *);
extern void VecNormalizeXZ_1cbb50(V4 *, V4 *);
extern void VecScale_1cbca0(V4 *, V4 *, f32);
extern void VecSub_1cbd00(V4 *, V4 *, V4 *);
extern void VecAdd3_1cbd60(V4 *, V4 *, V4 *, V4 *);
extern void VecAdd_1cbdc0(V4 *, V4 *, V4 *);
extern void VecCopy_1cbe30(V4 *, V4 *);
extern f32 sqrtf(f32);

extern f32 D_0045B080[];
extern f32 D_0047D2CC;
extern f32 D_0047D5D0;
extern f32 D_0047DA74;
extern f32 D_0047DAC8;
extern f32 D_0047DADC;
extern f32 D_0047DB14;
extern f32 D_0047DB28;
extern f32 D_0047DB2C;

static inline f32 Fabs(f32 x)
{
    return x < 0.0f ? -x : x;
}

static inline void clear(u8 *q, u32 n)
{
    if (q) {
        for (; n != 0; n--) {
            *q++ = 0;
        }
    }
}

static inline u8 GetPos(Obj *o, s32 id, V4 *out)
{
    void *b;
    if (o == NULL || id == 0) {
        return 0;
    }
    b = ModelGetFrame_1511f0(o, ModelFindFrameIndexByName_151220(o, id));
    if (b == NULL) {
        return 0;
    }
    FrameGetWorldPos_148f30(b, out);
    return 1;
}

static inline s32 Bad(Out *o)
{
    return (o->flags & 0x80000000) != 0;
}
static inline s32 Ok(Out *o)
{
    return !Bad(o);
}

void CharaHangLedgeFind_238a70(Out *out, Obj *obj, Tri *tris, s32 cnt, s32 mask, s32 id, s32 mode, f32 rad, f32 hgt)
{
    s32 res;
    Pr pr;
    V4 base;
    V4 pos;
    V4 rot;
    M4 mat;
    V4 off1;
    V4 off2;
    Idx idx;
    Cand cand[6];
    V4 bestp;
    V4 tn;
    Edge e;
    V4 mid;
    V4 un;
    V4 dir;
    Edge e2;
    V4 nrm;
    V4 hit;
    V4 side;
    V4 ev;
    V4 up;
    V4 va;
    V4 vb;
    V4 vd;
    s32 m;
    s32 n;
    s32 best;
    Tri *t;
    Tri *u;
    V4 *q;
    V4 *a;
    V4 *nn;
    s32 worst;
    s32 i;
    s32 j;
    s32 k;
    s32 kind;
    V4 *p;
    f32 mx;
    f32 dy;
    f32 r2sq;
    f32 h;
    f32 len2;
    f32 lim;
    f32 f;
    f32 r;
    f32 half;
    f32 d;
    f32 radsq;
    f32 c;
    f32 r2;
    f32 ny;

    out->flags = 0x80000000;
    if (obj == NULL || tris == NULL || cnt <= 0) {
        return;
    }
    base = obj->pos;
    *(V4u *)&pos = D_0047E750;
    pos.x = out->x;
    pos.y = out->y;
    pos.z = out->z;
    if (id != 0) {
        if (!GetPos(obj, id, &pos)) {
            return;
        }
    } else {
        rot = obj->rot;
        MatRotY_1cb200(&mat, rot.y);
        VecCopy_1cbe30(&mat.r[3], &base);
        if (mode != 0) {
            mat.r[3].y = hgt;
            *(V4u *)&off1 = D_0047E760;
            off1.y = 0.5f * D_0045B080[0];
            off1.z = 0.5f * D_0045B080[0];
            MatMulPoint_1cb8e0(&pos, &mat, &off1);
        } else {
            *(V4u *)&off2 = D_0047E770;
            off2.y = 2.5f * D_0045B080[0];
            off2.z = 0.5f * D_0045B080[0];
            MatMulPoint_1cb8e0(&pos, &mat, &off2);
        }
    }
    out->x = pos.x;
    out->y = pos.y;
    out->z = pos.z;
    if (IsInBattle_288420() == 0) {
        mask |= 2;
    }
    idx = *(Idx *)D_0044BAB0;
    n = 0;
    best = 0;
    rad = rad * 2.0f;
    worst = 0;
    r2 = 2.0f * rad;
        r2sq = r2 * r2;
    radsq = rad * rad;
    for (t = tris + 1, i = 1; i < cnt; i++, t++) {
        if (!(t->flags & 0x80)) {
            continue;
        }
        kind = -1;
        ny = t->n.y;
        if (0.75f <= ny && ny <= 1.0f) {
            kind = 0;
        } else if (-0.5f <= ny && ny <= D_0047DA74) {
            kind = 1;
        }
        if (kind < 0) {
            continue;
        }
        VecAdd3_1cbd60(&tn, &t->v[0], &t->v[1], &t->v[2]);
        for (k = 0; k < 3; k++) {
            clear((u8 *)&e, 8);
            e.a = &t->v[idx.v[k][0]];
            e.b = &t->v[idx.v[k][1]];
            if (VecDistSqXZ_1cb390(e.a, e.b) < radsq) {
                continue;
            }
            dy = e.a->y - e.b->y;
            len2 = VecDistSq_1cb3c0(e.a, e.b);
            dy = Fabs(dy);
            if (!(dy <= 5.0f)) {
                c = sqrtf(VecDistSqXZ_1cb390(e.a, e.b) / len2);
                if (c < 0.75f || 1.0f < c) {
                    continue;
                }
            }
            half = sqrtf(len2) / 2.0f;
            VecAdd_1cbdc0(&mid, e.a, e.b);
            VecScale_1cbca0(&mid, &mid, 0.5f);
            if (!(VecDistSq_1cb3c0(&mid, &pos) <= (r2 + half) * (r2 + half))) {
                continue;
            }
            for (j = 0, u = tris; j < i; j++, u++) {
                if (!(u->flags & 0x80)) {
                    continue;
                }
                VecAdd3_1cbd60(&un, &u->v[0], &u->v[1], &u->v[2]);
                if (kind == 0) {
                    if (!(un.y < tn.y)) {
                        continue;
                    }
                    if (u->n.y < -0.5f || D_0047DA74 < u->n.y) {
                        continue;
                    }
                    dir.y = 0.0f;
                    dir.w = 0.0f;
                    dir.x = tn.x - un.x;
                    dir.z = tn.z - un.z;
                } else {
                    if (un.y <= tn.y) {
                        continue;
                    }
                    if (u->n.y < 0.75f || 1.0f < u->n.y) {
                        continue;
                    }
                    dir.y = 0.0f;
                    dir.w = 0.0f;
                    dir.x = un.x - tn.x;
                    dir.z = un.z - tn.z;
                }
                for (m = 0; m < 3; m++) {
                    clear((u8 *)&e2, 8);
                    e2.a = &u->v[idx.v[m][0]];
                    e2.b = &u->v[idx.v[m][1]];
                    if ((VecDistSq_1cb3c0(e.a, e2.a) <= D_0047DB28 && VecDistSq_1cb3c0(e.b, e2.b) <= D_0047DB28) ||
                        (VecDistSq_1cb3c0(e.a, e2.b) <= D_0047DB28 && VecDistSq_1cb3c0(e.b, e2.a) <= D_0047DB28)) {
                        if (kind == 0) {
                            p = e.a;
                            q = e.b;
                            VecCopy_1cbe30(&nrm, &u->n);
                        } else {
                            p = e2.a;
                            q = e2.b;
                            VecCopy_1cbe30(&nrm, &t->n);
                        }
                        ClosestPointOnSegmentXZ_1c9e60(&hit, p, q, &pos);
                        d = VecDistSqXZ_1cb390(&hit, &pos);
                        if (d <= D_0047DB28) {
                            d = D_0047DB28;
                        } else if (!(d <= r2sq)) {
                            break;
                        }
                        VecNormalizeXZ_1cbb50(&nrm, &nrm);
                        if (VecDot3_1cba90(&nrm, &dir) < 0.0f) {
                            VecNegate_1cb9a0(&nrm, &nrm);
                        }
                        VecSubCross_1cb9c0(&side, p, q, &nrm);
                        if (side.y < 0.0f) {
                            a = p;
                        } else {
                            a = q;
                            q = p;
                        }
                        if (n < 6) {
                            cand[n].a = a;
                            cand[n].b = q;
                            VecCopy_1cbe30(&cand[n].n, &nrm);
                            cand[n].d = d;
                            if (n > 0) {
                                if (d < cand[best].d) {
                                    best = n;
                                    VecCopy_1cbe30(&bestp, &hit);
                                } else if (!(d <= cand[worst].d)) {
                                    worst = n;
                                }
                            } else {
                                VecCopy_1cbe30(&bestp, &hit);
                            }
                            n++;
                        } else {
                            if (d < cand[worst].d) {
                                s32 w;
                                cand[worst].a = a;
                                cand[worst].b = q;
                                VecCopy_1cbe30(&cand[worst].n, &nrm);
                                cand[worst].d = d;
                                if (d < cand[best].d) {
                                    best = worst;
                                    VecCopy_1cbe30(&bestp, &hit);
                                }
                                mx = cand[0].d;
                                worst = 0;
                                for (w = 1; w < 6; w++) {
                                    if (mx < cand[w].d) {
                                        mx = cand[w].d;
                                        worst = w;
                                    }
                                }
                            }
                        }
                        break;
                    }
                }
                if (m < 3) {
                    break;
                }
            }
        }
    }
    if (n > 0) {
        Cand *cc = &cand[best];
        VecCopy_1cbe30(&out->v[0], cc->a);
        VecCopy_1cbe30(&out->v[1], cand[best].b);
        VecCopy_1cbe30(&out->v[4], &cc->n);
        out->flags = 0;
        for (j = 0; j < n; j++) {
            if (j == best) {
                continue;
            }
            if ((out->flags & 0x40000000) && (out->flags & 0x20000000)) {
                break;
            }
            if (!(out->flags & 0x40000000) && VecDistSq_1cb3c0(cand[j].b, &out->v[0]) <= D_0047DAC8) {
                VecCopy_1cbe30(&out->v[2], cand[j].a);
                VecCopy_1cbe30(&out->v[5], &cand[j].n);
                out->flags |= 0x40000000;
            } else if (!(out->flags & 0x20000000) && VecDistSq_1cb3c0(cand[j].a, &out->v[1]) <= D_0047DAC8) {
                VecCopy_1cbe30(&out->v[3], cand[j].b);
                VecCopy_1cbe30(&out->v[6], &cand[j].n);
                out->flags |= 0x20000000;
            }
        }
        pr = *(Pr *)D_0047E780;
        for (k = 0; k < 3; k++) {
            if (k == 1 && !(out->flags & 0x40000000)) {
                continue;
            }
            if (k == 2 && !(out->flags & 0x20000000)) {
                continue;
            }
            nn = &out->v[k];
            if (1.0f == nn[4].x + nn[4].z) {
                continue;
            }
            VecSub_1cbd00(&ev, &out->v[pr.v[k][0]], &out->v[pr.v[k][1]]);
            up.y = 1.0f;
            ev.y = 0.0f;
            up.x = 0.0f;
            up.z = 0.0f;
            up.w = 0.0f;
            VecCross_1cb9f0(&ev, &ev, &up);
            VecNormalizeXZ_1cbb50(&ev, &ev);
            if (*(volatile f32 *)&ev.x != 0.0f) {
                if (Fabs(ev.x) < D_0047D2CC) {
                    ev.x = 0.0f;
                    ev.z = ev.z / Fabs(ev.z);
                    goto done;
                }
            }
            if (*(volatile f32 *)&ev.z != 0.0f) {
                if (Fabs(ev.z) < D_0047D2CC) {
                    f = Fabs(ev.x);
                    ev.z = 0.0f;
                    ev.x = ev.x / f;
                }
            }
        done:
            nn = (V4 *)((u8 *)nn + 0x40);
            if (VecDot3_1cba90(&ev, nn) < 0.0f) {
                VecNegate_1cb9a0(&ev, &ev);
            }
            VecCopy_1cbe30(nn, &ev);
        }
    }
    if (!(out->flags & 0x40000000)) {
        VecCopy_1cbe30(&out->v[2], &out->v[0]);
        VecCopy_1cbe30(&out->v[5], &out->v[4]);
    }
    if (!(out->flags & 0x20000000)) {
        VecCopy_1cbe30(&out->v[3], &out->v[1]);
        VecCopy_1cbe30(&out->v[6], &out->v[4]);
    }
    if (obj != NULL) {
        h = obj->m4C8 * (D_0047DB14 * (f32)D_0045B080[0]);
    } else {
        h = 0.0f;
    }
    lim = 2.0f * h;
    if (lim < 16.0f) {
        lim = 16.0f;
    }
    if (Ok(out) && lim * lim < VecDistSqXZ_1cb390(&bestp, &base)) {
        out->flags = 0x80000000;
    }
    if (Ok(out)) {
        *(V4u *)&va = D_0047E790;
        va.x = base.x;
        h = D_0047D5D0 * (f32)D_0045B080[0];
        h = bestp.y + (f32)h;
        va.z = base.z;
        *(V4u *)&vb = D_0047E7A0;
        va.y = h;
        vb.x = bestp.x;
        vb.y = h;
        vb.z = bestp.z;
        VecSub_1cbd00(&vd, &vb, &va);
        VecScaleToLength_1cb510(&vd, &vd, rad + VecLengthXZ_1cb490(&vd));
        if (CollRaycastNearestFiltered_1c8500(tris, cnt, mask, &va, &vd, &res, D_0047DB2C, D_0047DADC) >= 0) {
            out->flags = 0x80000000;
        }
    }
}
