/* rgp:protos */
#line 1
#include "types.h"

class Chr {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 Busy() { return VCM0(s32, 0x2A8); }
};

typedef struct { Chr *c; f32 dt; } Arg;

extern "C" {
extern s32 Sprintf_1343b8(char *, const char *, ...);
extern char *strcpy(char *, const char *);
extern void ModelMotionEventReleaseHandlers_1b02b0(s32, int);
extern void ObjRecClearFlags_1c3dc0(s32, s32, s32, s32);
extern void ObjRecSetFlags_1c3e00(s32, s32, s32, s32);
extern void ParamTableFadeToZero_1cf9d0(s32, s32, s32);
extern f32 ParamTableGetAlpha_1cfb40(s32, s32);
extern s32 ParamTableIsFadeIdle_1cfb70(s32, s32);
extern void GameSceneSoundSlot5PlaySe_1d05a0(s32, s32);
extern s32 GetCurrentScene_1f5be0(void);
extern s32 ModelHasMotion_20a5b0(s32, char *);
extern void CharaClearFlags_2124a0(u8 *);
extern s32 CharaPlayedMotionIsCurrent_2124c0(u8 *);
extern void CharaPlayMotion_212590(u8 *, s32, char *, s32, f32);
extern void CharaInvokeInitBt1_212ad0(u8 *);
extern void CharaSetInvincibleTime_2138a0(u8 *, f32);
extern void CharaSetHoverParams_2138e0(u8 *, f32, f32);
extern void CharaSetMoveDirMaybe_213b00(u8 *, void *);
extern s32 CharaGetId_214a80(u8 *);
extern s32 CharaSelectDeathState_217ca0(u8 *);
extern void CharaActLoco_21cc10(u8 *, Arg *);
extern void CharaResetToBaseMode_21e830(u8 *);
extern u64 ActCfgTableEvalNormalPrmtFlags_221600(s32, s32, s32, f32);
extern u64 ActCfgTableEvalNormalPendingPrmtFlags_2217a0(s32, s32, s32, f32);
extern f32 CharaGetHeightAboveGround_238380(u8 *);
extern s32 CharaGetCurMotionName_238560(u8 *);
extern f32 CharaGetMotionFrame_238570(u8 *);
extern float CharaGetForwardVec_238830(u8 *, void *);
extern void EffectPlayResurrection_2d8040(s32);
extern void DeathEffectSpawn_2d8270(s32);
extern char D_0045CBD0[];
extern char D_0045CBD8[];
extern char D_0045CBE0[];
extern char D_0045CBE8[];
extern char D_0045CBF0[];
extern char D_0045CBF8[];
extern char D_0045CC00[];
extern char D_0045CC08[];
extern char D_0045CC10[];
extern char D_0045CC18[];
extern char D_0045CC20[];
extern char D_0045CC28[];
extern char D_0045CC30[];
}

static inline void MakeName(u8 *o, char *buf, char *s2, char *s3, char *suf) {
    if (*(s16 *)(o + 0xA2E) == 2) {
        if (*(s16 *)(o + 0xA2C) <= 0) {
            strcpy(buf, s2);
        } else {
            Sprintf_1343b8(buf, D_0045CBD8, *(s16 *)(o + 0xA2C) + 0x60, suf);
        }
    } else if (*(s16 *)(o + 0xA2E) == 3) {
        if (*(s16 *)(o + 0xA2C) <= 0) {
            strcpy(buf, s3);
        } else {
            Sprintf_1343b8(buf, D_0045CBF0, *(s16 *)(o + 0xA2C) + 0x60, suf);
        }
    } else {
        if (*(s16 *)(o + 0xA2C) <= 0) {
            strcpy(buf, suf);
        } else {
            Sprintf_1343b8(buf, D_0045CBF8, *(s16 *)(o + 0xA2C) + 0x60, suf);
        }
        strcpy(buf, suf);
    }
}

