#include "types.h"

typedef struct Vec { f32 x, y, z, w; } Vec;
typedef struct Out { s32 i0; s16 s4; s16 s6; } Out;

class Self {
public:
    u8 pad0[0x10];
    Vec pos;            /* 10 */
    u8 pad20[0x38];
    u8 m58[0x48];       /* 58 */
    u8 mA0[0x30];       /* A0 */
    u32 flags;          /* D0 */
    u8 padD4[8];
    virtual s16 kind(); /* vptr DC, slot +8 */
    void *pE0;          /* E0 */
    u8 padE4[8];
    f32 fEC;            /* EC */
    u8 padF0[8];
    f32 fF8;            /* F8 */
};

typedef struct Ent { u8 pad[0x3D8]; u32 f3D8; } Ent;

extern "C" {
s32 TargetRefGetKind_2e7130(void *);
s32 TargetRefGetId_2e7120(void *);
void XformToLocal_2e7440(void *, Vec *, Vec *);
s32 EventVolumeRecAnyHit_2e4c70(void *, Vec *, f32);
s32 EventRecGetKey_2e5730(Self *);
void EventVolumeRecGetPoint_2e4d40(void *, Vec *);
void XformTransformPoint_2e75a0(Vec *, Vec *, Vec *);
u8 *GetGameData_1fede0(void);
void *GetActionMgr_1fdb50(void);
Ent *ActionMgrFindById_233b50(void *, s32);
s32 CharaHasEvObjContact_214960(Ent *);
char **CharaGetEvObjContact_214990(Ent *);
s32 StrEqualNonNull_1ca6c0(char *, s32);
void VecSub_1cbd00(Vec *, Vec *, Vec *);
f32 VecLength_1cb4c0(Vec *);
void VecScaleToLength_1cb510(Vec *, Vec *, f32);
void VecAdd_1cbdc0(Vec *, Vec *, Vec *);
void VecCopy_1cbe30(Vec *, Vec *, f32);
s32 CharaGetActionKind_213840(Ent *);
void CharaGetVelocity_238890(Ent *, Vec *);
void CharaSetVelocityFromVec_238790(Ent *, Vec *);
void *GetCurrentScene_1f5be0(void);
void *ObjRecGetLiveObject_1c4a90(void *, s32);
f32 ModelObjGetBodyWeight_23b0f0(void *);
}
extern f32 D_0045B080[];
extern f32 D_0047D1E8;
extern f32 D_0047D280;

static inline bool clr(u32 f, u32 m) { return !(f & m); }

extern "C" s32 ObjTypeMonographHitTest_372240(Self *self, Out *out, s32 id, Vec *vec, s32 unused, s32 on) {
    Vec vE0;
    Vec vD0;
    Vec vC0;
    Vec vB0;
    Vec vA0;
    Vec v90;
    Vec v80;
    u32 fl;
    u8 ok;
    s32 cur;
    Ent *e;
    char **pn;
    f32 s;
    f32 lim;
    f32 d;
    f32 t;
    f32 k;

    if (on == 0) return 0;
    fl = self->flags;
    if (!clr(fl, 0x80000000)) return 0;
    if (id < 0 || id >= 12) return 0;
    if (!(self->fF8 < 0.0f)) return 0;
    if (!clr(fl, 0x40000000) || !clr(fl, 0x20000000)) return 0;
    if ((TargetRefGetKind_2e7130(self->mA0) == 5 || TargetRefGetKind_2e7130(self->mA0) == 4) && id == TargetRefGetId_2e7120(self->mA0)) return 0;
    if (self->pE0 == 0) return 0;
    XformToLocal_2e7440(self->m58, &vE0, vec);
    if (EventVolumeRecAnyHit_2e4c70(self->pE0, &vE0, 0.0f) == 0) return 0;
    out->s4 = self->kind();
    out->i0 = EventRecGetKey_2e5730(self);
    out->s6 = 9;
    EventVolumeRecGetPoint_2e4d40(self->pE0, &vD0);
    XformTransformPoint_2e75a0(&self->pos, &vD0, &vD0);
    if (!(self->flags & 0x4000)) {
        ok = true;
        cur = ((s16 *)(*(u8 **)(GetGameData_1fede0() + 0x18)))[0x18E / 2];
        if (id != cur) {
            e = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), cur);
            if (e != 0 && CharaHasEvObjContact_214960(e) != 0) {
                pn = CharaGetEvObjContact_214990(e);
                ok = (u8)((StrEqualNonNull_1ca6c0(*pn, EventRecGetKey_2e5730(self)) != 0) ^ 1);
            }
        }
        if (ok) {
            XformTransformPoint_2e75a0(&self->pos, vec, &vE0);
            VecSub_1cbd00(&vC0, &vD0, vec);
            s = D_0045B080[0];
            lim = D_0047D280 * s; if (vC0.y < lim) {
                EventVolumeRecGetPoint_2e4d40(self->pE0, &vB0);
                XformTransformPoint_2e75a0(&self->pos, &vB0, &vB0);
                VecSub_1cbd00(&vA0, &vB0, vec);
                if (VecLength_1cb4c0(&vA0) <= (lim = 0.25f * s)) {
                    VecCopy_1cbe30(vec, &vB0, lim);
                } else {
                    VecScaleToLength_1cb510(&vA0, &vA0, lim);
                    VecAdd_1cbdc0(vec, vec, &vA0);
                }
            } else {
                e = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), id);
                if (e != 0 && CharaGetActionKind_213840(e) == 2) {
                    CharaGetVelocity_238890(e, &v90);
                    v90.y = 0.0f;
                    CharaSetVelocityFromVec_238790(e, &v90);
                    vec->y = vD0.y;
                } else {
                    return 0;
                }
            }
        }
    }
    k = D_0045B080[0];
    d = vec->y - vD0.y;
    if (d < 0.0f) d = -d;
    if (d < D_0047D1E8 * k) {
        self->fEC = self->fEC + ModelObjGetBodyWeight_23b0f0(ObjRecGetLiveObject_1c4a90(GetCurrentScene_1f5be0(), id));
        e = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), id);
        if (e != 0 && (e->f3D8 & 1)) {
            CharaGetVelocity_238890(e, &v80);
            if (v80.y < 0.0f) vec->y = vD0.y;
            out->s6 |= 0x10;
        }
        if (self->flags & 0x4000) out->s6 &= ~1;
    }
    return 1;
}
