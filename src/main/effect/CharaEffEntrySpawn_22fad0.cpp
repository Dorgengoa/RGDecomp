#define KI 1
#define KM 1
#define KZ 3
#include "types.h"
#ifndef KZ
#define KZ 0
#endif
#ifndef KR
#define KR 0
#endif

#ifdef __cplusplus
extern "C" {
#endif
typedef struct { f32 x, y, z, w; } Vec4;
typedef struct { f32 m[4][4]; } Mtx;
typedef struct { u8 name[4]; s16 id; } Ref;
typedef struct { s32 f0; s32 ret; s32 chk; s32 fc; s32 pad[4]; } Req;
typedef struct {
    f32 f0[6];
    s32 i18[6];
    f32 v30[3];
    f32 v3c[3];
    f32 v48[3];
    u16 pad54[2];
    s32 w58;
    s32 w5c;
    u16 flags;
    s16 idx62;
    Ref r64;
    Ref r6a;
    Ref r70;
    Ref r76;
} Self;
#if KZ == 3
struct S16 { s16 v; S16 &operator=(const S16 &o) { v = o.v; return *this; } };
typedef struct { S16 a; S16 b; s32 w[11]; } Blk;
#else
typedef struct { s16 a; s16 b; s32 w[11]; } Blk;
#endif

void FrameCalcWorldMatrix_148ff0(void *, Mtx *);
void *ModelGetRootFrame_1511a0(void *);
void MatGetEulerRot_1cb160(Vec4 *, Mtx *);
void MatFromRot_1cb180(Mtx *, Vec4 *);
f32 VecLength_1cb4c0(void *);
void MatMul_1cb700(Mtx *, Mtx *, Mtx *);
void MatMulVec4_1cb940(Vec4 *, Mtx *, Vec4 *);
void MatIdentity_1cbe40(Mtx *);
void *GetObjNodeByName_1ce3a0(u8 *, s16, char *);
void *GetLiveObjById_1ce420(u8 *, s16);
s32 GetActionMgr_1fdb50(void);
Blk *CharaGetTargetRef_214a30(u8 *);
u8 *ActionMgrFindById_233b50(s32, u8 *);
void *GetEffectMgr_2d9040(void);
Blk *EffectGetTargetRef_2e0030(void *, Req *);
void EffectSetId_2e0100(void *, Req *, u8 *);
void EffectSetName_2e01c0(void *, Req *, s32);
void EffectSetParamInt_2e0530(void *, Req *, s32, s32);
void EffectSetParamFloat_2e0600(void *, Req *, s32, f32);
void EffectAttachToNode_2e0790(void *, Req *, void *);
void EffectSetRot_2e09f0(void *, Req *, Vec4 *);
void EffectSetPos_2e0bb0(void *, Req *, Vec4 *);
void EffectSetScale_2e0ce0(void *, Req *, Vec4 *);
void EffectCreateByName_2e1020(Req *, void *, s32, s16);
void EffectSetAutoRelease_2e1170(void *, Req *, s32);
void TargetRefClear_2e71d0(Blk *);
char *ReadU32Bytes_302ec0(Ref *);
extern f32 D_0047E6F0;
extern f32 D_0047E6F4;
extern f32 D_0047E6F8;
extern f32 D_0047E6FC;
extern f32 D_0047E700;
extern f32 D_0047E704;
extern f32 D_0047E708;
extern f32 D_0047E70C;

static inline void *Resolve(u8 *model, Ref *ref)
{
    char *n = ReadU32Bytes_302ec0(ref);
    if (n != 0 && *n != 0) return GetObjNodeByName_1ce3a0(model, ref->id, n);
    {
        void *m = GetLiveObjById_1ce420(model, ref->id);
        if (m == 0) return 0;
        return ModelGetRootFrame_1511a0(m);
    }
}
#define RESOLVE(out, model, ref) { \
    char *n_ = ReadU32Bytes_302ec0(ref); \
    if (n_ != 0 && *n_ != 0) { out = GetObjNodeByName_1ce3a0(model, (ref)->id, n_); } \
    else { void *m_ = GetLiveObjById_1ce420(model, (ref)->id); if (m_ == 0) out = 0; else out = ModelGetRootFrame_1511a0(m_); } }

#if KR
#define GET(out, model, ref) RESOLVE(out, model, ref)
#else
#define GET(out, model, ref) out = Resolve(model, ref);
#endif

