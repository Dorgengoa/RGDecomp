#include "types.h"

typedef struct { f32 x, y, z, w; } V4;
typedef struct { f32 f[4]; } FA4;
typedef struct { char c[0x20]; } N32;
typedef struct { void *c; f32 dt; } Arg;

#define ZERO(d, n) { u8 *p_ = (u8 *)(d); u32 n_ = (n); if (p_) while (n_) { *p_ = 0; n_--; p_++; } }
static inline void Zero(void *d, u32 n) {
    u8 *p_ = (u8 *)d;
    if (p_) while (n) { *p_ = 0; n--; p_++; }
}
#define F(o, x) (*(f32 *)((o) + (x)))
#define I(o, x) (*(s32 *)((o) + (x)))
#define H(o, x) (*(s16 *)((o) + (x)))

extern "C" {
extern char *strcpy(char *, const char *);
extern f32 Cosf_128d30(f32);
extern f32 Sinf_128fd0(f32);
extern void ModelSetPos_151110(s32, void *);
extern void VecDivScalar_1cbbf0(void *, void *, f32);
extern void VecScale_1cbca0(V4 *, V4 *, f32);
extern void VecSub_1cbd00(void *, V4 *, void *);
extern f32 AngleWrap_1cbf30(f32);
extern void CharaClearFlags_2124a0(u8 *);
extern s32 CharaPlayedMotionIsCurrent_2124c0(u8 *);
extern void CharaPlayMotion_212590(u8 *, s32, char *, s32, f32);
extern void CharaSetYaw_2138f0(u8 *, f32);
extern void CharaSetPosXYZ_2139e0(u8 *, f32, f32, f32);
extern s32 CharaSelectLadderState_21a500(u8 *);
extern void CharaLadderStateReset_21ae70(void *);
extern void CharaActMoveMotion_21b180(u8 *, Arg *);
extern void CharaSetActionModeMoveMotion_21bbb0(u8 *);
extern void CharaActLoco_21cc10(u8 *, Arg *);
extern void CharaResetToBaseMode_21e830(u8 *);
extern u64 ActCfgTableEvalNormalPrmtFlags_221600(s32, s32, s32, f32);
extern u64 ActCfgTableEvalNormalPendingPrmtFlags_2217a0(s32, s32, s32, f32);
extern s32 CharaIsCurMotion_238540(u8 *, char *);
extern s32 CharaGetCurMotionName_238560(u8 *);
extern f32 CharaGetMotionFrame_238570(u8 *);
extern void CharaSetSrtVec40_238760(u8 *, f32, f32, f32);
extern void CharaSetVelocity_238770(u8 *, f32, f32, f32);
extern void CharaGetForwardVec_238830(u8 *, V4 *);
extern s32 IsInBattle_288420(void);
extern char D_0044B790[];
extern char D_0044B7B0[];
extern char D_0045CD58[];
extern char D_0045CD60[];
extern char D_0045CD68[];
extern char D_0045CD78[];
extern char D_0045CD88[];
extern char D_0045CD98[];
extern char D_0045CDA8[];
extern char D_0045CDB8[];
extern char D_0045CDC8[];
extern char D_0045CDD8[];
extern f32 D_0045B080[];
extern f32 D_0047D278;
extern f32 D_0047DB50;
extern FA4 D_0047E650 __attribute__((section(".sdata")));
extern FA4 D_0047E660 __attribute__((section(".sdata")));
}

