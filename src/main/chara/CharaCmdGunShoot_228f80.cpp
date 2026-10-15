#pragma opt_rebuildconditionals off
#pragma opt_propagation off
#pragma opt_common_subs off
#include "types.h"

class Unit {
public:
    virtual void vf0(); virtual void vf1(); virtual void vf2(); virtual void vf3(); virtual void vf4(); virtual void vf5();
    virtual void vf6(); virtual void vf7(); virtual void vf8(); virtual void vf9(); virtual void vf10(); virtual void vf11();
    virtual void vf12(); virtual void vf13(); virtual void vf14(); virtual void vf15(); virtual void vf16(); virtual void vf17();
    virtual void vf18(); virtual void vf19(); virtual void vf20(); virtual void vf21(); virtual void vf22(); virtual void vf23();
    virtual void vf24(); virtual void vf25(); virtual void vf26(); virtual void vf27(); virtual void vf28(); virtual void vf29();
    virtual void vf30(); virtual void vf31(); virtual void vf32(); virtual void vf33(); virtual void vf34(); virtual void vf35();
    virtual void vf36(); virtual void vf37(); virtual void vf38(); virtual void vf39(); virtual void vf40(); virtual void vf41();
    virtual void vf42(); virtual void vf43(); virtual void vf44(); virtual void vf45(); virtual void vf46(); virtual void vf47();
    virtual void vf48(); virtual void vf49(); virtual void vf50(); virtual void vf51(); virtual void vf52(); virtual void vf53();
    virtual void vf54(); virtual void vf55(); virtual void vf56(); virtual void vf57();
    virtual s32 Count(s32); /* 0xF0 */
    virtual void vf59(); virtual void vf60(); virtual void vf61(); virtual void vf62(); virtual void vf63(); virtual void vf64();
    virtual void vf65(); virtual void vf66(); virtual void vf67(); virtual void vf68(); virtual void vf69(); virtual void vf70();
    virtual void vf71(); virtual void vf72(); virtual void vf73(); virtual void vf74(); virtual void vf75(); virtual void vf76();
    virtual void vf77(); virtual void vf78(); virtual void vf79(); virtual void vf80(); virtual void vf81(); virtual void vf82();
    virtual void vf83(); virtual void vf84(); virtual void vf85(); virtual void vf86(); virtual void vf87(); virtual void vf88();
    virtual void vf89(); virtual void vf90(); virtual void vf91(); virtual void vf92(); virtual void vf93(); virtual void vf94();
    virtual void vf95(); virtual void vf96(); virtual void vf97(); virtual void vf98(); virtual void vf99(); virtual void vf100();
    virtual void vf101(); virtual void vf102(); virtual void vf103(); virtual void vf104(); virtual void vf105(); virtual void vf106();
    virtual void vf107(); virtual void vf108(); virtual void vf109(); virtual void vf110(); virtual void vf111(); virtual void vf112();
    virtual void vf113(); virtual void vf114(); virtual void vf115(); virtual void vf116(); virtual void vf117(); virtual void vf118();
    virtual void vf119(); virtual void vf120(); virtual void vf121(); virtual void vf122(); virtual void vf123(); virtual void vf124();
    virtual void vf125(); virtual void vf126(); virtual void vf127(); virtual void vf128(); virtual void vf129(); virtual void vf130();
    virtual void vf131(); virtual void vf132(); virtual void vf133(); virtual void vf134(); virtual void vf135(); virtual void vf136();
    virtual void vf137(); virtual void vf138(); virtual void vf139(); virtual void vf140(); virtual void vf141(); virtual void vf142();
    virtual void vf143(); virtual void vf144(); virtual void vf145(); virtual void vf146(); virtual void vf147(); virtual void vf148();
    virtual void vf149(); virtual void vf150(); virtual void vf151(); virtual void vf152(); virtual void vf153(); virtual void vf154();
    virtual void vf155(); virtual void vf156(); virtual void vf157(); virtual void vf158(); virtual void vf159(); virtual void vf160();
    virtual void vf161(); virtual void vf162(); virtual void vf163(); virtual void vf164(); virtual void vf165(); virtual void vf166();
    virtual void vf167(); virtual void vf168(); virtual void vf169(); virtual void vf170(); virtual void vf171(); virtual void vf172();
    virtual void vf173(); virtual void vf174(); virtual void vf175(); virtual void vf176(); virtual void vf177(); virtual void vf178();
    virtual void vf179(); virtual void vf180(); virtual void vf181(); virtual void vf182(); virtual void vf183(); virtual void vf184();
    virtual void vf185(); virtual void vf186(); virtual void vf187(); virtual void vf188(); virtual void vf189(); virtual void vf190();
    virtual void vf191(); virtual void vf192(); virtual void vf193(); virtual void vf194(); virtual void vf195(); virtual void vf196();
    virtual void vf197(); virtual void vf198(); virtual void vf199(); virtual void vf200(); virtual void vf201(); virtual void vf202();
    virtual void vf203(); virtual void vf204(); virtual void vf205(); virtual void vf206(); virtual void vf207(); virtual void vf208();
    virtual void vf209(); virtual void vf210(); virtual void vf211(); virtual void vf212(); virtual void vf213(); virtual void vf214();
    virtual void vf215(); virtual void vf216(); virtual void vf217(); virtual void vf218(); virtual void vf219(); virtual void vf220();
    virtual void vf221(); virtual void vf222();
    virtual Unit *Sub(s32); /* 0x384 */
};
#include "vec.h"
#pragma optimization_level 3
#pragma opt_arithtransformation off
#define A ((Emit *)&ab)
#define B ((Emit *)&bb)

