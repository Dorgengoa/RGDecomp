/* rgp:protos */
#line 1
#include "types.h"

class Ctl {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v20C(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0x20C, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};

typedef struct {
    Ctl *x0;
    f32 x4;
} Ctx_00217de0;

typedef struct {
    u8 pad0[0x4FC];
    s32 x4FC;
} Mdl_00217de0;

typedef struct Obj {
    u8 pad0[0x94];
    s32 x94;                            /* 0x94 */
    u8 pad98[0x3D0 - 0x98];
    u64 m3D0;                           /* 0x3D0 */
    u8 pad3D8[0x3F4 - 0x3D8];
    Mdl_00217de0 *m3F4;                 /* 0x3F4 */
    u8 pad3F8[0x428 - 0x3F8];
    s32 m428;                           /* 0x428 */
    s32 m42C;                           /* 0x42C */
    u8 pad430[0x568 - 0x430];
    u64 m568;                           /* 0x568 */
    u64 m570;                           /* 0x570 */
    u8 pad578[0x880 - 0x578];
    f32 x880;                           /* 0x880 */
    f32 x884;
    f32 x888;
    f32 x88C;
    f32 x890;                           /* 0x890 */
    u8 pad894[0xA2C - 0x894];
    s16 mA2C;                           /* 0xA2C */
    s16 mA2E;                           /* 0xA2E */
    u8 padA30[0xA32 - 0xA30];
    s16 mA32;                           /* 0xA32 */
    s16 mA34;                           /* 0xA34 */
    s16 mA36;                           /* 0xA36 */
    u8 padA38[0xAD0 - 0xA38];
    s32 mAD0;                           /* 0xAD0 */
    s32 mAD4;                           /* 0xAD4 */
} Obj;

extern "C" {
void CharaPlayMotion_212590(Obj *, Mdl_00217de0 *, char *, s32, f32);
s32 CharaPlayedMotionIsCurrent_2124c0(Obj *);
void CharaActLoco_21cc10(Obj *, Ctx_00217de0 *);
void CharaResetToBaseMode_21e830(Obj *);
s32 CharaInputInterruptMaybe_21e8f0(Obj *, Ctx_00217de0 *);
u64 ActCfgTableEvalNormalPrmtFlags_221600(s32, s32, s32, f32);
u64 ActCfgTableEvalNormalPendingPrmtFlags_2217a0(s32, s32, s32, f32);
s32 CharaGetCurMotionName_238560(Obj *);
f32 CharaGetMotionFrame_238570(Obj *);
s32 CharaBlownAwayNextState_218790(Obj *);
void CharaSetActionModeBlownAway_218840(Obj *);
extern "C" void CharaActBlownAway_217de0(Obj *p, Ctx_00217de0 *c, int rgp_a2, int rgp_a3);
char *strcpy(char *, const char *);
s32 Sprintf_1343b8(char *, const char *, ...);
void CharaSetVelocity_238770(Obj *, f32, f32, f32);
f32 AngleWrap_1cbf30(f32);
void CharaSetYaw_2138f0(Obj *, f32);
s32 GetCurrentScene_1f5be0(void);
s32 CharaGetId_214a80(Obj *);
void ParamTableSetAlpha_1cfb10(s32, s32, f32);
void SoundPlayScaledVolume_1b9520(s32, s32, s32, f32);
s32 CharaHasLandedMaybe_20fdb0(Obj *);
s32 GameSceneSoundSlot5GetHandle_1d0790(s32);
s32 CharaIsHeadUnderwaterMaybe_238250(Obj *);
s32 CharaIsMovingXZMaybe_20f9c0(Obj *);
void CharaSetInvincibleTime_2138a0(Obj *, f32);
extern f32 D_0047D1FC;
extern char D_0045CBD8[];
extern char D_0045CBF0[];
extern char D_0045CBF8[];
extern char D_0045CC38[];
extern char D_0045CC48[];
extern char D_0045CC58[];
extern char D_0045CC68[];
extern char D_0045CC78[];
extern char D_0045CC88[];
extern char D_0045CC98[];
extern char D_0045CCA8[];
extern char D_0045CCB0[];
extern char D_0045CCC0[];
extern char D_0045CCD0[];
extern char D_0045CCE0[];
}

#define MKNAME(name, s2, s3, base)                                              \
    if (p->mA2E == 2) {                                                         \
        if (p->mA2C <= 0) {                                                     \
            strcpy(name, s2);                                                   \
        } else {                                                                \
            Sprintf_1343b8(name, D_0045CBD8, p->mA2C + 0x60, base);              \
        }                                                                       \
    } else if (p->mA2E == 3) {                                                  \
        if (p->mA2C <= 0) {                                                     \
            strcpy(name, s3);                                                   \
        } else {                                                                \
            Sprintf_1343b8(name, D_0045CBF0, p->mA2C + 0x60, base);              \
        }                                                                       \
    } else {                                                                    \
        if (p->mA2C <= 0) {                                                     \
            strcpy(name, base);                                                 \
        } else {                                                                \
            Sprintf_1343b8(name, D_0045CBF8, p->mA2C + 0x60, base);              \
        }                                                                       \
        strcpy(name, base);                                                     \
    }

extern "C" void CharaActBlownAway_217de0(Obj *p, Ctx_00217de0 *c, int rgp_a2, int rgp_a3)
{
    u64 keep;
    s32 st;
    f32 a;

    p->m42C = 0;
    if (c->x0->v20C((int)(long)(c), (int)(long)(rgp_a2), (int)(long)(rgp_a3)) == 5) {
        CharaResetToBaseMode_21e830(p);
        CharaActLoco_21cc10(p, c);
        return;
    }
    keep = ActCfgTableEvalNormalPendingPrmtFlags_2217a0(p->m428, p->mA32, CharaGetCurMotionName_238560(p), CharaGetMotionFrame_238570(p));
    p->m570 = p->m568 & (ActCfgTableEvalNormalPrmtFlags_221600(p->m428, p->mA32, CharaGetCurMotionName_238560(p), CharaGetMotionFrame_238570(p)) | 0x0017C7FC00000000ULL);
    st = CharaBlownAwayNextState_218790(p);
    p->m3D0 &= 0xFFFFBFFFFFFFFFFFULL;
    switch (st) {
    case 0:
        if (p->mA34 != st) {
            char name[0x20] __attribute__((aligned(16)));

            MKNAME(name, D_0045CC38, D_0045CC58, D_0045CC48)
            CharaPlayMotion_212590(p, p->m3F4, name, 6, 1.0f);
            p->mA34 = st;
            p->mAD0 = 0;
            *(f32 *)&p->mAD4 = 0.0f;
            if (!(p->m3D0 & ((u64)2 << 32))) {
                CharaSetVelocity_238770(p, p->x880, 0.0f, p->x888);
                a = AngleWrap_1cbf30(p->x890 - D_0047D1FC);
                p->x94 = 0;
                CharaSetYaw_2138f0(p, a);
            }
            ParamTableSetAlpha_1cfb10(GetCurrentScene_1f5be0(), ((short)CharaGetId_214a80(p)), 1.0f);
            SoundPlayScaledVolume_1b9520(p->m3F4->x4FC, 8, 0, 1.0f);
        } else if (((unsigned char)CharaPlayedMotionIsCurrent_2124c0(p)) == 0 || (((unsigned char)CharaPlayedMotionIsCurrent_2124c0(p)) != 0 && !(CharaGetMotionFrame_238570(p) < 1.0f))) {
            if (CharaHasLandedMaybe_20fdb0(p) != 0) {
                char name[0x20] __attribute__((aligned(16)));

                MKNAME(name, D_0045CC68, D_0045CC88, D_0045CC78)
                CharaPlayMotion_212590(p, p->m3F4, name, 6, 1.0f);
                p->mA34 = 2;
                p->mAD0 = 0;
                p->mAD4 = 0;
            } else {
                char name[0x20] __attribute__((aligned(16)));

                MKNAME(name, D_0045CC98, D_0045CCB0, D_0045CCA8)
                CharaPlayMotion_212590(p, p->m3F4, name, 0, 1.0f);
                p->mA34 = 1;
                p->mAD0 = 0;
                p->mAD4 = 0;
                p->mA36 = 0x1A;
            }
        }
        break;
    case 1:
        p->m3D0 |= (u64)0x40000 << 32;
        p->mA36 = 0x1A;
        break;
    case 2:
        p->m3D0 |= (u64)0x20000000 << 32;
        if (p->mA34 != st) {
            char name[0x20] __attribute__((aligned(16)));

            MKNAME(name, D_0045CC68, D_0045CC88, D_0045CC78)
            CharaPlayMotion_212590(p, p->m3F4, name, 6, 1.0f);
            p->mA34 = st;
            p->mAD0 = 0;
            p->mAD4 = 0;
            p->mA36 = 0x1A;
        }
        if (*(f32 *)&p->mAD0 < 2.0f && 2.0f <= *(f32 *)&p->mAD0 + c->x4) {
            SoundPlayScaledVolume_1b9520(GameSceneSoundSlot5GetHandle_1d0790(GetCurrentScene_1f5be0()), 0x24, 0, 1.0f);
            p->m3D0 |= 0x80;
        }
        if (((unsigned char)CharaPlayedMotionIsCurrent_2124c0(p)) == 0 || (((unsigned char)CharaPlayedMotionIsCurrent_2124c0(p)) != 0 && !(CharaGetMotionFrame_238570(p) < 1.0f))) {
            if (((unsigned char)CharaIsHeadUnderwaterMaybe_238250(p)) != 0 || CharaIsMovingXZMaybe_20f9c0(p) == 0) {
                char name[0x20] __attribute__((aligned(16)));

                MKNAME(name, D_0045CCC0, D_0045CCE0, D_0045CCD0)
                CharaPlayMotion_212590(p, p->m3F4, name, 6, 1.0f);
                p->mA34 = 3;
                p->mAD0 = 0;
                p->mAD4 = 0;
                if (((short)CharaGetId_214a80(p)) >= 0 && ((short)CharaGetId_214a80(p)) < 12) {
                    CharaSetInvincibleTime_2138a0(p, 15.0f);
                }
            }
        }
        break;
    case 3:
        if (((unsigned char)CharaPlayedMotionIsCurrent_2124c0(p)) == 0 || (((unsigned char)CharaPlayedMotionIsCurrent_2124c0(p)) != 0 && !(CharaGetMotionFrame_238570(p) < 1.0f))) {
            CharaResetToBaseMode_21e830(p);
            CharaActLoco_21cc10(p, c);
            return;
        }
        if (CharaInputInterruptMaybe_21e8f0(p, c) != 0) {
            return;
        }
        break;
    default:
        CharaSetActionModeBlownAway_218840(p);
        CharaActBlownAway_217de0(p, c, 0, 0);
        return;
    }
    p->m3D0 |= 4;
    p->m3D0 |= (u64)0x4000000 << 32;
    p->m568 &= keep;
}
