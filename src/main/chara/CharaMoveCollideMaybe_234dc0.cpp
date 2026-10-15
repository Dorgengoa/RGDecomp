#include "types.h"
#pragma opt_lifetimes off
#pragma opt_rebuildconditionals off

extern "C" {

typedef struct V4 {
    f32 x, y, z, w;
} __attribute__((aligned(16))) V4;

typedef struct N4 {
    f32 x, y, z, w;
} N4;

typedef struct Tri {
    f32 v[3][4];
    N4 n;
    s16 s[10];
    s32 x54;
} __attribute__((aligned(16))) Tri;

typedef struct PP {
    V4 *p[2];
} __attribute__((aligned(16))) PP;

typedef struct Hit {
    u8 pad0[0xC];
    s32 xC;
    f32 x10;
} Hit;

typedef struct Prm {
    u8 pad0[0x4C8];
    f32 x4C8;
    f32 x4CC;
} Prm;

typedef struct Ent {
    u8 pad0[0x50];
    V4 x50;
    V4 x60;
    V4 x70;
    V4 x80;
    V4 x90;
    V4 xA0;
    V4 xB0;
    V4 xC0;
    V4 xD0;
    V4 xE0;
    V4 xF0;
    u8 pad100[0x350 - 0x100];
    u8 x350[0x3CC - 0x350];
    s32 x3CC;
    u64 fl;
    s32 x3D8;
    f32 x3DC;
    u8 pad3E0[4];
    f32 x3E4;
    f32 x3E8;
    u8 pad3EC[4];
    f32 x3F0;
    Prm *x3F4;
    u8 pad3F8[0x40E - 0x3F8];
    s16 x40E;
    s16 x410;
} Ent;

typedef struct Col {
    s32 id;
    u8 pad4[8];
    Tri *tris;
    s32 ntris;
    Tri *l1;
    s32 n1;
    Tri *l2;
    s32 n2;
    Tri *l3;
    s32 n3;
    V4 *sph;
    s32 nsph;
    s32 x34;
    u8 pad38[4];
    f32 x3C;
} Col;

void CharaMoveRolloverMaybe_236930(Ent *, Col *);
void VecAdd_1cbdc0(V4 *, V4 *, V4 *);
void VecSub_1cbd00(V4 *, V4 *, V4 *);
void VecWrapAngle_1cbe90(V4 *, V4 *);
void VecCopy_1cbe30(V4 *, V4 *);
void VecScale_1cbca0(V4 *, V4 *, f32);
void VecScaleToLength_1cb510(V4 *, V4 *, f32);
void VecAdd3_1cbd60(V4 *, V4 *, V4 *, V4 *);
void VecNormalize_1cbb80(V4 *, V4 *);
void VecLinearCombine_1cb8b0(V4 *, V4 *, V4 *, f32, f32);
f32 VecLengthSqXZ_1cb450(V4 *);
f32 VecLengthSq_1cb470(V4 *);
f32 VecLengthXZ_1cb490(V4 *);
f32 VecDotXZ_1cba70(V4 *, V4 *);
f32 VecDot3_1cba90(V4 *, V4 *);
void ModelSetRot_151080(Prm *, V4 *);
void ModelSetPos_151110(Prm *, V4 *);
void MatRotY_1cb200(V4 *, f32);
void SrtGetPos_1c7430(V4 *, V4 *);
void MtxMulDir_1cb910(V4 *, V4 *, V4 *);
void *GetEventObjMgr_2d1960(void);
s32 EventObjMgrPosClearOfVolumesMaybe_2e8b60(void *, V4 *, f32);
void CharaPlaceAt_2f3a40(s32, V4 *, s32, f32);
f32 GetThrowGravity_3647b0(void);
void *GetCurrentScene_1f5be0(void);
f32 GameSceneGetTimeStep_1ceba0(void *);
s32 CharaCalcBoundsRangeMaybe_237f20(Ent *, V4 *, V4 *, s32, s32, f32);
void TriCalcBounds_1cb540(V4 *, V4 *, void *, void *, void *);
f32 FloatInRange_1c9280(f32, f32, f32);
s32 CharaCollClampFloorCeilingMaybe_2364e0(s32, V4 *, V4 *, Tri *, s32, s32, bool, bool, f32, f32, f32);
void CharaCollideWallsMaybe_236cb0(Ent *, Tri *, s32, V4 *, V4 *, V4 *, f32);
Hit *ObjGetNthAttachPointPos_1ade20(Prm *, s32, s32, V4 *);
s32 CirclePushOutXZMaybe_1c82c0(V4 *, V4 *, V4 *, f32, f32);
s32 CollSweepFindTriLoweredMaybe_23abc0(Tri *, s32, s32, V4 *, V4 *, f32 *);
s32 CollSweepFindTriRaisedMaybe_23ae20(Tri *, s32, s32, V4 *, V4 *, f32 *);
s32 CollSweepFindTriRaisedMaybe_23acf0(Tri *, s32, s32, V4 *, V4 *, f32 *);
void GameSceneSoundSlot5PlaySeVol_1d05d0(void *, s32, f32);
void CharaProbeWaterSurfaceMaybe_237520(Ent *, Tri *, s32, s32);
void CharaGroundSnapMaybe_237990(Ent *, Tri *, s32, f32);
void CharaCollProbeAheadMaybe_237340(Ent *, Tri *, s32);
void CharaHangLedgeFind_238a70(void *, Prm *, Tri *, s32, s32, s32, s32, f32, f32);
f32 sqrtf(f32);

extern f32 D_0045B078[];
extern const f32 D_0045B080[];
extern f32 D_0045B088[];
extern f32 D_0047D288;
extern f32 D_0047D870;
extern f32 D_0047DAB4;
extern f32 D_0047DAC0;
extern f32 D_0047DB14;
extern f32 D_0047DB20;
extern f32 D_0047DB38;
extern f32 D_0047DB3C;
extern f32 D_0047DB40;
extern f32 D_0047DB4C;
extern f32 D_0047E720[4];
}

