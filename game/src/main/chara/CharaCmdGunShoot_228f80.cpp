/* rgp:protos */
#line 1
#pragma opt_rebuildconditionals off
#pragma opt_propagation off
#pragma opt_common_subs off
#include "types.h"

class Unit {
public:
    VC_VPTR_MEMBER;     
         
         
         
         
         
         
         
         
       
    s32 Count(s32 a0) { return VCM(s32, (void *, s32), 0xF0, a0); } /* 0xF0 */
         
         
         
         
         
         
         
         
         
         
         
         
         
         
         
         
         
         
         
         
         
         
         
         
         
         
         
     
    Unit * Sub(s32 a0) { return VCM(Unit *, (void *, s32), 0x384, a0); } /* 0x384 */
};
#include "vec.h"
#pragma optimization_level 3
#pragma opt_arithtransformation off
#define A ((Emit *)&ab)
#define B ((Emit *)&bb)

class Emit {
public:
    u8 pad0[0xB0];
    VC_VPTR_MEMBER;     
         
         
    
    void Pos(f32 a0, f32 a1, f32 a2) { VCM(void, (void *, f32, f32, f32), 0x54, a0, a1, a2); } /* 0x54 */
     
    void Scale(f32 a0) { VCM(void, (void *, f32), 0x60, a0); } /* 0x60 */
    u8 padB4[8];
    s16 xBC;
    u8 padBE[0x1B0 - 0xBE];
    Vec4 x1B0;
    s32 x1C0;
    f32 x1C4;
    f32 x1C8;
    u8 pad1CC[0x630 - 0x1CC];
};

typedef struct EmitBuf {
    u8 d[0x630];
} __attribute__((aligned(16))) EmitBuf;

typedef struct Cam {
    Vec4 x0;
    Vec4 x10;
} Cam;

typedef struct Rq {
    u8 pad0[8];
    s32 x8;
    u8 padC[0x20 - 0xC];
} Rq;

typedef struct Wk {
    u8 pad0[0xA44];
    u32 xA44;
} Wk;

typedef struct Chr {
    u8 pad0[0x4FC];
    s32 x4FC;
} Chr;

typedef struct Gm {
    u8 pad0[0x14];
    s32 x14;
} Gm;

typedef struct F4 { f32 x, y, z, w; } F4;
extern "C" {
f32 RandFloat_13c010(void);
void FrameCalcWorldMatrix_148ff0(s32, Vec4 *);
s32 SoundNextPlayHandle_1b81c0(void);
void SoundPlayScaledVolume_1b9520(s32, s32, s32, f32);
Chr *ObjRecGetLiveObject_1c4a90(s32, s32);
void MatToRotPos_1cade0(Vec4 *, Vec4 *, Vec4 *);
void VecScaleToLength_1cb510(Vec4 *, Cam *, f32);
void VecLinearCombine_1cb8b0(Vec4 *, Cam *, Vec4 *, f32, f32);
void MatMulVec4_1cb940(Vec4 *, Vec4 *, Vec4 *);
void VecSub_1cbd00(Vec4 *, Vec4 *, Vec4 *);
void VecCopy_1cbe30(Vec4 *, Cam *);
s32 GetObjNodeByName_1ce3a0(s32, s32, s32);
s32 GameSceneSoundSlot5GetHandle_1d0790(s32);
s32 GetCurrentScene_1f5be0(void);
s32 GetActionMgr_1fdb50(void);
Gm *GetGameData_1fede0(void);
s32 CharaGetBaseActionMode_213830(Wk *);
void CharaGetTargetPos_214a40(Wk *, Vec4 *);
void ProjectileCloneAndRegister_22e560(Emit *);
Wk *ActionMgrFindById_233b50(s32, s32);
f32 GetScaledGravity_23b170(void);
s32 GetEffectMgr_2d9040(void);
void EffectSetId_2e0100(s32, Rq *, s32);
void EffectSetRot_2e09f0(s32, Rq *, Vec4 *);
void EffectSetPos_2e0bb0(s32, Rq *, Vec4 *);
void EffectCreateByName_2e1020(Rq *, s32, s32, s32);
void EffectSetAutoRelease_2e1170(s32, Rq *, s32);
s32 ScriptArgGetStr_302cb0(s32);
s32 ScriptArgGetInt_302d70(s32);
s32 GetSphereModel_313e00(void);
void ProjectileCtor_317eb0(Emit *, s32, s32, s32, f32);
void ExecInfoInitFromObj_3a7790(void *, s32, s32);
void ExecInfoInitFromChara_3a7830(void *, s32, u8, s32, s32);
Unit *CharaMgrPoolFindById_3a8c60(s32, s32);
extern f32 D_0045B080[];
extern u8 D_00471AA0[];
extern f32 D_0047D278 __attribute__((section(".sdata")));
extern f32 D_0047DB7C __attribute__((section(".sdata")));
extern f32 D_0047E6E0[4];
s32 CharaCmdGunShoot_228f80(s32 *e, s32 base, s32 kind);
}

