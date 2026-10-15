#include "types.h"

typedef struct V4 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} V4;

typedef struct Obj21e {
    u8 pad0[0x64];
    f32 m64;
    u8 pad68[0x70 - 0x68];
    f32 m70;
    u8 pad74[4];
    f32 m78;
    u8 pad7C[0x450 - 0x7C];
    V4 m450;
    u8 pad460[0x470 - 0x460];
    f32 m470;
    u8 pad474[4];
    f32 m478;
    u8 pad47C[0x570 - 0x47C];
    u64 m570;
    u8 pad578[0x6FB - 0x578];
    u8 m6FB;
    u8 pad6FC[0x8B0 - 0x6FC];
    u8 m8B0[0xA2E - 0x8B0];
    s16 mA2E;
    u8 padA30[0xA34 - 0xA30];
    s16 mA34;
    u8 padA36[0xA44 - 0xA36];
    u32 mA44;
    u8 padA48[0xAD8 - 0xA48];
    f32 mAD8;
    u8 padADC[0xB4C - 0xADC];
    s16 mB4C;
    s16 mB4E;
    s16 mB50;
    s16 mB52;
} Obj21e;

extern "C" {
f32 Cosf_128d30(f32);
f32 Sinf_128fd0(f32);
s32 Rand_133710(void);
s32 StrEqualNonNull_1ca6c0(s32, void *);
f32 VecDotXZ_1cba70(V4 *, V4 *);
s32 CharaResSptLoadDoneMaybe_1f08f0(s32, s32);
s32 GetGameMode_1f59c0(void);
s32 GetCharaResMgr_1fdb60(void);
s32 CharaActFlagsTurnBitsMaybe_20a590(u64);
s32 CharaIsMovingXZMaybe_20f9c0(Obj21e *);
s32 CharaHasLadder_210830(Obj21e *);
s32 CharaIsGroundReadyMaybe_210850(Obj21e *);
s32 CharaShouldStartFallMaybe_2108f0(Obj21e *);
s32 CharaSetMoveDirXYZMaybe_213a90(Obj21e *, f32, f32, f32);
s32 CharaIsWeaponDrawnMaybe_213f70(Obj21e *);
s32 CharaGetId_214a80(Obj21e *);
void CharaExecInfoInit_219100(void *);
s32 CharaGetCurMotionName_238560(Obj21e *);
s32 IsInBattle_288420(void);
extern f32 D_0047DB58;
extern u8 D_0045CF28[];
s32 CharaSelectLocoState_21e190(Obj21e *arg0);
}

#define BZERO(d, n) { u8 *p_ = (u8 *)(d); u32 n_ = (n); if (p_) while (n_) { *p_ = 0; n_--; p_++; } }

