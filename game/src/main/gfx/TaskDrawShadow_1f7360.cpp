/* rgp:protos */
#line 1
#include "types.h"

typedef struct {
    f32 x, y, z, w;
} V4_1F7360;

class Cam1F7360 {
    u8 pad[0xC0];
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f39(f32 * a0) { VCM(void, (void *, f32 *), 0xA4, a0); }
};

class Ent1F7360 {
    u8 pad[0x1B0];
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f16() { VCM0(void, 0x48); }
};

class V1F7360 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v120() { VCM0(void, 0x1E8); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v160() { VCM0(void, 0x288); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    u8 * f211() { return VCM0(u8 *, 0x354); }
};

extern "C" {
extern void DrawListAddTexLoad_1418c0(s32, s32, f32);
extern void DrawListEndPlaneShadowPass_146cc0(s32);
extern void DrawListAddPlaneShadowMtxPkt_147ae0(s32, void *);
extern void DrawListBeginPlaneShadowPass_147b80(s32, void *);
extern void FrameGetWorldPos_148f30(s32, f32 *);
extern void ModelSetScale_150ff0(Ent1F7360 *, f32 *);
extern void ModelSetPos_151110(Ent1F7360 *, f32 *);
extern s32 ModelGetRootFrame_1511a0(Ent1F7360 *);
extern void PlaneShadowDescSetPlane_156a20(void *, void *, void *, void *);
extern void PlaneShadowDescInit_156a70(void *);
extern s32 NameTableFindByName_159fb0(s32, void *, s32);
extern void NameTableCopyNode_15ad70(void *, s32);
extern void NameTableNodeCtor_15ae50(void *);
extern s32 GetDrawCtxNameTable_15de40(void);
extern s32 GetDrawCtx_15de80(void);
extern void Character2LightBlendGetMatrices_1aeb90(Ent1F7360 *, f32 *, f32 *);
extern Cam1F7360 *ObjRecGetLiveObject_1c3bc0(u8 *, s32);
extern s32 ObjRecGetFlags_1c3d90(u8 *, s32, s32);
extern s32 ObjRecHasFlags6_1c3eb0(u8 *, s32, s32);
extern Ent1F7360 *ObjRecGetLiveObject_1c4a90(u8 *, s32);
extern f32 VecDistSq_1cb3c0(f32 *, f32 *);
extern f32 VecLengthSqXZ_1cb450(f32 *, void *);
extern f32 VecLengthSq_1cb470(f32 *, void *);
extern void VecScaleToLength_1cb510(f32 *, f32 *, f32);
extern void VecNormalize_1cbb80(f32 *, f32 *);
extern void VecCopy_1cbe30(void *, f32 *);
extern f32 ParamTableGetAlpha_1cfb40(u8 *, s32);
extern s32 GetGameMode_1f59c0(void);
extern u8 *GetCurrentScene_1f5be0(void);
extern u8 *GetGameData_1fede0(void);
extern u8 *ActionMgrFindById_233b50(void *, s32);
extern f32 CharaGetHeightAboveGround_238380(u8 *);
extern s32 ObjGetNthAttachPointPosSafe_23b0c0(Ent1F7360 *, s32, s32, f32 *);
extern f32 ModelObjGetScaledHeight_23b110(Ent1F7360 *);
extern f32 ModelObjGetScaledRadius_23b140(Ent1F7360 *);
extern V1F7360 * ActorCastToUnit_3b8770(s32, int, int, int);
extern s32 ActorFindById_3eb870(u8 *, s32);
extern f32 D_0045B080[];
extern u8 D_0045BCE0[];
extern u8 D_0045BCF0[];
extern f32 D_0047E510;
extern f32 D_0047E514;
extern f32 D_0047E518;
extern f32 D_0047E51C;
extern f32 D_0047E520;
extern f32 D_0047E524;
extern f32 D_0047E528;
extern f32 D_0047E52C;
extern f32 D_0047E530;
extern f32 D_0047E534;
extern f32 D_0047E538;
extern f32 D_0047E53C;
extern Ent1F7360 *D_00481A74;
extern s32 D_00481A78;
extern f32 D_004B6980[];
extern f32 D_004B6984[];
extern f32 D_004B6988[];
extern f32 D_004B698C[];
extern u8 D_004B8680[];
}

#define Map(i) (((i) >= 12 && (i) < 60) ? ((i) - 12) >> 2 : -1)

extern "C" void TaskDrawShadow_1f7360(void) {
    V4_1F7360 V330 __attribute__((aligned(16)));
    V4_1F7360 V320 __attribute__((aligned(16)));
    V4_1F7360 V310 __attribute__((aligned(16)));
    u8 s[0x190] __attribute__((aligned(16)));
    f32 cam[4] __attribute__((aligned(16)));
    f32 v160[4] __attribute__((aligned(16)));
    f32 v120[16] __attribute__((aligned(16)));
    f32 vE0[16] __attribute__((aligned(16)));
    f32 vD0[4] __attribute__((aligned(16)));
    f32 vC0[4] __attribute__((aligned(16)));
    u8 *d;
    f32 *pf;
    s32 mgr;
    s32 tl;
    s32 t;
    u8 *g;
    u8 *pl;
    s32 fp;
    bool s7;
    f32 f24;
    f32 f25;
    f32 f0;
    f32 f23;
    f32 f22;
    f32 f21;
    f32 k;
    f32 f20;
    s32 i;
    Ent1F7360 *e;
    u8 *s0;
    s32 c;
    V1F7360 *v;
    u8 *w;
    Ent1F7360 *s1;

    if (D_00481A78 > 0) {
        return;
    }
    d = GetGameData_1fede0();
    mgr = GetDrawCtx_15de80();
    tl = GetDrawCtxNameTable_15de40();
    DrawListAddTexLoad_1418c0(mgr, 0x320, 1.0f);
    NameTableFindByName_159fb0(tl, D_0045BCE0, -1);
    pf = (f32 *)&V330;
    pf[0] = D_0047E510;
    pf[1] = D_0047E514;
    pf[2] = D_0047E518;
    pf[3] = D_0047E51C;
    pf = (f32 *)&V320;
    pf[0] = D_0047E520;
    pf[1] = D_0047E524;
    pf[2] = D_0047E528;
    pf[3] = D_0047E52C;
    pf = (f32 *)&V310;
    pf[0] = D_0047E530;
    pf[1] = D_0047E534;
    pf[2] = D_0047E538;
    pf[3] = D_0047E53C;
    NameTableNodeCtor_15ae50(s + 0x30);
    NameTableNodeCtor_15ae50(s + 0x98);
    NameTableNodeCtor_15ae50(s + 0x110);
    PlaneShadowDescInit_156a70(s);
    PlaneShadowDescSetPlane_156a20(s, &V330, &V320, &V310);
    *(s32 *)(s + 0x100) = 1;
    *(s32 *)(s + 0x104) = 1;
    *(s32 *)(s + 0x108) = 1;
    *(f32 *)(s + 0x178) = D_004B698C[0];
    *(f32 *)(s + 0x180) = D_004B6980[0];
    *(f32 *)(s + 0x184) = D_004B6984[0];
    *(f32 *)(s + 0x188) = D_004B6988[0];
    *(f32 *)(s + 0x18C) = 1.0f;
    t = NameTableFindByName_159fb0(tl, D_0045BCE0, -1);
    if (t != 0) {
        NameTableCopyNode_15ad70(s + 0x30, t);
    }
    t = NameTableFindByName_159fb0(tl, D_0045BCF0, -1);
    if (t != 0) {
        NameTableCopyNode_15ad70(s + 0x110, t);
        *(s32 *)(s + 0x100) = 1;
    }
    DrawListBeginPlaneShadowPass_147b80(mgr, s);
    g = GetCurrentScene_1f5be0();
    pl = D_004B8680;
    fp = *(s16 *)(*(u8 **)(d + 0x18) + 0x18E);
    s7 = 0;
    if (GetGameMode_1f59c0() != 9 && GetGameMode_1f59c0() != 10) {
        s7 = 1;
    }
    ObjRecGetLiveObject_1c3bc0(g, *(s32 *)(g + 0x4344))->f39(cam);
    f24 = ModelObjGetScaledRadius_23b140(D_00481A74);
    i = 0;
    k = 30.0f * D_0045B080[0];
    f21 = 2.0f * D_0045B080[0];
    f22 = k * k;
    f20 = -2.0f * D_0045B080[0];
    for (; i < 0xE0; i++) {
        if (((unsigned char)ObjRecHasFlags6_1c3eb0(g, 1, i)) == 0) {
            continue;
        }
        if (ObjRecGetFlags_1c3d90(g, 1, i) & 0x20) {
            continue;
        }
        if (ObjRecGetFlags_1c3d90(g, 1, i) & 0x40) {
            continue;
        }
        e = ObjRecGetLiveObject_1c4a90(g, i);
        if (e == 0) {
            continue;
        }
        if (*(s32 *)(g + 0x4344) == 3) {
            if (i >= 12 && i < 60) {
                if (fp == Map(i)) {
                    continue;
                }
            } else if (fp == i) {
                continue;
            }
        }
        if (i >= 12 && i < 60) {
            s0 = ActionMgrFindById_233b50(pl, Map(i));
        } else {
            s0 = ActionMgrFindById_233b50(pl, i);
        }
        if (ObjGetNthAttachPointPosSafe_23b0c0(e, 0, 0, v160) == 0) {
            FrameGetWorldPos_148f30(ModelGetRootFrame_1511a0(e), v160);
        }
        if (!(VecDistSq_1cb3c0(cam, v160) <= f22)) {
            continue;
        }
        Character2LightBlendGetMatrices_1aeb90(e, v120, vE0);
        FrameGetWorldPos_148f30(ModelGetRootFrame_1511a0(e), &V320.x);
        f23 = -ModelObjGetScaledHeight_23b110(e);
        if (s7 && ((i >= 0x80 && i < 0x9C) || (i >= 0xC0 && i < 0xE0))) {
            f25 = ParamTableGetAlpha_1cfb40(g, i);
            if (f25 <= 0.0f) {
                continue;
            }
            if (ObjGetNthAttachPointPosSafe_23b0c0(e, 0, 0, vD0) != 0) {
                V320.x = vD0[0];
                V320.z = vD0[2];
            }
            V330.y = 1.0f;
            V330.x = 0.0f;
            V330.z = 0.0f;
            V330.w = 0.0f;
            f25 = f25 * ModelObjGetScaledRadius_23b140(e) / f24;
            c = ActorFindById_3eb870(d, i);
            if (c != 0 && (v = ActorCastToUnit_3b8770(c, 0, 0, 0)) != 0 && (w = v->f211()) != 0) {
                f25 = f25 * ((f32)*(s16 *)(w + 6) / 1024.0f);
            }
            e = D_00481A74;
            ModelSetPos_151110(e, &V320.x);
            {
                u8 *p_ = (u8 *)vC0;
                u32 n_ = 0x10;
                if (p_) {
                    while (n_) {
                        *p_ = 0;
                        n_--;
                        p_++;
                    }
                }
            }
            vC0[1] = 1.0f;
            vC0[0] = f25;
            vC0[2] = f25;
            ModelSetScale_150ff0(e, vC0);
        } else {
            if (i >= 12 && i < 60) {
                f23 = f23 - f21;
            }
            f25 = v120[1];
            f0 = VecLengthSqXZ_1cb450(v120, 0);
            if (!(16.0f * f0 <= 9.0f * (f25 * f25))) {
                v120[1] = 0.0f;
                VecScaleToLength_1cb510(v120, v120, 0.75f * f25);
                v120[1] = f25;
                VecNormalize_1cbb80(v120, v120);
            }
            if (VecLengthSq_1cb470(v120, 0) <= 0.0f) {
                V330.x = 0.0f;
                V330.y = 1.0f;
                V330.z = 0.0f;
                V330.w = 0.0f;
            } else {
                VecCopy_1cbe30(&V330, v120);
            }
        }
        if (s0 != 0 && (*(s32 *)(s0 + 0x3D8) & 4)) {
            f0 = CharaGetHeightAboveGround_238380(s0);
            if (!(f0 <= 0.0f)) {
                f23 = f23 - f0;
            }
        }
        f23 = (f23 < f20) ? f23 : f20;
        V320.y = V320.y + f23;
        PlaneShadowDescSetPlane_156a20(s, &V330, &V320, &V310);
        DrawListAddPlaneShadowMtxPkt_147ae0(mgr, s);
        e->f16();
    }
    DrawListEndPlaneShadowPass_146cc0(mgr);
}