extern "C" void CharaActDeath_216f60(u8 *o, Arg *p) {
    char bF0[0x20] __attribute__((aligned(16)));
    u8 vE0[0x10] __attribute__((aligned(16)));
    char bC0[0x20] __attribute__((aligned(16)));
    u8 vB0[0x10] __attribute__((aligned(16)));
    char b90[0x20] __attribute__((aligned(16)));
    u8 v80[0x10] __attribute__((aligned(16)));
    char b60[0x20] __attribute__((aligned(16)));
    u8 v50[0x10] __attribute__((aligned(16)));
    s32 k;
    u64 keep;
    u64 mask;
    s32 r;
    s32 w;

    *(s32 *)(o + 0x42C) = 0;
    k = CharaGetCurMotionName_238560(o);
    keep = ActCfgTableEvalNormalPendingPrmtFlags_2217a0(*(s32 *)(o + 0x428), *(s16 *)(o + 0xA32), k, CharaGetMotionFrame_238570(o));
    k = CharaGetCurMotionName_238560(o);
    mask = ActCfgTableEvalNormalPrmtFlags_221600(*(s32 *)(o + 0x428), *(s16 *)(o + 0xA32), k, CharaGetMotionFrame_238570(o)) | 0x0000100000000000ULL;
    *(u64 *)(o + 0x570) = *(u64 *)(o + 0x568) & mask;
    r = ((short)CharaSelectDeathState_217ca0(o));
    *(u64 *)(o + 0x3D0) |= 0x0000080000000000ULL;
    *(u64 *)(o + 0x3D0) |= 0x0000001000000000ULL;
    *(s32 *)(o + 0xA44) |= 0x800000;
    CharaSetInvincibleTime_2138a0(o, 1.0f);
    switch (r) {
    case 0:
        if (*(s16 *)(o + 0xA34) != r) {
            MakeName(o, bF0, D_0045CBD0, D_0045CBE8, D_0045CBE0);
            CharaPlayMotion_212590(o, *(s32 *)(o + 0x3F4), bF0, 6, 1.0f);
            *(s16 *)(o + 0xA34) = r;
            *(s32 *)(o + 0xAD0) = 0;
            *(s32 *)(o + 0xAD4) = 0;
            CharaClearFlags_2124a0(o);
            *(s16 *)(o + 0xA36) = 0x1B;
            CharaGetForwardVec_238830(o, vE0);
            CharaSetMoveDirMaybe_213b00(o, vE0);
            ObjRecSetFlags_1c3e00(GetCurrentScene_1f5be0(), 1, ((short)CharaGetId_214a80(o)), 0xA0000);
        } else if (((unsigned char)CharaPlayedMotionIsCurrent_2124c0(o)) == 0 || (((unsigned char)CharaPlayedMotionIsCurrent_2124c0(o)) != 0 && !(CharaGetMotionFrame_238570(o) < 1.0f))) {
            MakeName(o, bC0, D_0045CC00, D_0045CC10, D_0045CC08);
            CharaPlayMotion_212590(o, *(s32 *)(o + 0x3F4), bC0, 4, 1.0f);
            *(s16 *)(o + 0xA34) = r;
            *(s32 *)(o + 0xAD0) = 0;
            *(s32 *)(o + 0xAD4) = 0;
            CharaClearFlags_2124a0(o);
            *(s16 *)(o + 0xA34) = ((*(u64 *)(o + 0x3D0) & 0x0200000000000000ULL) || (*(s32 *)(o + 0xA44) & 0x400000)) ? 0xA : 4;
            *(s32 *)(o + 0xAD0) = 0;
            *(s32 *)(o + 0xAD4) = 0;
        }
        break;
    case 1:
        if (*(s16 *)(o + 0xA34) != r) {
            CharaSetHoverParams_2138e0(o, 0.0f, CharaGetHeightAboveGround_238380(o));
            CharaPlayMotion_212590(o, *(s32 *)(o + 0x3F4), D_0045CC18, 2, 1.0f);
            *(s16 *)(o + 0xA34) = r;
            *(s32 *)(o + 0xAD0) = 0;
            *(s32 *)(o + 0xAD4) = 0;
            CharaClearFlags_2124a0(o);
            *(s16 *)(o + 0xA36) = 0x1B;
            CharaGetForwardVec_238830(o, vB0);
            CharaSetMoveDirMaybe_213b00(o, vB0);
        } else if (((unsigned char)CharaPlayedMotionIsCurrent_2124c0(o)) == 0 || (((unsigned char)CharaPlayedMotionIsCurrent_2124c0(o)) != 0 && !(CharaGetMotionFrame_238570(o) < 1.0f))) {
            CharaPlayMotion_212590(o, *(s32 *)(o + 0x3F4), D_0045CC08, 0, 1.0f);
            *(s16 *)(o + 0xA34) = 2;
            *(s32 *)(o + 0xAD0) = 0;
            *(s32 *)(o + 0xAD4) = 0;
        }
        keep |= 0x0000100000000000ULL;
        break;
    case 2:
        if (*(s16 *)(o + 0xA34) != r) {
            MakeName(o, b90, D_0045CC00, D_0045CC10, D_0045CC08);
            if (ModelHasMotion_20a5b0(*(s32 *)(o + 0x3F4), b90) != 0) {
                CharaPlayMotion_212590(o, *(s32 *)(o + 0x3F4), b90, 0, 1.0f);
            }
            *(s16 *)(o + 0xA34) = r;
            *(s32 *)(o + 0xAD0) = 0;
            *(s32 *)(o + 0xAD4) = 0;
            CharaClearFlags_2124a0(o);
        }
        break;
    case 3:
        if (*(s16 *)(o + 0xA34) != r) {
            CharaPlayMotion_212590(o, *(s32 *)(o + 0x3F4), D_0045CC20, 6, 1.0f);
            *(s16 *)(o + 0xA34) = r;
            *(s32 *)(o + 0xAD0) = 0;
            *(s32 *)(o + 0xAD4) = 0;
            CharaClearFlags_2124a0(o);
            ObjRecClearFlags_1c3dc0(GetCurrentScene_1f5be0(), 1, ((short)CharaGetId_214a80(o)), 0xA0038);
            CharaGetForwardVec_238830(o, v80);
            CharaSetMoveDirMaybe_213b00(o, v80);
        } else if (((unsigned char)CharaPlayedMotionIsCurrent_2124c0(o)) == 0 || (((unsigned char)CharaPlayedMotionIsCurrent_2124c0(o)) != 0 && !(CharaGetMotionFrame_238570(o) < 1.0f))) {
            ModelMotionEventReleaseHandlers_1b02b0(*(s32 *)(o + 0x3F4), 0);
            *(s16 *)(o + 0xA34) = ((*(u64 *)(o + 0x3D0) & 0x0200000000000000ULL) || (*(s32 *)(o + 0xA44) & 0x400000)) ? 0xA : 4;
            *(s32 *)(o + 0xAD0) = 0;
            *(s32 *)(o + 0xAD4) = 0;
        }
        break;
    case 4:
        w = GetCurrentScene_1f5be0();
        if (*(f32 *)(o + 0xAD4) == 0.0f) {
            if (p->c != 0) {
                if (p->c->Busy() == 0) {
                    DeathEffectSpawn_2d8270(((short)CharaGetId_214a80(o)));
                }
            }
            ParamTableFadeToZero_1cf9d0(w, ((short)CharaGetId_214a80(o)), 0xA);
            *(f32 *)(o + 0xAD4) += p->dt;
        }
        if (ParamTableIsFadeIdle_1cfb70(w, ((short)CharaGetId_214a80(o))) != 0 && ParamTableGetAlpha_1cfb40(w, ((short)CharaGetId_214a80(o))) == 0.0f) {
            *(s16 *)(o + 0xA34) = 0xA;
            ObjRecSetFlags_1c3e00(w, 1, ((short)CharaGetId_214a80(o)), 0x18);
            ModelMotionEventReleaseHandlers_1b02b0(*(s32 *)(o + 0x3F4), 0);
        }
        if (ParamTableGetAlpha_1cfb40(w, ((short)CharaGetId_214a80(o))) <= 0.5f) {
            ObjRecSetFlags_1c3e00(w, 1, ((short)CharaGetId_214a80(o)), 0x20);
        }
        break;
    case 0xA:
        GetCurrentScene_1f5be0();
        *(s16 *)(o + 0xA2E) = 0;
        break;
    case 0x14:
        if (*(s16 *)(o + 0xA34) != r) {
            if (*(s16 *)(o + 0xA2C) <= 0) {
                strcpy(b60, D_0045CC28);
            } else {
                Sprintf_1343b8(b60, D_0045CBD8, *(s16 *)(o + 0xA2C) + 0x60, D_0045CC30);
            }
            CharaPlayMotion_212590(o, *(s32 *)(o + 0x3F4), b60, 6, 1.0f);
            *(s16 *)(o + 0xA34) = r;
            *(s32 *)(o + 0xAD0) = 0;
            *(s32 *)(o + 0xAD4) = 0;
            CharaClearFlags_2124a0(o);
            GameSceneSoundSlot5PlaySe_1d05a0(GetCurrentScene_1f5be0(), 0x4B);
            *(s16 *)(o + 0xA36) = 0x1C;
            CharaInvokeInitBt1_212ad0(o);
            CharaGetForwardVec_238830(o, v50);
            CharaSetMoveDirMaybe_213b00(o, v50);
            EffectPlayResurrection_2d8040(((short)CharaGetId_214a80(o)));
        } else if (((unsigned char)CharaPlayedMotionIsCurrent_2124c0(o)) == 0 || (((unsigned char)CharaPlayedMotionIsCurrent_2124c0(o)) != 0 && !(CharaGetMotionFrame_238570(o) < 1.0f))) {
            CharaSetInvincibleTime_2138a0(o, 45.0f);
            *(s32 *)(o + 0xA44) &= ~0x800000;
            *(f32 *)(*(u8 **)(o + 0x3F4) + 0x448) = 1.0f;
            CharaResetToBaseMode_21e830(o);
            CharaActLoco_21cc10(o, p);
            return;
        }
        break;
    default:
        CharaResetToBaseMode_21e830(o);
        CharaActLoco_21cc10(o, p);
        return;
    }
    *(u64 *)(o + 0x3D0) |= 0x0400000000000000ULL;
    *(u64 *)(o + 0x568) &= keep;
}
