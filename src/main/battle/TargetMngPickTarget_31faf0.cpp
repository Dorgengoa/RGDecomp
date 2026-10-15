#include "types.h"

typedef unsigned __int128 u128;

struct Vec4 {
    f32 x, y, z, w;
};

struct T30 {
    s16 a;
    s16 b;
    s32 w[11];
};

struct Ent {
    T30 t;
    f32 ang;             /* 0x30 */
};

struct Self {
    u8 pad0[0x90];
    Vec4 pos;            /* 0x90 */
    u8 padA0[0x10];
    f32 fB0;             /* 0xB0 */
    f32 fB4;
    f32 fB8;             /* 0xB8 */
    f32 fBC;
    T30 tgt;             /* 0xC0 */
};

struct Obj {
    u8 pad0[0x10];
    u8 sub[0xD0];        /* 0x10 */
    u32 flags;           /* 0xE0 */
};

struct Q {
    s16 id;
    u8 pad2[0x36];
    f32 x;               /* 0x38 */
    f32 y;
    f32 z;
    f32 w;
    u8 pad48[0xE];
    u8 flags;            /* 0x56 */
};

struct R8 {
    s16 id;
    u8 pad2[6];
    s16 flags;           /* 0x08 */
};

struct Tgt2 {
    u8 pad0[0x180];
    u128 pos;            /* 0x180 */
    Vec4 rot;            /* 0x190 */
};

struct Ctl18 {
    u8 pad0[0x18E];
    s16 id;              /* 0x18E */
    u8 pad190[0x42D0 - 0x190];
    u8 flags;            /* 0x42D0 */
};

struct Ctl {
    u8 pad0[0x18];
    Ctl18 *c;            /* 0x18 */
};

extern "C" {
s32 FuncPointGetActiveId_201a00(void);
s32 GetStaticScene_1c6c70(void);
s32 GetCharaResMgr_1fdb60(void);
s32 GetMapMgr_201a90(void);
s32 GetActionMgr_1fdb50(void);
Ctl *GetGameData_1fede0(void);
s32 ActionMgrFindById_233b50(s32, s32);
s32 CharaIsActionFreeMaybe_2105e0(s32);
s32 TargetRefGetId_2e7120(T30 *);
s32 TargetRefGetKind_2e7130(T30 *);
void CharaGetPos_2388d0(s32, Vec4 *);
void SrtGetPosThunk_1c7430(s32, Vec4 *);
void CharaGetRot_2388e0(s32, Vec4 *);
void SrtGetRotThunk_1c7440(s32, Vec4 *);
f32 VecDistSq_1cb3c0(Vec4 *, Vec4 *);
void TargetRefCtor_2e71f0(Ent *);
f32 Atan2f_1291a8(f32, f32);
s32 GetEventObjMgr_2d1960(void);
s32 EventObjMgrGetTypeList_2e9d60(s32, s32);
Obj *DListGetHead_42ea60(s32);
Obj *DListGetNext_42eb30(Obj *);
T30 *EvObjGetTargetRef_2f9ca0(u8 *);
void TargetRefGetPos_2e6a60(T30 *, Vec4 *);
void VecSub_1cbd00(Vec4 *, Vec4 *, Vec4 *);
f32 VecLengthSq_13d440(Vec4 *);
f32 EvTargetPointObjGetRadius_2f93a0(u8 *);
f32 WrapAngle_13c050(f32);
s32 GetInsectCageMgr_1fdb30(void);
s32 InsectCageMgrGetSlot_39b140(s32, s32);
s32 InsectCageSlotGetState_39bb00(s32);
void InsectCageSlotGetPos_39b340(s32, Vec4 *);
f32 VecLengthSqXZ_13d410(Vec4 *);
s32 InsectCageSlotGetId_39b460(s32);
void TargetRefSetInsectCageSlot_2e6290(Ent *, s32);
s32 GetTreasureBoxPool_3389b0(void);
s32 TreasureBoxPoolCollectInReach_3391d0(s32, s32 *, s32);
void TreasureBoxGetPos_33ae30(s32, Vec4 *);
s32 TreasureBoxGetRecId_33b160(s32);
void TargetRefSetTreasureBox_2e62e0(Ent *, s32);
void NpcViewCtor_41c210(void *, Ctl *, s32, s32, s32);
void IterInit_370170(void *, void *);
Q *IterNext_370040(void *);
void TargetRefSetPointWithId_2e6210(Ent *, s32, f32, f32, f32, f32);
s32 GetNpcObjTable_312860(void);
s32 PartyCountExcludingLeader_3c2610(Ctl18 *, s32, s32);
s32 PartyGetNonLeaderId_3c2750(Ctl18 *, s32);
s32 CharaGetActionMode_213850(s32);
s32 CharaCanActMaybe_210500(s32);
void CharaGetPos_2388a0(s32, Vec4 *);
void TargetRefSetModelKind3_2e6660(Ent *, s32, s32, f32);
s32 NpcObjTableCollectIds_2fb3b0(s32, s32 *);
Tgt2 *ObjRecGetLiveObject_1c4a90(s32, s32);
R8 *NpcObjFindDefById_2fb490(s32, s32);
f32 Sinf_128fd0(f32);
f32 Cosf_128d30(f32);
void VecAdd_1cbdc0(Vec4 *, Vec4 *, Vec4 *);
s32 PadIsTriggered_1839f0(void *, s32);
void TargetRefSetId_2e6780(T30 *, s32);
extern f32 D_0045B080[];
extern f32 D_0047DB14;
extern f32 D_0047DC48;
extern f32 D_0047D404;
extern f32 D_0047D1FC;
extern f32 D_0047DC4C;
extern u8 D_004B2570[];
}