extern "C" void CharaActLadder_2198e0(u8 *o, Arg *p) {
    N32 nA;
    V4 vA;
    V4 dA;
    V4 vB;
    V4 tB;
    N32 nC;
    V4 vC;
    V4 dC;
    s32 k;
    u64 keep;
    u64 mask;
    s32 r;
    f32 K;

    I(o, 0x42C) = 0;
    k = CharaGetCurMotionName_238560(o);
    keep = ActCfgTableEvalNormalPendingPrmtFlags_2217a0(I(o, 0x428), H(o, 0xA32), k, CharaGetMotionFrame_238570(o));
    k = CharaGetCurMotionName_238560(o);
    mask = ActCfgTableEvalNormalPrmtFlags_221600(I(o, 0x428), H(o, 0xA32), k, CharaGetMotionFrame_238570(o)) | 0x4060;
    *(u64 *)(o + 0x570) = *(u64 *)(o + 0x568) & mask;
    if (IsInBattle_288420() != 0) {
        *(u64 *)(o + 0x570) |= 0x4000;
    }
    r = CharaSelectLadderState_21a500(o);
    switch (r) {
    case 0:
        if (r != H(o, 0xA34)) {
            nA = *(N32 *)D_0044B790;
            if (H(o, 0xA2E) == 2) {
                strcpy(nA.c, D_0045CD58);
            }
            if (H(o, 0xA2E) == 3) {
                strcpy(nA.c, D_0045CD60);
            }
            if (CharaIsCurMotion_238540(o, nA.c) == 0) {
                CharaPlayMotion_212590(o, I(o, 0x3F4), nA.c, 0, 0.25f);
            }
            H(o, 0xA34) = r;
            I(o, 0xAD0) = 0;
            I(o, 0xAD4) = 0;
            CharaClearFlags_2124a0(o);
            ZERO(&vA, 0x10);
            vA.x = Sinf_128fd0(F(o, 0x850));
            vA.z = Cosf_128d30(F(o, 0x850));
            VecScale_1cbca0(&vA, &vA, 0.5f * D_0045B080[0]);
            *(FA4 *)&dA = D_0047E650;
            dA.x = F(o, 0x830) - vA.x;
            dA.y = F(o, 0x834);
            dA.z = F(o, 0x838) - vA.z;
            VecSub_1cbd00(o + 0x80, &dA, o + 0x70);
            VecDivScalar_1cbbf0(o + 0x80, o + 0x80, 30.0f);
            F(o, 0x94) = AngleWrap_1cbf30(F(o, 0x850) - F(o, 0x64)) / 30.0f;
            I(o, 0x854) = 1;
        }
        break;
    case 0x28:
        if (r != H(o, 0xA34)) {
            CharaPlayMotion_212590(o, I(o, 0x3F4), D_0045CD68, 6, 1.0f);
            H(o, 0xA34) = r;
            I(o, 0xAD0) = 0;
            I(o, 0xAD4) = 0;
            CharaClearFlags_2124a0(o);
            ZERO(&vB, 0x10);
            vB.x = Sinf_128fd0(F(o, 0x850));
            vB.z = Cosf_128d30(F(o, 0x850));
            VecScale_1cbca0(&vB, &vB, 0.5f * D_0045B080[0]);
            CharaSetSrtVec40_238760(o, 0.0f, 0.0f, 0.0f);
            CharaSetVelocity_238770(o, 0.0f, 0.0f, 0.0f);
            CharaSetPosXYZ_2139e0(o, F(o, 0x830) - vB.x, F(o, 0x834), F(o, 0x838) - vB.z);
            CharaSetYaw_2138f0(o, F(o, 0x850));
            I(o, 0x854) = 1;
        }
        break;
    case 0x29:
        if (r != H(o, 0xA34)) {
            CharaPlayMotion_212590(o, I(o, 0x3F4), D_0045CD78, 6, 1.0f);
            H(o, 0xA34) = r;
            I(o, 0xAD0) = 0;
            I(o, 0xAD4) = 0;
            CharaClearFlags_2124a0(o);
            F(o, 0x74) = F(o, 0x834) + (f32)(I(o, 0x854) - 1) * (D_0047DB50 * *(volatile f32 *)D_0045B080);
            I(o, 0x854) = I(o, 0x854) + 1;
        }
        break;
    case 0x2A:
        if (r != H(o, 0xA34)) {
            CharaPlayMotion_212590(o, I(o, 0x3F4), D_0045CD88, 6, 1.0f);
            H(o, 0xA34) = r;
            I(o, 0xAD0) = 0;
            I(o, 0xAD4) = 0;
            CharaClearFlags_2124a0(o);
            F(o, 0x74) = F(o, 0x834) + (f32)(I(o, 0x854) - 1) * (D_0047DB50 * *(volatile f32 *)D_0045B080);
            I(o, 0x854) = I(o, 0x854) + 1;
        }
        break;
    case 0x2B:
        if (r != H(o, 0xA34)) {
            CharaPlayMotion_212590(o, I(o, 0x3F4), D_0045CD98, 2, 1.0f);
            H(o, 0xA34) = r;
            I(o, 0xAD0) = 0;
            I(o, 0xAD4) = 0;
            CharaClearFlags_2124a0(o);
            F(o, 0x74) = F(o, 0x834) + (f32)(I(o, 0x854) - 1) * (D_0047DB50 * *(volatile f32 *)D_0045B080);
            I(o, 0x854) = I(o, 0x858);
        } else if (CharaPlayedMotionIsCurrent_2124c0(o) != 0 && !(CharaGetMotionFrame_238570(o) < 1.0f)) {
            CharaGetForwardVec_238830(o, &tB);
            VecScale_1cbca0(&tB, &tB, D_0047D278 * *(volatile f32 *)D_0045B080);
            F(o, 0x70) = F(o, 0x70) + tB.x;
            F(o, 0x74) = F(o, 0x844);
            F(o, 0x78) = F(o, 0x78) + tB.z;
            ModelSetPos_151110(I(o, 0x3F4), o + 0x70);
            CharaLadderStateReset_21ae70(o + 0x830);
            *(u64 *)(o + 0x3D0) |= 0x0000400000000000ULL;
            CharaResetToBaseMode_21e830(o);
            CharaActLoco_21cc10(o, p);
            return;
        }
        break;
    case 1:
        if (r != H(o, 0xA34)) {
            nC = *(N32 *)D_0044B7B0;
            if (H(o, 0xA2E) == 2) {
                strcpy(nC.c, D_0045CD58);
            }
            if (H(o, 0xA2E) == 3) {
                strcpy(nC.c, D_0045CD60);
            }
            if (CharaIsCurMotion_238540(o, nC.c) == 0) {
                CharaPlayMotion_212590(o, I(o, 0x3F4), nC.c, 0, 0.25f);
            }
            H(o, 0xA34) = r;
            I(o, 0xAD0) = 0;
            I(o, 0xAD4) = 0;
            CharaClearFlags_2124a0(o);
            ZERO(&vC, 0x10);
            vC.x = Sinf_128fd0(F(o, 0x850));
            vC.z = Cosf_128d30(F(o, 0x850));
            K = D_0045B080[0];
            VecScale_1cbca0(&vC, &vC, 0.5f * K - D_0047D278 * K);
            *(FA4 *)&dC = D_0047E660;
            dC.x = F(o, 0x830) - vC.x;
            dC.y = F(o, 0x834) + (f32)I(o, 0x858) * (D_0047DB50 * K);
            dC.z = F(o, 0x838) - vC.z;
            VecSub_1cbd00(o + 0x80, &dC, o + 0x70);
            VecDivScalar_1cbbf0(o + 0x80, o + 0x80, 30.0f);
            F(o, 0x94) = AngleWrap_1cbf30(F(o, 0x850) - F(o, 0x64)) / 30.0f;
            I(o, 0x854) = 6;
        }
        break;
    case 0x2C:
        if (r != H(o, 0xA34)) {
            CharaPlayMotion_212590(o, I(o, 0x3F4), D_0045CDA8, 6, 1.0f);
            H(o, 0xA34) = r;
            I(o, 0xAD0) = 0;
            I(o, 0xAD4) = 0;
            CharaClearFlags_2124a0(o);
            I(o, 0x854) = I(o, 0x858) - 6;
            {
            V4 vD = {0};
            vD.x = Sinf_128fd0(F(o, 0x850));
            vD.z = Cosf_128d30(F(o, 0x850));
            K = D_0045B080[0];
            VecScale_1cbca0(&vD, &vD, 0.5f * K);
            CharaSetSrtVec40_238760(o, 0.0f, 0.0f, 0.0f);
            CharaSetVelocity_238770(o, 0.0f, 0.0f, 0.0f);
            CharaSetPosXYZ_2139e0(o, F(o, 0x830) - vD.x, F(o, 0x834) + (f32)(I(o, 0x854) - 1) * (D_0047DB50 * K), F(o, 0x838) - vD.z);
            CharaSetYaw_2138f0(o, F(o, 0x850));
            ModelSetPos_151110(I(o, 0x3F4), o + 0x70);
            }
        }
        break;
    case 0x2D:
        if (r != H(o, 0xA34)) {
            CharaPlayMotion_212590(o, I(o, 0x3F4), D_0045CDB8, 6, 1.0f);
            H(o, 0xA34) = r;
            I(o, 0xAD0) = 0;
            I(o, 0xAD4) = 0;
            CharaClearFlags_2124a0(o);
            F(o, 0x74) = F(o, 0x834) + (f32)(I(o, 0x854) - 1) * (D_0047DB50 * *(volatile f32 *)D_0045B080);
            I(o, 0x854) = I(o, 0x854) - 1;
        }
        break;
    case 0x2E:
        if (r != H(o, 0xA34)) {
            CharaPlayMotion_212590(o, I(o, 0x3F4), D_0045CDC8, 6, 1.0f);
            H(o, 0xA34) = r;
            I(o, 0xAD0) = 0;
            I(o, 0xAD4) = 0;
            CharaClearFlags_2124a0(o);
            F(o, 0x74) = F(o, 0x834) + (f32)(I(o, 0x854) - 1) * (D_0047DB50 * *(volatile f32 *)D_0045B080);
            I(o, 0x854) = I(o, 0x854) - 1;
        }
        break;
    case 0x2F:
        if (r != H(o, 0xA34)) {
            CharaPlayMotion_212590(o, I(o, 0x3F4), D_0045CDD8, 2, 1.0f);
            H(o, 0xA34) = r;
            I(o, 0xAD0) = 0;
            I(o, 0xAD4) = 0;
            CharaClearFlags_2124a0(o);
            F(o, 0x74) = F(o, 0x834) + (f32)(I(o, 0x854) - 1) * (D_0047DB50 * *(volatile f32 *)D_0045B080);
            I(o, 0x854) = 0;
        } else if (CharaPlayedMotionIsCurrent_2124c0(o) != 0 && !(CharaGetMotionFrame_238570(o) < 1.0f)) {
            F(o, 0x74) = F(o, 0x834);
            CharaLadderStateReset_21ae70(o + 0x830);
            CharaResetToBaseMode_21e830(o);
            CharaActLoco_21cc10(o, p);
            return;
        }
        break;
    case 0x32:
    case 0x33:
    case 0x34:
    case 0x36:
    case 0x37:
    case 0x38:
        break;
    case 0x65:
        CharaClearFlags_2124a0(o);
        CharaSetActionModeMoveMotion_21bbb0(o);
        H(o, 0xA34) = 0xCA;
        CharaActMoveMotion_21b180(o, p);
        return;
    default:
        CharaClearFlags_2124a0(o);
        CharaResetToBaseMode_21e830(o);
        CharaActLoco_21cc10(o, p);
        return;
    }
    *(u64 *)(o + 0x568) &= keep;
}
