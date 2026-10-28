/* rgp:protos */
#line 1
#include "types.h"

class A21C1F0 {
    u8 pad[0x1B0];
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f15(f32 a0) { VCM(void, (void *, f32), 0x44, a0); }
};

class B21C1F0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v60() { VCM0(void, 0xF8); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f198() { VCM0(void, 0x320); }
};

extern "C" {
extern void strcpy(char *, const char *);
extern f32 RandFloat_13c010(void);
extern void MotionListResetAll_171e00(void *);
extern void ModelObjPlayMotionByName_1867a0(A21C1F0 *, char *, s32);
extern void ModelObjSetMotionPhase_1add80(A21C1F0 *, f32);
extern void ModelMotionEventReleaseHandlers_1b02b0(A21C1F0 *, int);
extern s32 SoundNextPlayHandle_1b81c0(void);
extern void SoundPlayScaledVolume_1b9520(s32, s32, s32, f32);
extern void ObjRecClearFlags_1c3dc0(s32, s32, s32, s32);
extern void ObjRecSetFlags_1c3e00(s32, s32, s32, s32);
extern void ParamTableFadeToOne_1cf9e0(s32, s32, s32);
extern void ParamTableSetAlpha_1cfb10(s32, s32, f32);
extern s32 ParamTableIsFadeIdle_1cfb70(s32, s32);
extern s32 GameSceneSoundSlot5GetHandle_1d0790(s32);
extern s32 GetCurrentScene_1f5be0(void);
extern s32 ModelHasMotion_20a5b0(A21C1F0 *, char *);
extern void CharaClearFlags_2124a0(u8 *);
extern s32 CharaPlayedMotionIsCurrent_2124c0(u8 *);
extern void CharaPlayMotion_212590(u8 *, A21C1F0 *, char *, s32, f32);
extern void CharaSetInvincibleTime_2138a0(u8 *, f32);
extern s32 CharaGetId_214a80(u8 *);
extern s32 CharaAppearSelectState_21c8a0(u8 *);
extern void CharaActLoco_21cc10(u8 *, void **);
extern void CharaResetToBaseMode_21e830(u8 *);
extern u64 ActCfgTableEvalNormalPrmtFlags_221600(s32, s32, s32, f32);
extern u64 ActCfgTableEvalNormalPendingPrmtFlags_2217a0(s32, s32, s32, f32);
extern u8 *CharaGetGroundTri_238410(u8 *, s32);
extern s32 CharaGetCurMotionName_238560(u8 *);
extern f32 CharaGetMotionFrame_238570(u8 *);
extern f32 CharaGetCollRadius_2386a0(u8 *);
extern s32 GetEffectMgr_2d9040(void);
extern void EffectSetId_2e0100(s32, void *, s32);
extern void EffectSetRotXyz_2e0910(s32, void *, f32, f32, f32);
extern void EffectSetPos_2e0bb0(s32, void *, void *);
extern void EffectSetScaleXyz_2e0c90(s32, void *, f32, f32, f32);
extern void EffectCreateByName_2e1020(void *, s32, char *, s32);
extern B21C1F0 * ActorCastToUnit_3b8770(void *, int, int, int);
extern f32 D_0045B080[];
extern char D_0045CF08[];
extern char D_0045CF10[];
extern char D_0045CF18[];
extern char D_0045CF20[];
extern char D_0045CF28[];
extern f32 D_0047DB00;
}

static inline void Notify(void **p, int rgp_a1, int rgp_a2, int rgp_a3) {
    B21C1F0 *v;
    if (*p != 0) {
        v = ActorCastToUnit_3b8770(*p, (int)rgp_a1, (int)rgp_a2, (int)rgp_a3);
        if (v != 0) {
            v->f198();
        }
    }
}