s32 CharaSelectLocoState_21e190(Obj21e *arg0)
{
    V4 v50;
    V4 v40;
    V4 v30;
    s32 v;
    s32 h;
    bool b1;
    bool ok;
    bool b;
    u64 x;

    switch (arg0->mA2E) {
    case 3:
    case 2:
    case 1:
    case 0:
        break;
    default:
        arg0->mA2E = 0;
    }
    if (CharaShouldStartFallMaybe_2108f0(arg0) != 0) {
        return 0x65;
    }
    switch (arg0->mA34) {
    case 0x28:
    case 0x29:
    case 0x2A:
    case 0x2B:
    case 0x2C:
    case 0x2D:
        return arg0->mA34;
    }
    v = GetGameMode_1f59c0();
    switch (v) {
    case 6:
    case 7:
        if (IsInBattle_288420() != 0) {
            if (CharaIsWeaponDrawnMaybe_213f70(arg0) == 0) {
                CharaExecInfoInit_219100(arg0->m8B0);
                switch (arg0->mB4C) {
                case 1:
                case 2:
                    h = GetCharaResMgr_1fdb60();
                    if (CharaResSptLoadDoneMaybe_1f08f0(h, CharaGetId_214a80(arg0)) != 0) {
                        return 0x28;
                    }
                }
            }
            arg0->mB50 = 0;
            arg0->mB52 = 0;
        } else {
            if (CharaIsWeaponDrawnMaybe_213f70(arg0) != 0) {
                ok = true;
                b1 = (arg0->mA44 & 0x1000000) && !(arg0->mA44 & 0x800000);
                if (b1 && arg0->m6FB != 0) {
                    ok = false;
                }
                if (ok) {
                    switch (arg0->mB50) {
                    case 2:
                        arg0->m6FB = 0;
                        h = GetCharaResMgr_1fdb60();
                        if (CharaResSptLoadDoneMaybe_1f08f0(h, CharaGetId_214a80(arg0)) != 0) {
                            if (arg0->mA2E == 2) {
                                return 0x2A;
                            }
                            if (arg0->mA2E == 3) {
                                return 0x2B;
                            }
                        } else {
                            arg0->mB50 = 0;
                            arg0->mB52 = 0;
                            arg0->mA2E = 0;
                            return -1;
                        }
                        break;
                    case 3:
                        arg0->m6FB = 0;
                        h = GetCharaResMgr_1fdb60();
                        if (CharaResSptLoadDoneMaybe_1f08f0(h, CharaGetId_214a80(arg0)) != 0) {
                            if (arg0->mA2E == 2) {
                                return 0x2C;
                            }
                            if (arg0->mA2E == 3) {
                                return 0x2D;
                            }
                        } else {
                            arg0->mB50 = 0;
                            arg0->mB52 = 0;
                            arg0->mA2E = 0;
                            return -1;
                        }
                        break;
                    }
                }
            }
            arg0->mB4C = 0;
            arg0->mB4E = 0;
        }
    }
    if ((arg0->m570 & 0x10000) && CharaIsGroundReadyMaybe_210850(arg0) != 0) {
        return 0x64;
    }
    if (IsInBattle_288420() == 0 && (arg0->m570 & 0x80000) && CharaHasLadder_210830(arg0) != 0) {
        return 0x66;
    }
    if (arg0->m570 & 0x80000000) {
        CharaSetMoveDirXYZMaybe_213a90(arg0, arg0->m470 - arg0->m70, 0.0f, arg0->m478 - arg0->m78);
        if (arg0->mA2E != 0 && arg0->mA2E != 1 && ((x = arg0->m570) & 3)) {
            switch (CharaActFlagsTurnBitsMaybe_20a590(x)) {
            case 0x200:
                return 0xA;
            case 0x400:
                return 0xB;
            case 0x80:
                return 0xC;
            case 0x100:
                return 0xD;
            }
        }
    }
    if (arg0->m570 & 0x40000000) {
        if (arg0->mA2E == 2) {
            BZERO(&v50, 0x10);
            v50.x = Sinf_128fd0(arg0->m64);
            v50.z = Cosf_128d30(arg0->m64);
            if (VecDotXZ_1cba70(&v50, &arg0->m450) < D_0047DB58) {
                return 2;
            }
        }
    }
    if (arg0->m570 & 3) {
        if (arg0->m570 & 2) {
            return 2;
        }
        if (arg0->m570 & 1) {
            return 1;
        }
    }
    if (arg0->m570 & 0x40000000) {
        return 0xE;
    }
    switch (arg0->mA34) {
    case 0:
        BZERO(&v40, 0x10);
        v40.x = Sinf_128fd0(arg0->m64);
        v40.z = Cosf_128d30(arg0->m64);
        if (VecDotXZ_1cba70(&v40, &arg0->m450) < D_0047DB58) {
            b = arg0->mA2E == 0 || arg0->mA2E == 1;
            return b ? 1 : 2;
        }
        break;
    case 2:
    case 1:
        BZERO(&v30, 0x10);
        v30.x = Sinf_128fd0(arg0->m64);
        v30.z = Cosf_128d30(arg0->m64);
        if (VecDotXZ_1cba70(&v30, &arg0->m450) < D_0047DB58) {
            arg0->m570 |= 0x800;
            return arg0->mA34;
        }
        break;
    }
    if (GetGameMode_1f59c0() == 6 && arg0->mA2E == 0 && arg0->mAD8 < 0.0f && arg0->mA34 != 0x1E && arg0->mA34 != 0x1F &&
        StrEqualNonNull_1ca6c0(CharaGetCurMotionName_238560(arg0), D_0045CF28) != 0) {
        return (Rand_133710() & 1) ? 0x1E : 0x1F;
    }
    switch (arg0->mA34) {
    case 0x15:
        if (CharaIsMovingXZMaybe_20f9c0(arg0) == 0) {
            return 0x16;
        }
    case 0x1E:
    case 0x1F:
    case 0x14:
    case 0x16:
        return arg0->mA34;
    }
    return 0;
}