static inline void Clr(u8 *p, u32 n)
{
    if (p != 0) {
        while (n != 0) {
            *p = 0;
            n--;
            p++;
        }
    }
}

static inline f32 Abs(f32 x)
{
    if (x < 0.0f) {
        return -x;
    }
    return x;
}

static inline void Snap(Prm *p, f32 x, f32 y, f32 z)
{
    V4 v;
    v = *(V4 *)D_0047E720;
    v.x = x;
    v.y = y;
    v.z = z;
    ModelSetPos_151110(p, &v);
}

static inline s32 Flag(Ent *e, u64 m)
{
    return (e->fl & m) != 0;
}

extern "C" void CharaMoveCollideMaybe_234dc0(Ent *e, Col *c)
{
    bool moved;
    f32 sx;
    f32 o77C;
    V4 v760;
    V4 m730[3];
    V4 v720;
    V4 v710;
    V4 v700;
    V4 v6F0;
    V4 v6E0;
    V4 v6D0;
    V4 v6C0;
    V4 v6B0;
    PP ptrs;
    V4 v690;
    V4 hv[0x40];
    V4 push;
    V4 v270;
    V4 v260;
    V4 v250;
    V4 v240;
    V4 v230;
    V4 v220;
    V4 v210;
    V4 v200;
    V4 v1F0;
    V4 v1E0;
    V4 v1D0;
    V4 v1C0;
    V4 v1B0;
    V4 v1A0;
    V4 v190;
    V4 v180;
    V4 v170;
    V4 v160;
    V4 v150;
    V4 v140;
    f32 o778;
    s32 j;
    f32 sy;
    f32 r28;
    f32 r27;
    f32 len;
    f32 r25;
    f32 r24;
    Tri *lst;
    f32 f;
    f32 r23;
    V4 *hp;
    f32 r22;
    f32 d;
    f32 r13;
    f32 k21;
    f32 dt;
    Tri *t;
    s32 nh;
    f32 k;
    f32 sz;
    f32 lim2;
    f32 rr;
    f32 lo;
    s32 ia;
    s32 idx;
    s32 ic;
    Tri *dst;
    Tri *l2;
    f32 upY;
    u64 fl;
    f32 a;
    f32 t0;
    V4 **pp;
    V4 *sph;
    s32 cnt;
    bool noDn;
    Hit *h;
    s32 timer;
    s32 ib;
    bool noUp;
    f32 o774;
    f32 tt;
    f32 hiY;
    f32 lim;
    s32 nl;
    Prm *prm;
    s32 pass;
    s32 n2;
    f32 o770;
    s32 id;
    Tri *tris;
    s32 i;
    s32 n;

    CharaMoveRolloverMaybe_236930(e, c);
    e->x3CC = 0x80000000;
    if (e->x3F4 != 0) {
        VecAdd_1cbdc0(&e->x60, &e->x60, &e->x90);
        VecWrapAngle_1cbe90(&e->x60, &e->x60);
        ModelSetRot_151080(e->x3F4, &e->x60);
        MatRotY_1cb200(m730, e->x60.y);
        SrtGetPos_1c7430(&e->x50, &v760);
        MtxMulDir_1cb910(&e->xA0, m730, &e->xA0);
        MtxMulDir_1cb910(&e->xB0, m730, &e->xB0);
        VecAdd_1cbdc0(&e->xC0, &e->xC0, &e->xA0);
        VecAdd_1cbdc0(&e->xD0, &e->xD0, &e->xB0);
        if (e->fl & 0x0000008000000000ULL) {
            e->xD0.y = 0.0f;
        }
        if (e->fl & 0x0000004000000000ULL) {
            e->xD0.z = 0.0f;
            e->xD0.x = 0.0f;
        }
        VecAdd_1cbdc0(&e->x80, &e->x80, &e->xC0);
        moved = 0;
        if (c != 0) {
            if (EventObjMgrPosClearOfVolumesMaybe_2e8b60(GetEventObjMgr_2d1960(), &e->x70, 0.0f) == 0) {
                CharaPlaceAt_2f3a40(c->id, &e->x70, 0, e->x60.y);
            }
            Clr((u8 *)&v720, 16);
            fl = e->fl;
            if (!(fl & 0x0000400000000000ULL) && !(fl & 0x0000002000000000ULL) && !(fl & 0x0000008000000000ULL)) {
                if (fl & 0x20) {
                    v720.y = GetThrowGravity_3647b0();
                } else {
                    k = D_0045B078[0];
                    v720.y = -2.0f * (D_0045B088[0] * (*(f32 *)&D_0045B080[0] / (k * k))) * GameSceneGetTimeStep_1ceba0(GetCurrentScene_1f5be0());
                }
            }
            VecAdd_1cbdc0(&e->x80, &e->x80, &v720);
            VecAdd_1cbdc0(&e->x70, &e->x70, &e->xE0);
            VecCopy_1cbe30(&v710, &e->x70);
            v710.y += e->x80.y;
            a = *(volatile f32 *)&e->x80.y;
            k = *(f32 *)&D_0045B080[0];
            if (a < 0.0f) {
                a = -a;
            }
            lim = 0.5f * k;
            if (!(a <= lim)) {
                e->x80.y = (e->x80.y < 0.0f) ? -lim : lim;
            }
            c->n1 = 0;
            c->n2 = 0;
            c->n3 = 0;
            if (CharaCalcBoundsRangeMaybe_237f20(e, &v700, &v6F0, 0, 0, 0.0f) != 0) {
                d = *(f32 *)&D_0045B080[0];
                d = 2.0f * (f32)d;
                v700.y += d;
                v6F0.y -= d;
                t = c->tris;
                for (i = 0; i < c->ntris; i++, t++) {
                    if (t->s[3] & e->x40E) {
                        continue;
                    }
                    TriCalcBounds_1cb540(&v6E0, &v6D0, t->v[0], t->v[1], t->v[2]);
                    if (FloatInRange_1c9280(Abs(t->n.y), D_0047DB38, 1.0f) && v6D0.y <= v700.y) {
                        dst = &c->l1[c->n1];
                        *dst = *t;
                        c->n1++;
                    }
                    if (FloatInRange_1c9280(Abs(t->n.y), 0.5f, 1.0f) && v6D0.y <= v700.y && v6F0.y <= v6E0.y) {
                        dst = &c->l2[c->n2];
                        *dst = *t;
                        c->n2++;
                    }
                    f = t->n.y;
                    if (D_0047DB3C <= f && f <= D_0047D288 && v6D0.y <= v700.y && v6F0.y <= v6E0.y) {
                        dst = &c->l3[c->n3];
                        *dst = *t;
                        c->n3++;
                    }
                }
            }
            fl = e->fl;
            if (fl & 0x0010000000000000ULL) {
                e->fl = fl & ~0x0010000000000000ULL;
            }
            if ((e->x3D8 & 0x20) && !(e->fl & 0x0000800000000000ULL) && !(e->x3E8 <= D_0047DB14 * k)) {
                VecSub_1cbd00(&v6C0, &e->x80, &e->xF0);
                v6C0.y -= (v720.y * e->x3E4) / e->x3E8;
                VecScale_1cbca0(&v6C0, &v6C0, 1.0f - D_0047DB40 * e->x3E4);
                VecAdd_1cbdc0(&e->x80, &e->xF0, &v6C0);
            }
            prm = e->x3F4;
            sx = e->x80.x;
            sy = e->x80.y;
            sz = e->x80.z;
            lo = D_0047DAC0 * k;
            if (prm != 0) {
                r24 = prm->x4C8 * (D_0047DB14 * k);
            } else {
                r24 = 0.0f;
            }
            r24 = (r24 > lo) ? r24 : lo;
            lo = D_0047DAB4 * k;
            if (prm != 0) {
                r28 = prm->x4CC * (D_0047DB14 * k);
            } else {
                r28 = 0.0f;
            }
            r28 = (r28 > lo) ? r28 : lo;
            r25 = 0.5f * r28;
            if (r25 < 1.25f * k) {
                r25 = 1.25f * k;
            }
            if (e->fl & 0x0000000800000000ULL) {
                e->x80.y = 0.0f;
            }
            if (e->fl & 0x0000000400000000ULL) {
                e->x80.x = 0.0f;
                e->x80.z = 0.0f;
            }
            if (c->tris != 0 && c->ntris > 0) {
                moved = 1;
                VecCopy_1cbe30(&v6B0, &e->x70);
                l2 = c->l2;
                n2 = c->n2;
                fl = e->fl;
                noUp = (fl & 0x0000020000000000ULL) != 0;
                noDn = (fl & 0x0000040000000000ULL) != 0;
                if ((fl & 0x4000000000000000ULL) && !(fl & 0x0001000000000000ULL)) {
                    r13 = D_0047DB20 * k;
                } else {
                    r13 = 0.0f;
                }
                if (CharaCollClampFloorCeilingMaybe_2364e0(c->id, &e->x70, &e->x70, l2, n2, e->x40E,
                                 !noDn, !noUp,
                                 r28, r13, r25) != 0) {
                    e->x410 = 0.5f * D_0045B078[0];
                    e->x40E |= 0x1000;
                }
                CharaCollideWallsMaybe_236cb0(e, c->l3, c->n3, &v6B0, &e->x70, &e->x80, c->x3C);
                VecCopy_1cbe30(&v6B0, &e->x70);
                Clr((u8 *)&ptrs, 8);
                ptrs.p[0] = &e->xD0;
                ptrs.p[1] = &e->x80;
                r27 = D_0047DAC0 * r24;
                pass = 0;
                k21 = *(f32 *)&D_0045B080[0];
                r23 = D_0047DB14 * k21;
                lim2 = r27 * r27;
                r22 = 2.0f * r23;
                upY = r25 + 5.0f * r23;
                timer = 0.5f * D_0045B078[0];
                hiY = r28 + r22;
                k = D_0047DB20 * k21;
                do {
                    pp = &ptrs.p[pass];
                    VecCopy_1cbe30(&v690, *pp);
                    if (VecLengthSq_1cb470(&v690) == 0.0f) {
                        continue;
                    }
                    ModelSetPos_151110(e->x3F4, &e->x70);
                    if (!(e->fl & 0x0000080000000000ULL)) {
                        nh = 0;
                        sph = c->sph;
                        j = 0;
                        cnt = c->nsph;
                        while ((h = ObjGetNthAttachPointPos_1ade20(e->x3F4, 0x78, j, hp = &hv[nh])) != 0) {
                            j++;
                            if (h->xC != 0 && !(h->x10 <= 0.0f)) {
                                nh++;
                                hp->w = h->x10 * r23;
                            }
                        }
                        Clr((u8 *)&push, 16);
                        for (ia = 0; ia < nh; ia++) {
                            for (ib = cnt - 1; ib >= 0; ib--) {
                                if (CirclePushOutXZMaybe_1c82c0(&v270, &sph[ib], &hv[ia], sph[ib].w, hv[ia].w) != 0) {
                                    v270.w = 0.0f;
                                    VecScaleToLength_1cb510(&v260, &v270, r22);
                                    VecAdd_1cbdc0(&v270, &v270, &v260);
                                    VecAdd_1cbdc0(&push, &push, &v270);
                                    for (ic = 0; ic < nh; ic++) {
                                        VecAdd_1cbdc0(&hv[ic], &hv[ic], &v270);
                                    }
                                }
                            }
                        }
                        if (!(VecLengthSqXZ_1cb450(&push) <= lim2)) {
                            VecScale_1cbca0(&push, &push, r27 / VecLengthXZ_1cb490(&push));
                        }
                        VecAdd_1cbdc0(&e->x70, &e->x70, &push);
                        Clr((u8 *)&v250, 16);
                        len = VecLengthSq_1cb470(&v690);
                        if (!(len <= 0.0f)) {
                            r25 = 1.0f;
                            for (ia = 0; ia < nh; ia++) {
                                if (r25 <= 0.0f) {
                                    break;
                                }
                                for (ib = cnt - 1; ib >= 0; ib--) {
                                    VecSub_1cbd00(&v240, &sph[ib], &hv[ia]);
                                    { f32 s_ = *(volatile f32 *)&sph[ib].w; f32 h_ = *(volatile f32 *)&hv[ia].w; rr = h_ + s_; }
                                    rr = VecLengthSq_1cb470(&v240) - rr * rr;
                                    if (rr <= 0.0f) {
                                        VecCopy_1cbe30(&v250, &v240);
                                        r25 = 0.0f;
                                        break;
                                    }
                                    dt = VecDot3_1cba90(&v690, &v240);
                                    tt = dt * dt - len * rr;
                                    if (!(tt <= 0.0f)) {
                                        rr = (dt - sqrtf(tt)) / len;
                                        if (!(rr < 0.0f) && !(r25 <= rr)) {
                                            VecCopy_1cbe30(&v250, &v240);
                                            r25 = rr;
                                        }
                                    }
                                }
                            }
                            if (r25 < 1.0f) {
                                len = v690.y;
                                v690.y = 0.0f;
                                VecLinearCombine_1cb8b0(&v690, &v690, &v690, D_0047D870 * r25, 0.5f * (1.0f - r25));
                                v690.y = len;
                            }
                        }
                    }
                    Clr((u8 *)&v230, 16);
                    v230.x = v690.x;
                    v230.z = v690.z;
                    f = VecLengthXZ_1cb490(&v690);
                    if (f <= 0.0f) {
                        rr = 1.0f;
                    } else {
                        rr = r27 / f;
                    }
                    f32 h32_ = 32.0f;
                    if (rr * h32_ < 1.0f) {
                        rr = 0.03125f;
                    }
                    t0 = 0.0f;
                    len = t0;
                    while (t0 < 1.0f) {
                        len += rr;
                        if (!(len <= 1.0f)) {
                            len = 1.0f;
                        }
                        while (t0 < len) {
                            VecScale_1cbca0(&v220, &v690, len - t0);
                            VecCopy_1cbe30(&v210, &e->x70);
                            if (!(e->fl & 0x0000020000000000ULL)) {
                                lst = c->l2;
                                nl = c->n2;
                                VecCopy_1cbe30(&v200, &v210);
                                VecCopy_1cbe30(&v1F0, &v210);
                                v200.y += upY;
                                v1F0.y += hiY;
                                VecSub_1cbd00(&v1F0, &v1F0, &v200);
                                if (CollSweepFindTriLoweredMaybe_23abc0(lst, nl, e->x40E | 0x1800, &v200, &v1F0, &o77C) >= 0) {
                                    e->x410 = timer;
                                    e->x40E |= 0x1000;
                                    if (!(v220.y <= 0.0f)) {
                                        v220.y = 0.0f;
                                    }
                                    v210.y = v200.y + o77C * v1F0.y - r28 - r23;
                                }
                                VecCopy_1cbe30(&v1E0, &v210);
                                v1E0.y += r28;
                                if (CollSweepFindTriLoweredMaybe_23abc0(lst, nl, e->x40E | 0x1800, &v1E0, &v220, &o778) >= 0) {
                                    e->x410 = timer;
                                    e->x40E |= 0x1000;
                                    v220.x *= o778;
                                    v220.z *= o778;
                                    v210.y -= r23;
                                    if (!(v220.y <= 0.0f)) {
                                        v220.y = 0.0f;
                                    }
                                }
                            }
                            VecAdd_1cbdc0(&v210, &v210, &v220);
                            if (!(e->fl & 0x0000040000000000ULL)) {
                                VecCopy_1cbe30(&v1D0, &v210);
                                VecCopy_1cbe30(&v1C0, &v210);
                                v1D0.y += k21;
                                fl = e->fl;
                                if ((fl & 0x4000000000000000ULL) && !(fl & 0x0001000000000000ULL)) {
                                    v1C0.y -= k;
                                }
                                VecSub_1cbd00(&v1B0, &v1C0, &v1D0);
                                lst = c->l1;
                                idx = CollSweepFindTriRaisedMaybe_23ae20(lst, c->n1, e->x40E, &v1D0, &v1B0, &o774);
                                if (idx >= 0) {
                                    t = &lst[idx];
                                    if (FloatInRange_1c9280(Abs(t->n.y), 0.5f, 1.0f)) {
                                        { f32 t_ = v1D0.y + v1B0.y * o774; v210.y = t_ + r23; }
                                    } else {
                                        VecScale_1cbca0(&v1A0, &v1B0, o774);
                                        r25 = VecDot3_1cba90((V4 *)&t->n, &v1B0);
                                        VecScale_1cbca0(&v190, (V4 *)&t->n, r25 / VecLengthSq_1cb470((V4 *)&t->n));
                                        VecSub_1cbd00(&v190, &v1B0, &v190);
                                        VecScale_1cbca0(&v190, &v190, 1.0f - o774);
                                        VecAdd3_1cbd60(&v180, &v1D0, &v1A0, &v190);
                                        v180.y += r23;
                                    }
                                }
                            }
                            CharaCollideWallsMaybe_236cb0(e, c->l3, c->n3, &v6B0, &v210, &v220, c->x3C);
                            if (!(e->fl & 0x0000040000000000ULL)) {
                                lst = c->l2;
                                nl = c->n2;
                                VecCopy_1cbe30(&v170, &v210);
                                VecCopy_1cbe30(&v160, &v210);
                                v170.y += k21;
                                v160.y = e->x70.y + v220.y;
                                fl = e->fl;
                                if ((fl & 0x4000000000000000ULL) && !(fl & 0x0001000000000000ULL)) {
                                    v160.y -= k;
                                }
                                VecSub_1cbd00(&v150, &v160, &v170);
                                idx = CollSweepFindTriRaisedMaybe_23acf0(lst, nl, e->x40E, &v170, &v150, &o770);
                                if (idx >= 0) {
                                    t = &lst[idx];
                                    { f32 t_ = v170.y + v150.y * o770; v210.y = t_ + r23; }
                                    r25 = v690.y;
                                    Clr((u8 *)&v140, 16);
                                    v140.x = v230.x;
                                    v140.y = -VecDotXZ_1cba70(&v230, (V4 *)&t->n) / t->n.y;
                                    v140.z = v230.z;
                                    VecNormalize_1cbb80(&v140, &v140);
                                    f = VecDot3_1cba90(&v690, &v140);
                                    VecScale_1cbca0(&v690, &v140, f <= 0.0f ? 0.0f : f);
                                    if ((e->fl & 0x0002000000000000ULL) && r25 < D_0047DB4C) {
                                        if (r25 < -1.5f) {
                                            id = c->id;
                                            if (id >= 0x80 && id < 0x9C) {
                                                GameSceneSoundSlot5PlaySeVol_1d05d0(GetCurrentScene_1f5be0(), 0x41, 1.0f);
                                                e->fl |= 0x80;
                                            }
                                        }
                                        { f32 h_ = -0.5f; f = r25 * h_; }
                                        if (!(f <= v690.y)) {
                                            v690.y = f;
                                        }
                                        e->fl |= 0x2000000000000000ULL;
                                    }
                                }
                            }
                            VecCopy_1cbe30(&e->x70, &v210);
                            VecCopy_1cbe30(&v6B0, &v210);
                            t0 = len;
                        }
                    }
                    VecCopy_1cbe30(*pp, &v690);
                } while (++pass < 2);
            }
            if (!moved) {
                VecAdd3_1cbd60(&e->x70, &e->x70, &e->x80, &e->xD0);
            }
            if (e->fl & 0x0000000800000000ULL) {
                e->x80.y = sy;
            }
            if (e->fl & 0x0000000400000000ULL) {
                e->x80.x = sx;
                e->x80.z = sz;
            }
            {
                Prm *qp = e->x3F4;
                f32 qz = e->x70.z;
                f32 qy = e->x70.y + e->x3DC;
                f32 qx = e->x70.x;
                N4 q = *(N4 *)D_0047E720;
                q.x = qx;
                q.y = qy;
                q.z = qz;
                ModelSetPos_151110(qp, (V4 *)&q);
            }
            tris = c->tris;
            if (tris != 0) {
                n = c->ntris;
                if (n > 0) {
                    CharaProbeWaterSurfaceMaybe_237520(e, tris, n, c->x34);
                    CharaGroundSnapMaybe_237990(e, tris, n, v710.y);
                    CharaCollProbeAheadMaybe_237340(e, tris, n);
                    if (((e->fl & 0x0400000000000000ULL) != 0) ^ 1) {
                        CharaHangLedgeFind_238a70(e->x350, e->x3F4, tris, n, e->x40E, 0, (e->x3D8 & 0x10) != 0, r24, e->x3F0);
                    } else {
                        e->x3CC = 0x80000000;
                    }
                    {
                Prm *qp = e->x3F4;
                f32 qz = e->x70.z;
                f32 qy = e->x70.y + e->x3DC;
                f32 qx = e->x70.x;
                N4 q = *(N4 *)D_0047E720;
                q.x = qx;
                q.y = qy;
                q.z = qz;
                ModelSetPos_151110(qp, (V4 *)&q);
            }
                }
            }
        }
        VecAdd_1cbdc0(&e->x80, &e->x80, &e->xE0);
        f32 k = D_0045B080[0];
        e->xA0.x = 0.0f;
        e->xA0.y = 0.0f;
        e->xA0.z = 0.0f;
        e->xA0.w = 0.0f;
        e->xB0.x = 0.0f;
        e->xB0.y = 0.0f;
        e->xB0.z = 0.0f;
        e->xB0.w = 0.0f;
        e->xC0.x = 0.0f;
        e->xC0.y = 0.0f;
        e->xC0.z = 0.0f;
        e->xC0.w = 0.0f;
        e->xD0.x = 0.0f;
        e->xD0.y = 0.0f;
        e->xD0.z = 0.0f;
        e->xD0.w = 0.0f;
        if (e->x70.y < -1100 * k) {
            e->x70.y = 100.0f * k;
        }
    }
}