class Emit {
public:
    u8 pad0[0xB0];
    virtual void vf0(); virtual void vf1(); virtual void vf2(); virtual void vf3(); virtual void vf4(); virtual void vf5();
    virtual void vf6(); virtual void vf7(); virtual void vf8(); virtual void vf9(); virtual void vf10(); virtual void vf11();
    virtual void vf12(); virtual void vf13(); virtual void vf14(); virtual void vf15(); virtual void vf16(); virtual void vf17();
    virtual void vf18();
    virtual void Pos(f32, f32, f32); /* 0x54 */
    virtual void vf20(); virtual void vf21();
    virtual void Scale(f32); /* 0x60 */
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
extern const f32 D_0047D278 __attribute__((section(".sdata")));
extern const f32 D_0047DB7C __attribute__((section(".sdata")));
extern f32 D_0047E6E0[4];
s32 CharaCmdGunShoot_228f80(s32 *e, s32 base, s32 kind);
}

extern "C" s32 CharaCmdGunShoot_228f80(s32 *e, s32 base, s32 kind)
{
    Cam cam;
    Vec4 v60;
    Vec4 v50;
    Vec4 v40;
    Vec4 v30;
    Rq rq;
    EmitBuf ab;
    Vec4 dir;
    Vec4 tgt;
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
    if (u != 0 && u->Sub(CharaGetBaseActionMode_213830(w) != 2)->Count(0) <= 0) {
        k = GameSceneSoundSlot5GetHandle_1d0790(ctx);
        SoundPlayScaledVolume_1b9520(k, 0xC, SoundNextPlayHandle_1b81c0(), 1.0f);
        return 1;
    }
    c = ObjRecGetLiveObject_1c4a90(ctx, e[0]);
    if (c != 0) {
        k = c->x4FC;
        SoundPlayScaledVolume_1b9520(k, 0x46, SoundNextPlayHandle_1b81c0(), 1.0f);
    }
    FrameCalcWorldMatrix_148ff0(s1, &v50);
    MatToRotPos_1cade0(&v30, &v40, &v50);
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
            s32 r = CharaGetBaseActionMode_213830(w);
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
        VecCopy_1cbe30(&dir, &cam);
    }
    VecScaleToLength_1cb510(&dir, &cam, 20.0f * D_0045B080[0]);
    A->xBC = 1;
    A->Scale(10.0f);
    A->Pos(cam.x10.x, cam.x10.y, cam.x10.z);
    A->x1B0 = dir;
    ProjectileCloneAndRegister_22e560(A);
    *(u8 **)(A->pad0 + 0xB0) = D_00471AA0;
    {
    F4 col = *(F4 *)D_0047E6E0;
    EmitBuf bb;
    t = (RandFloat_13c010() - D_0047D278) / 2.0f;
    VecLinearCombine_1cb8b0(&tgt, &cam, &v60, t, (1.0f + RandFloat_13c010()) / 8.0f);
    tgt.y += 2.5f;
    MatMulVec4_1cb940((Vec4 *)&col, &v50, (Vec4 *)&col);
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