s32 CharaEffEntrySpawn_22fad0(Self *self, u8 *model)
{
    Req req;
    Vec4 v170;
    Mtx m130;
    Vec4 v120;
    Mtx mE0;
    Mtx mA0;
    Vec4 v90;
    Mtx m50;
#if KI
    s32 idx;
#else
    s16 idx;
#endif
    void *ctx;
    void *m;
    s32 i;
    Blk *p;
    u8 *c;
    Blk *src;

    idx = -1;
    if (self->flags & 1) idx = self->idx62;
    ctx = GetEffectMgr_2d9040();
    EffectCreateByName_2e1020(&req, ctx, self->w58, idx);
    if (req.chk < 0) return -1;
    EffectSetId_2e0100(ctx, &req, model);
    if (!(self->flags & 2)) EffectSetAutoRelease_2e1170(ctx, &req, 1);
    v170.x = D_0047E6F0;
    v170.y = D_0047E6F4;
    v170.z = D_0047E6F8;
    v170.w = D_0047E6FC;
    if (self->flags & 0x800) {
        v170.x = self->v30[0];
        v170.y = self->v30[1];
        v170.z = self->v30[2];
        v170.w = 1.0f;
    }
    if (self->flags & 0x100) {
        GET(m, model, &self->r6a)
#if KM
        if (m == 0) MatIdentity_1cbe40(&m130);
        else FrameCalcWorldMatrix_148ff0(m, &m130);
#else
        if (m != 0) FrameCalcWorldMatrix_148ff0(m, &m130);
        else MatIdentity_1cbe40(&m130);
#endif
        MatMulVec4_1cb940(&v170, &m130, &v170);
    }
    EffectSetPos_2e0bb0(ctx, &req, &v170);
    { u8 *p_ = (u8 *)&v120; u32 n_ = 16; if (p_) while (n_) { *p_ = 0; n_--; p_++; } }
    if (self->flags & 0x1000) {
        v120.x = self->v3c[0];
        v120.y = self->v3c[1];
        v120.z = self->v3c[2];
        *(s32 *)&v120.w = 0;
    }
    if (self->flags & 0x200) {
        GET(m, model, &self->r70)
#if KM
        if (m == 0) MatIdentity_1cbe40(&mE0);
        else FrameCalcWorldMatrix_148ff0(m, &mE0);
#else
        if (m != 0) FrameCalcWorldMatrix_148ff0(m, &mE0);
        else MatIdentity_1cbe40(&mE0);
#endif
        MatFromRot_1cb180(&mA0, &v120);
        MatMul_1cb700(&mA0, &mE0, &mA0);
        MatGetEulerRot_1cb160(&v120, &mA0);
    }
    EffectSetRot_2e09f0(ctx, &req, &v120);
    v90.x = D_0047E700;
    v90.y = D_0047E704;
    v90.z = D_0047E708;
    v90.w = D_0047E70C;
    if (self->flags & 0x2000) {
        v90.x = self->v48[0];
        v90.y = self->v48[1];
        v90.z = self->v48[2];
        *(s32 *)&v90.w = 0;
    }
    if (self->flags & 0x400) {
        GET(m, model, &self->r76)
#if KM
        if (m == 0) MatIdentity_1cbe40(&m50);
        else FrameCalcWorldMatrix_148ff0(m, &m50);
#else
        if (m != 0) FrameCalcWorldMatrix_148ff0(m, &m50);
        else MatIdentity_1cbe40(&m50);
#endif
        v90.x = VecLength_1cb4c0(m50.m[0]);
        v90.y = VecLength_1cb4c0(m50.m[1]);
        v90.z = VecLength_1cb4c0(m50.m[2]);
        *(s32 *)&v90.w = 0;
    }
    EffectSetScale_2e0ce0(ctx, &req, &v90);
    if (self->flags & 0x80) {
        GET(m, model, &self->r64)
        if (m != 0) EffectAttachToNode_2e0790(ctx, &req, m);
    }
    if (self->flags & 8) EffectSetName_2e01c0(ctx, &req, self->w5c);
    if (self->flags & 0x10) {
        for (i = 0; i < 6; i++) EffectSetParamInt_2e0530(ctx, &req, i, self->i18[i]);
    }
    if (self->flags & 0x20) {
        for (i = 0; i < 6; i++) EffectSetParamFloat_2e0600(ctx, &req, i, self->f0[i]);
    }
    p = EffectGetTargetRef_2e0030(ctx, &req);
    if (p != 0) {
        TargetRefClear_2e71d0(p);
        c = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), model);
        if (c != 0 && (*(s32 *)(c + 0xA44) & 0x8000)) {
#if KZ == 1 || KZ == 3
            src = CharaGetTargetRef_214a30(c);
            *p = *src;
#elif KZ == 2
            s32 n_;
            s32 *d_;
            s32 *s_;
            src = CharaGetTargetRef_214a30(c);
            p->a = src->a;
            p->b = src->b;
            s_ = src->w;
            d_ = p->w;
            n_ = 11;
            do {
                n_--;
                *d_ = *s_;
                s_++;
                d_++;
            } while (n_ > 0);
#else
            s32 *s_;
            s32 *d_;
            s32 n_;
            src = CharaGetTargetRef_214a30(c);
            p->a = src->a;
            p->b = src->b;
            s_ = src->w;
            d_ = p->w;
            n_ = 11;
            do {
                n_--;
                *d_ = *s_;
                s_++;
                d_++;
            } while (n_ > 0);
#endif
        }
    }
    return req.ret;
}
#ifdef __cplusplus
}
#endif