static inline f32 Abs(f32 x) {
    if (x < 0.0f) x = -x;
    return x;
}

extern "C" s32 TargetMngPickTarget_31faf0(Self *self) {
    u8 it[8];
    Vec4 v1170;
    Vec4 v1160;
    Vec4 v1150;
    Vec4 v1140;
    Ent ents[64];
    s32 list340[64];
    u8 buf[0x20];
    s32 list120[128];
    s32 w1;
    s32 w2;
    s32 cnt2;
    Ctl *ctl;
    s32 u;
    s32 best;
    bool far;
    s32 n;
    s32 k;
    s32 id;
    s32 cnt;
    s32 cnt3;
    s32 t2;
    s32 m;
    s32 sel;
    s32 res;
    Ent *e;
    Obj *o;
    u8 *sub;
    T30 *t;
    Q *q;
    Tgt2 *o2;
    R8 *r;
    s32 *pp;
    s32 kc;
    s32 uc;
    Ent *pe;
    s32 dir;
    f32 a;
    f32 qq;
    f32 f25;
    f32 f24;
    f32 f23;
    f32 m05;
    f32 m10;
    f32 f26;
    f32 f21;
    f32 d;
    f32 cur;
    f32 step;
    f32 lim;
    f32 thr;
    f32 t3;
    f32 t15;

    if (FuncPointGetActiveId_201a00() >= 0) return 0;
    w1 = GetStaticScene_1c6c70();
    GetCharaResMgr_1fdb60();
    GetMapMgr_201a90();
    w2 = GetActionMgr_1fdb50();
    ctl = GetGameData_1fede0();
    u = ActionMgrFindById_233b50(w2, ctl->c->id);
    if (u == 0) return 0;
    if (CharaIsActionFreeMaybe_2105e0(u) == 0) return 0;
    best = -1;
    far = TargetRefGetId_2e7120(&self->tgt) < 0;
    if (!far) {
        CharaGetPos_2388d0(u, &v1150);
        SrtGetPosThunk_1c7430(u, &v1140);
        thr = D_0045B080[0]; thr = D_0047DB14 * (f32)thr / 10.0f;
        if (!(VecDistSq_1cb3c0(&v1150, &v1140) <= thr * thr)) {
            far = 1;
        } else {
            CharaGetRot_2388e0(u, &v1150);
            SrtGetRotThunk_1c7440(u, &v1140);
            d = v1150.y - v1140.y;
            d = (d < 0.0f) ? -d : d;
            if (!(d <= D_0047DC48)) far = 1;
        }
    }
    if (far) best = 0x7FFFFFFF;
    t3 = D_0045B080[0]; t3 = 3.0f * (f32)t3;
    f25 = t3 * t3;
    e = ents;
    do {
        TargetRefCtor_2e71f0(e);
        e++;
    } while (e < &ents[64]);
    n = 0;
    f24 = Atan2f_1291a8(self->fB0, self->fB8);
    for (o = DListGetHead_42ea60(EventObjMgrGetTypeList_2e9d60(GetEventObjMgr_2d1960(), 14)); o != 0; o = DListGetNext_42eb30(o)) {
        sub = o->sub;
        if (((o->flags & 0x80000000) != 0) ^ 1) {
            if (o->flags & 0x2000000) {
                t = EvObjGetTargetRef_2f9ca0(sub);
                TargetRefGetPos_2e6a60(t, &v1160);
                VecSub_1cbd00(&v1170, &v1160, &self->pos);
                d = VecLengthSq_13d440(&v1170);
                qq = EvTargetPointObjGetRadius_2f93a0(sub);
                if (d <= qq * EvTargetPointObjGetRadius_2f93a0(sub)) {
                    if (best < 0) {
                        if (TargetRefGetKind_2e7130(&self->tgt) == TargetRefGetKind_2e7130(t) && TargetRefGetId_2e7120(&self->tgt) == TargetRefGetId_2e7120(t)) {
                            best = n;
                        }
                    }
                    ents[n].t = *t;
                    ents[n].ang = WrapAngle_13c050(Atan2f_1291a8(v1170.x, v1170.z) - f24);
                    n++;
                }
            }
        }
    }
    m05 = -0.5f * D_0045B080[0];
    f23 = 2.0f * D_0045B080[0];
    t2 = GetInsectCageMgr_1fdb30();
    for (k = 0; k < 3; k++) {
        m = InsectCageMgrGetSlot_39b140(t2, k);
        if (m == 0) continue;
        if (InsectCageSlotGetState_39bb00(m) != 2) continue;
        InsectCageSlotGetPos_39b340(m, &v1160);
        VecSub_1cbd00(&v1170, &v1160, &self->pos);
        if (!(m05 <= v1170.y)) continue;
        if (f23 < v1170.y) continue;
        if (!(VecLengthSqXZ_13d410(&v1170) <= f25)) continue;
        if (best < 0) {
            if (TargetRefGetKind_2e7130(&self->tgt) == 12 && TargetRefGetId_2e7120(&self->tgt) == InsectCageSlotGetId_39b460(m)) {
                best = n;
            }
        }
        e = &ents[n];
        TargetRefSetInsectCageSlot_2e6290(e, InsectCageSlotGetId_39b460(m));
        e->ang = WrapAngle_13c050(Atan2f_1291a8(v1170.x, v1170.z) - f24);
        n++;
    }
    cnt = TreasureBoxPoolCollectInReach_3391d0(GetTreasureBoxPool_3389b0(), list340, 0x40);
    for (k = 0; k < cnt; k++) {
        pp = &list340[k];
        if (*pp == 0) continue;
        TreasureBoxGetPos_33ae30(*pp, &v1160);
        VecSub_1cbd00(&v1170, &v1160, &self->pos);
        if (!(m05 <= v1170.y)) continue;
        if (f23 < v1170.y) continue;
        if (!(VecLengthSqXZ_13d410(&v1170) <= f25)) continue;
        if (best < 0) {
            if (TargetRefGetKind_2e7130(&self->tgt) == 11 && TargetRefGetId_2e7120(&self->tgt) == TreasureBoxGetRecId_33b160(*pp)) {
                best = n;
            }
        }
        e = &ents[n];
        TargetRefSetTreasureBox_2e62e0(e, TreasureBoxGetRecId_33b160(*pp));
        e->ang = WrapAngle_13c050(Atan2f_1291a8(v1170.x, v1170.z) - f24);
        n++;
    }
    NpcViewCtor_41c210(buf, ctl, -1, 0, 1);
    IterInit_370170(it, buf);
    while ((q = IterNext_370040(it)) != 0) {
        if (!(q->flags & 1)) continue;
        v1160.x = q->x;
        v1160.y = q->y;
        v1160.z = q->z;
        v1160.w = q->w;
        VecSub_1cbd00(&v1170, &v1160, &self->pos);
        if (!(m05 <= v1170.y)) continue;
        if (t3 < v1170.y) continue;
        if (!(VecLengthSqXZ_13d410(&v1170) <= f25)) continue;
        if (best < 0) {
            if (TargetRefGetKind_2e7130(&self->tgt) == 13 && q->id == TargetRefGetId_2e7120(&self->tgt)) {
                best = n;
            }
        }
        e = &ents[n];
        TargetRefSetPointWithId_2e6210(e, q->id, v1160.x, v1160.y, v1160.z, v1160.w);
        e->ang = WrapAngle_13c050(Atan2f_1291a8(v1170.x, v1170.z) - f24);
        n++;
    }
    t2 = GetNpcObjTable_312860();
    m10 = D_0045B080[0]; m10 = -1.0f * (f32)m10;
    if (!(ctl->c->flags & 1)) {
        cnt2 = PartyCountExcludingLeader_3c2610(ctl->c, 1, 1);
        cnt2 = (s32)cnt2;
        for (kc = 0; kc < cnt2; kc++) {
            id = PartyGetNonLeaderId_3c2750(ctl->c, kc);
            uc = ActionMgrFindById_233b50(w2, id);
            if (uc == 0) continue;
            if (CharaGetActionMode_213850(uc) != 0) continue;
            if (CharaCanActMaybe_210500(uc) == 0) continue;
            CharaGetPos_2388a0(uc, &v1160);
            VecSub_1cbd00(&v1170, &v1160, &self->pos);
            if (!(VecLengthSq_13d440(&v1170) <= f25)) continue;
            if (best < 0) {
                if (TargetRefGetKind_2e7130(&self->tgt) == 3 && id == TargetRefGetId_2e7120(&self->tgt)) {
                    best = n;
                }
            }
            e = &ents[n];
            TargetRefSetModelKind3_2e6660(e, id, -1, 0.0f);
            e->ang = WrapAngle_13c050(Atan2f_1291a8(v1170.x, v1170.z) - f24);
            n++;
        }
    }
    cnt3 = NpcObjTableCollectIds_2fb3b0(t2, list120);
    k = 0;
    t15 = 1.5f * D_0045B080[0];
    f26 = 0.5f * D_0045B080[0];
    for (; k < cnt3; k++) {
        id = list120[k];
        o2 = ObjRecGetLiveObject_1c4a90(w1, id);
        if (o2 == 0) continue;
        *(u128 *)&v1160 = o2->pos;
        r = NpcObjFindDefById_2fb490(t2, id);
        if (r == 0) continue;
        if (r->flags & 8) {
            Vec4 tmp110;
            *(u128 *)&tmp110 = *(u128 *)&o2->rot;
            Vec4 v100 = {0};
            v100.x = t15 * Sinf_128fd0(tmp110.y);
            v100.z = t15 * Cosf_128d30(tmp110.y);
            VecAdd_1cbdc0(&v1160, &v1160, &v100);
        }
        if (r->flags & 0x10) {
            Vec4 tmpF0;
            *(u128 *)&tmpF0 = *(u128 *)&o2->rot;
            Vec4 vE0 = {0};
            vE0.x = f26 * Sinf_128fd0(tmpF0.y);
            vE0.z = f26 * Cosf_128d30(tmpF0.y);
            VecAdd_1cbdc0(&v1160, &v1160, &vE0);
        }
        VecSub_1cbd00(&v1170, &v1160, &self->pos);
        if (!(m10 <= v1170.y)) continue;
        if (f23 < v1170.y) continue;
        if (!(VecLengthSqXZ_13d410(&v1170) <= f25)) continue;
        if (best < 0) {
            if (TargetRefGetKind_2e7130(&self->tgt) == 3 && id == TargetRefGetId_2e7120(&self->tgt)) {
                best = n;
            }
        }
        e = &ents[n];
        TargetRefSetModelKind3_2e6660(e, id, r->id, 0.0f);
        e->ang = WrapAngle_13c050(Atan2f_1291a8(v1170.x, v1170.z) - f24);
        n++;
    }
    pe = ents;
    lim = D_0047D404;
    res = -1;
    sel = -1;
    if ((u8)far == 0 && best >= 0) {
        dir = 0;
        if (PadIsTriggered_1839f0(D_004B2570, 0x2000) != 0) dir--;
        if (PadIsTriggered_1839f0(D_004B2570, 0x8000) != 0) dir++;
        cur = pe[best].ang;
        step = D_0047D1FC;
        res = best;
        if (dir < 0) step = D_0047DC4C;
        if (dir != 0) {
            for (k = 0; k < n; k++, pe++) {
                if (!(Abs(pe->ang) <= *(f32 *)&D_0047D404)) continue;
                a = *(volatile f32 *)&pe->ang;
                if ((dir < 0 && !(a <= cur)) || (dir > 0 && a < cur)) a += step;
                if ((dir < 0 && a < cur && (sel < 0 || !(a <= f21))) ||
                    (dir > 0 && !(a <= cur) && (sel < 0 || a < f21))) {
                    f21 = a;
                    sel = k;
                }
            }
        }
    } else {
        for (k = 0; k < n; k++, pe++) {
            a = pe->ang;
            if (a < 0.0f) a = -a;
            if (a < lim) {
                lim = a;
                res = k;
            }
        }
    }
    if (res >= 0) {
        if (sel < 0) {
            self->tgt = ents[res].t;
        } else {
            self->tgt = ents[sel].t;
        }
        return 1;
    }
    TargetRefSetId_2e6780(&self->tgt, -1);
    return 0;
}
