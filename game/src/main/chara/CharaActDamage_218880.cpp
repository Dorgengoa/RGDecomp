/* rgp:protos */
#line 1
#include "types.h"

class V218880 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v80() { VCM0(void, 0x148); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f129(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0x20C, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};


extern "C" {
extern s32 Rand_133710(void);
extern s32 Sprintf_1343b8(char *, const char *, ...);
extern char *strcpy(char *, const char *);
extern void SoundPlayScaledVolume_1b9520(s32, s32, s32, f32);
extern f32 AngleWrap_1cbf30(f32);
extern void ParamTableSetAlpha_1cfb10(s32, s32, f32);
extern s32 GetCurrentScene_1f5be0(void);
extern s32 ModelHasMotion_20a5b0(s32, char *);
extern s32 CharaWeaponStateValidateMaybe_20a600(s32);
extern void CharaRequestAction_212410(u8 *, char *, f32);
extern void CharaClearFlags_2124a0(u8 *);
extern s32 CharaPlayedMotionIsCurrent_2124c0(u8 *);
extern void CharaPlayMotion_212590(u8 *, s32, char *, s32, f32);
extern s32 CharaGetBaseActionMode_213830(u8 *);
extern void CharaSetMoveDirMaybe_213b00(u8 *, void *);
extern s32 CharaGetId_214a80(u8 *);
extern s32 CharaActDamageNextStateMaybe_218fc0(u8 *);
extern void CharaActLoco_21cc10(u8 *, void **);
extern void CharaResetToBaseMode_21e830(u8 *);
extern s32 CharaInputInterruptMaybe_21e8f0(u8 *, void **);
extern u64 ActCfgTableEvalNormalPrmtFlags_221600(s32, s32, s32, f32);
extern u64 ActCfgTableEvalNormalPendingPrmtFlags_2217a0(s32, s32, s32, f32);
extern s32 ActCfgTableFindMoveById_223080(s32, s32);
extern s32 CharaGetCurMotionName_238560(u8 *);
extern f32 CharaGetMotionFrame_238570(u8 *);
extern void CharaSetVelocity_238770(u8 *, f32, f32, f32);
extern float CharaGetForwardVec_238830(u8 *, void *);
extern char D_0045CBD8[];
extern char D_0045CBF0[];
extern char D_0045CBF8[];
extern char D_0045CCF0[];
extern char D_0045CD00[];
extern char D_0045CD10[];
extern char D_0045CD18[];
extern char D_0045CD20[];
extern char D_0045CD28[];
extern char D_0045CD38[];
extern char D_0045CD48[];
extern f32 D_0047D1FC;
}


typedef struct {
    __extension__ unsigned long long pad0 : 46;
    unsigned long long b46 : 1;
    unsigned long long pad47 : 17;
} __attribute__((aligned(8))) BF218880;

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

extern "C" void CharaActDamage_218880(u8 *o, void **p, int rgp_a2, int rgp_a3) {
    char bB0[0x20] __attribute__((aligned(16)));
    char b90[0x20] __attribute__((aligned(16)));
    u8 v80[0x10] __attribute__((aligned(16)));
    char b60[0x20] __attribute__((aligned(16)));
    s32 k;
    u64 keep;
    u64 mask;
    s32 r;
    s32 t;

    *(s32 *)(o + 0x42C) = 0;
    if (((V218880 *)*p)->f129((int)(long)(p), (int)(long)(rgp_a2), (int)(long)(rgp_a3)) == 5) {
        CharaResetToBaseMode_21e830(o);
        CharaActLoco_21cc10(o, p);
        return;
    }
    k = CharaGetCurMotionName_238560(o);
    keep = ActCfgTableEvalNormalPendingPrmtFlags_2217a0(*(s32 *)(o + 0x428), *(s16 *)(o + 0xA32), k, CharaGetMotionFrame_238570(o));
    k = CharaGetCurMotionName_238560(o);
    mask = ActCfgTableEvalNormalPrmtFlags_221600(*(s32 *)(o + 0x428), *(s16 *)(o + 0xA32), k, CharaGetMotionFrame_238570(o)) | 0x0017C7FC00000000ULL;
    if (!(*(s32 *)(o + 0xA44) & 0x1000000)) {
        if (*(f32 *)(o + 0xACC) > 5.0f && (*(u64 *)(o + 0x568) & 0x100000000ULL)) {
            switch (((short)CharaGetBaseActionMode_213830(o))) {
            case 2:
                CharaRequestAction_212410(o, D_0045CCF0, 0.25f);
                break;
            case 3:
                CharaRequestAction_212410(o, D_0045CD00, 0.25f);
                break;
            }
        }
    }
    *(u64 *)(o + 0x570) = *(u64 *)(o + 0x568) & mask;
    r = CharaActDamageNextStateMaybe_218fc0(o);
    if (*(s32 *)(o + 0x3D8) & 1) {
        *(u64 *)(o + 0x3D0) &= ~0x0000400000000000ULL;
    }
    *(s32 *)(o + 0x42C) = ActCfgTableFindMoveById_223080(*(s32 *)(o + 0x428), CharaWeaponStateValidateMaybe_20a600(*(s16 *)(o + 0xA2E)));
    switch (r) {
    case 1:
        if (*(s16 *)(o + 0xA34) != r) {
            MakeName(o, bB0, D_0045CD10, D_0045CD20, D_0045CD18);
            MakeName(o, b90, D_0045CD28, D_0045CD48, D_0045CD38);
            if (ModelHasMotion_20a5b0(*(s32 *)(o + 0x3F4), b90) != 0) {
                CharaPlayMotion_212590(o, *(s32 *)(o + 0x3F4), bB0, 4, 1.0f);
            } else {
                CharaPlayMotion_212590(o, *(s32 *)(o + 0x3F4), bB0, 6, 1.0f);
            }
            *(s16 *)(o + 0xA34) = r;
            *(s32 *)(o + 0xAD0) = 0;
            *(s32 *)(o + 0xAD4) = 0;
            CharaClearFlags_2124a0(o);
            ParamTableSetAlpha_1cfb10(GetCurrentScene_1f5be0(), ((short)CharaGetId_214a80(o)), 1.0f);
            if (!(*(u64 *)(o + 0x3D0) & 0x200000000ULL)) {
                CharaSetVelocity_238770(o, 0.0f, 0.0f, 0.0f);
            }
            if (!(*(u64 *)(o + 0x3D0) & 0x100000000ULL)) {
                *(f32 *)(o + 0x64) = AngleWrap_1cbf30(*(f32 *)(o + 0x890) - D_0047D1FC);
                *(s32 *)(o + 0x94) = 0;
                CharaGetForwardVec_238830(o, v80);
                CharaSetMoveDirMaybe_213b00(o, v80);
            }
            if (((short)CharaGetId_214a80(o)) >= 0 && ((short)CharaGetId_214a80(o)) < 12) {
                t = *(s32 *)(*(u8 **)(o + 0x3F4) + 0x4FC);
                SoundPlayScaledVolume_1b9520(t, Rand_133710() % 3 + 9, 0, 1.0f);
            }
        }
        break;
    case 2:
        if (*(s16 *)(o + 0xA34) != r) {
            MakeName(o, b60, D_0045CD28, D_0045CD48, D_0045CD38);
            if (ModelHasMotion_20a5b0(*(s32 *)(o + 0x3F4), b60) == 0) {
                CharaResetToBaseMode_21e830(o);
                CharaActLoco_21cc10(o, p);
                return;
            }
            CharaPlayMotion_212590(o, *(s32 *)(o + 0x3F4), b60, 6, 1.0f);
            *(s16 *)(o + 0xA34) = r;
            *(s32 *)(o + 0xAD0) = 0;
            *(s32 *)(o + 0xAD4) = 0;
        } else {
            if (CharaInputInterruptMaybe_21e8f0(o, p) != 0) {
                return;
            }
            if (((unsigned char)CharaPlayedMotionIsCurrent_2124c0(o)) == 0 || (((unsigned char)CharaPlayedMotionIsCurrent_2124c0(o)) != 0 && !(CharaGetMotionFrame_238570(o) < 1.0f))) {
                CharaResetToBaseMode_21e830(o);
                CharaActLoco_21cc10(o, p);
                return;
            }
        }
        break;
    default:
        CharaResetToBaseMode_21e830(o);
        CharaActLoco_21cc10(o, p);
        return;
    }
    *(u64 *)(o + 0x3D0) |= 4;
    *(u64 *)(o + 0x3D0) |= 0x0400000000000000ULL;
    *(u64 *)(o + 0x568) &= keep;
}