extern "C" void CharaActAppear_21c1f0(u8 *o, void **p) {
    char buf[0x20] __attribute__((aligned(16)));
    u8 v60[0x20] __attribute__((aligned(16)));
    s32 k;
    u64 keep;
    s32 r;
    s32 g;
    s32 s;
    f32 t;
    B21C1F0 *v;

    *(s32 *)(o + 0x42C) = 0;
    k = CharaGetCurMotionName_238560(o);
    keep = ActCfgTableEvalNormalPendingPrmtFlags_2217a0(*(s32 *)(o + 0x428), *(s16 *)(o + 0xA32), k, CharaGetMotionFrame_238570(o));
    k = CharaGetCurMotionName_238560(o);
    *(u64 *)(o + 0x570) = *(u64 *)(o + 0x568) & ActCfgTableEvalNormalPrmtFlags_221600(*(s32 *)(o + 0x428), *(s16 *)(o + 0xA32), k, CharaGetMotionFrame_238570(o));
    r = ((short)CharaAppearSelectState_21c8a0(o));
    if (*(u64 *)(o + 0x3D0) & 0x0008000000000000ULL) {
        *(u64 *)(o + 0x3D0) |= 0x0000400000000000ULL;
        *(s32 *)(o + 0x84) = 0;
    }
    g = GetCurrentScene_1f5be0();
    *(u64 *)(o + 0x3D0) &= ~0x0010000000000000ULL;
    switch (r) {
    case 0x14:
        CharaSetInvincibleTime_2138a0(o, 1.0f);
        ObjRecSetFlags_1c3e00(g, 1, ((short)CharaGetId_214a80(o)), 0xA0030);
        MotionListResetAll_171e00(*(u8 **)(o + 0x3F4) + 0x1F0);
        ModelObjPlayMotionByName_1867a0(*(A21C1F0 **)(o + 0x3F4), D_0045CF08, 6);
        (*(A21C1F0 **)(o + 0x3F4))->f15(1.0f);
        ModelObjSetMotionPhase_1add80(*(A21C1F0 **)(o + 0x3F4), 1.0f);
        ModelMotionEventReleaseHandlers_1b02b0(*(A21C1F0 **)(o + 0x3F4), 0);
        *(s16 *)(o + 0xA34) = 0x15;
        *(s32 *)(o + 0xAD0) = 0;
        *(s32 *)(o + 0xAD4) = 0;
        CharaClearFlags_2124a0(o);
    case 0x15:
        if (!(*(f32 *)(o + 0xAD0) < (f32)*(s16 *)(o + 0xB4A))) {
            ObjRecClearFlags_1c3dc0(g, 1, ((short)CharaGetId_214a80(o)), 0xA0030);
            s = GameSceneSoundSlot5GetHandle_1d0790(g);
            SoundPlayScaledVolume_1b9520(s, 0x47, SoundNextPlayHandle_1b81c0(), 1.0f);
            s = GetEffectMgr_2d9040();
            {
                u8 *p_ = (u8 *)buf;
                u32 n_ = 0x20;
                if (p_) {
                    while (n_) {
                        *p_ = 0;
                        n_--;
                        p_++;
                    }
                }
            }
            switch (*(s16 *)(CharaGetGroundTri_238410(o, 0) + 0x42)) {
            case 0xE:
            case 0x11:
                strcpy(buf, D_0045CF10);
                break;
            case 2:
            case 0x10:
            case 1:
                strcpy(buf, D_0045CF18);
                break;
            }
            EffectCreateByName_2e1020(v60, s, buf, -1);
            EffectSetId_2e0100(s, v60, ((short)CharaGetId_214a80(o)));
            EffectSetPos_2e0bb0(s, v60, o + 0x70);
            EffectSetRotXyz_2e0910(s, v60, 0.0f, D_0047DB00 * (RandFloat_13c010() - 0.5f), 0.0f);
            t = CharaGetCollRadius_2386a0(o) / (2.0f * D_0045B080[0]);
            if (t < 0.25f) {
                t = 0.25f;
            }
            EffectSetScaleXyz_2e0c90(s, v60, t, t, t);
            if (ModelHasMotion_20a5b0(*(A21C1F0 **)(o + 0x3F4), D_0045CF20) == 0) {
                v = ActorCastToUnit_3b8770(*p, 0, 0, 0);
                if (v != 0) {
                    v->f198();
                }
                CharaResetToBaseMode_21e830(o);
                CharaActLoco_21cc10(o, p);
                return;
            }
            CharaPlayMotion_212590(o, *(A21C1F0 **)(o + 0x3F4), D_0045CF20, 6, 1.0f);
            *(s16 *)(o + 0xA34) = 0x16;
            *(s32 *)(o + 0xAD0) = 0;
            *(s32 *)(o + 0xAD4) = 0;
            *(u64 *)(o + 0x3D0) |= 0x0010000000000000ULL;
        }
        CharaSetInvincibleTime_2138a0(o, 15.0f);
        break;
    case 0x16:
        if (((unsigned char)CharaPlayedMotionIsCurrent_2124c0(o)) == 0 || (((unsigned char)CharaPlayedMotionIsCurrent_2124c0(o)) != 0 && !(CharaGetMotionFrame_238570(o) < 1.0f))) {
            Notify(p, 0, 0, 0);
            CharaResetToBaseMode_21e830(o);
            CharaActLoco_21cc10(o, p);
            return;
        }
        break;
    case 0xA:
        if (*(s16 *)(o + 0xA34) != r) {
            ObjRecSetFlags_1c3e00(g, 1, ((short)CharaGetId_214a80(o)), 0xA0000);
            ParamTableSetAlpha_1cfb10(g, ((short)CharaGetId_214a80(o)), 0.0f);
            ParamTableFadeToOne_1cf9e0(g, ((short)CharaGetId_214a80(o)), *(s16 *)(o + 0xB4A));
            CharaPlayMotion_212590(o, *(A21C1F0 **)(o + 0x3F4), D_0045CF28, 6, 1.0f);
            *(s16 *)(o + 0xA34) = 0xA;
            *(s32 *)(o + 0xAD0) = 0;
            *(s32 *)(o + 0xAD4) = 0;
            CharaClearFlags_2124a0(o);
        }
        if (ParamTableIsFadeIdle_1cfb70(g, ((short)CharaGetId_214a80(o))) != 0) {
            Notify(p, 0, 0, 0);
            ObjRecClearFlags_1c3dc0(g, 1, ((short)CharaGetId_214a80(o)), 0xA0000);
            CharaResetToBaseMode_21e830(o);
            CharaActLoco_21cc10(o, p);
            return;
        }
        break;
    default:
        Notify(p, 0, 0, 0);
        CharaResetToBaseMode_21e830(o);
        CharaActLoco_21cc10(o, p);
        return;
    }
    *(u64 *)(o + 0x3D0) |= 0x0400000000000000ULL;
    Notify(p, 0, 0, 0);
    *(u64 *)(o + 0x568) &= keep;
}