extern "C" s32 CharaCmdGunShoot_228f80(s32 *e, s32 base, s32 kind)
{
    __attribute__((aligned(16))) unsigned char rgp_blk1[(0x20 + sizeof(Cam)) + (0x0 + sizeof(Vec4)) + (0x10 + sizeof(Vec4)) + (0x40) + (0x30) + (0x20)]; typedef char rgp_blk1_chk0[(0x0) + sizeof(Vec4) <= (0x10) && (0x0) >= 0 ? 1 : -1]; typedef char rgp_blk1_chk1[(0x10) + sizeof(Vec4) <= (0x20) && (0x10) >= 0 ? 1 : -1];
    
    
    Vec4 v40 __attribute__((aligned(16)));
    Vec4 v30 __attribute__((aligned(16)));
    Rq rq __attribute__((aligned(16)));
    EmitBuf ab __attribute__((aligned(16)));
    Vec4 dir __attribute__((aligned(16)));
    Vec4 tgt __attribute__((aligned(16)));
    Wk *w;
    s32 k;
    s32 s1;
    Unit *u;
    s32 ctx;
    Chr *c;
    s32 m;
    s32 id;
    u8 f;
    s32 tf;
    u8 *em;
    f32 t;

    if (kind != 4) {
        return 0;
    }
    w = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), e[0]);
    if (w == 0) {
        return 1;
    }
    k = ScriptArgGetInt_302d70(base + 5);
    s1 = GetObjNodeByName_1ce3a0(e[0], k, ScriptArgGetStr_302cb0(base + 0xA));
    if (s1 == 0) {
        return 1;
    }
    u = CharaMgrPoolFindById_3a8c60(GetGameData_1fede0()->x14, e[0]);
    ctx = GetCurrentScene_1f5be0();
    if (u != 0 && u->Sub(((short)CharaGetBaseActionMode_213830(w)) != 2)->Count(0) <= 0) {
        k = GameSceneSoundSlot5GetHandle_1d0790(ctx);
        SoundPlayScaledVolume_1b9520(k, 0xC, SoundNextPlayHandle_1b81c0(), 1.0f);
        return 1;
    }
    c = ObjRecGetLiveObject_1c4a90(ctx, e[0]);
    if (c != 0) {
        k = c->x4FC;
        SoundPlayScaledVolume_1b9520(k, 0x46, SoundNextPlayHandle_1b81c0(), 1.0f);
    }
    FrameCalcWorldMatrix_148ff0(s1, &(*(Vec4 *)(rgp_blk1 + 0x0)));
    MatToRotPos_1cade0(&v30, &v40, &(*(Vec4 *)(rgp_blk1 + 0x0)));
    m = GetEffectMgr_2d9040();
    EffectCreateByName_2e1020(&rq, m, ScriptArgGetStr_302cb0(base + 0xF), -1);
    if (rq.x8 < 0) {
        return 1;
    }
    EffectSetAutoRelease_2e1170(m, &rq, 1);
    EffectSetId_2e0100(m, &rq, e[0]);
    EffectSetPos_2e0bb0(m, &rq, &v40);
    EffectSetRot_2e09f0(m, &rq, &v30);
    ProjectileCtor_317eb0(A, 1, e[0], 5, 150.0f);
    id = e[0];
    em = A->pad0 + 0x10;
    if (id >= 0 && id < 0xC) {
        {
            s32 r = ((short)CharaGetBaseActionMode_213830(w));
            u8 v;
if (r == 3) v = 1; else v = 0;
            tf = (u8)v;
        }
        ExecInfoInitFromChara_3a7830(em, e[0], tf, 0, ScriptArgGetStr_302cb0(base));
    } else if (id >= 0x80 && id < 0x9C) {
        ExecInfoInitFromObj_3a7790(em, e[0], ScriptArgGetStr_302cb0(base));
    }
    if (w->xA44 & 0x8000) {
        CharaGetTargetPos_214a40(w, &dir);
        VecSub_1cbd00(&dir, &dir, &v40);
    } else {
        VecCopy_1cbe30(&dir, &(*(Cam *)(rgp_blk1 + 0x20)));
    }
    VecScaleToLength_1cb510(&dir, &(*(Cam *)(rgp_blk1 + 0x20)), 20.0f * D_0045B080[0]);
    A->xBC = 1;
    A->Scale(10.0f);
    A->Pos((*(Cam *)(rgp_blk1 + 0x20)).x10.x, (*(Cam *)(rgp_blk1 + 0x20)).x10.y, (*(Cam *)(rgp_blk1 + 0x20)).x10.z);
    A->x1B0 = dir;
    ProjectileCloneAndRegister_22e560(A);
    *(u8 **)(A->pad0 + 0xB0) = D_00471AA0;
    {
    F4 col __attribute__((aligned(16))) = *(F4 *)D_0047E6E0;
    EmitBuf bb __attribute__((aligned(16)));
    t = (RandFloat_13c010() - D_0047D278) / 2.0f;
    VecLinearCombine_1cb8b0(&tgt, &(*(Cam *)(rgp_blk1 + 0x20)), &(*(Vec4 *)(rgp_blk1 + 0x10)), t, (1.0f + RandFloat_13c010()) / 8.0f);
    tgt.y += 2.5f;
    MatMulVec4_1cb940((Vec4 *)&col, &(*(Vec4 *)(rgp_blk1 + 0x0)), (Vec4 *)&col);
    ProjectileCtor_317eb0(B, 0, 0, 4, 60.0f);
    B->x1C0 = GetSphereModel_313e00();
    B->xBC = 3;
    B->Scale(0.25f);
    B->Pos(col.x, col.y, col.z);
    B->x1B0 = tgt;
    B->x1C4 = GetScaledGravity_23b170();
    B->x1C8 = D_0047DB7C * (1.0f + RandFloat_13c010());
    ProjectileCloneAndRegister_22e560(B);
    *(u8 **)(B->pad0 + 0xB0) = D_00471AA0;
    }
    return 1;
}
