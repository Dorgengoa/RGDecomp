#include "types.h"
#pragma divbyzerocheck on

typedef struct {
    f32 x, y, z, w;
} Vec;

typedef struct {
    u8 pad0[0x64];
    f32 f64;
    u8 pad68[0x18];
    Vec f80;
    u8 pad90[0x340];
    u64 f3D0;
    u32 f3D8;
    u8 pad3DC[0x18];
    s32 f3F4;
    u8 pad3F8[0x2C];
    s16 f424;
    u8 pad426[2];
    s32 f428;
    s32 f42C;
    u8 pad430[0x10];
    u8 f440[0x10];
    u8 f450[0x118];
    u64 f568;
    u64 f570;
    u8 pad578[0x498];
    f32 fA10;
    u8 padA14[0x18];
    s16 fA2C;
    s16 fA2E;
    u8 padA30[2];
    s16 fA32;
    s16 fA34;
    u8 padA36[4];
    s16 fA3A;
    s16 fA3C;
    u8 padA3E[2];
    s16 fA40;
    u8 padA42[2];
    u32 fA44;
    u8 padA48[0x88];
    f32 fAD0;
    f32 fAD4;
    f32 fAD8;
} Chr;

typedef struct {
    u8 pad0[4];
    f32 f4;
} Step;

typedef struct {
    u8 pad0[0xC];
    f32 fC;
} Mot;

typedef struct {
    u8 pad0[0x42];
    s16 f42;
} Anm;

typedef struct {
    u8 pad0[0x18];
    struct {
        u8 pad0[0x18E];
        s16 f18E;
    } *f18;
} Ctx;

typedef struct {
    u8 pad0[0x4344];
    s32 f4344;
} Wld;

extern "C" {
f32 Cosf_128d30(f32);
f32 Sinf_128fd0(f32);
f32 RandFloat_13c010(void);
void Sprintf_1343b8(char *, const char *, s32, const char *);
f32 VecLengthSqXZ_1cb450(Vec *);
f32 VecDotXZ_1cba70(f32 *, void *);
void GameSceneSoundSlot5PlaySeVol_1d05d0(s32, s32, f32);
s32 GetGameMode_1f59c0(void);
s32 GetCurrentScene_1f5be0(void);
Ctx *GetGameData_1fede0(void);
s32 ModelHasMotion_20a5b0(s32, const char *);
s32 CharaIsLandedOrLockedMaybe_2109c0(Chr *);
void CharaClearFlags_2124a0(Chr *);
s32 CharaPlayedMotionIsCurrent_2124c0(Chr *);
void CharaPlayMotion_212590(Chr *, s32, const char *, s32, f32);
void CharaSetMoveDirXYZMaybe_213a90(Chr *, f32, f32, f32);
void CharaSetMoveDirMaybe_213b00(Chr *, void *);
s32 CharaGetId_214a80(Chr *);
void CharaClearActionEffects_214ce0(Chr *);
s32 CharaTryStartAction_216700(Chr *, Step *);
void CharaActLadder_2198e0(Chr *, Step *);
void CharaSetActionModeLadder_21a850(Chr *);
void CharaActMoveMotion_21b180(Chr *, Step *);
void CharaSetActionModeMoveMotion_21bbb0(Chr *);
void CharaActBattleInOut_21bbf0(Chr *, Step *);
void CharaSetActionModeBattleInOut_21c190(Chr *);
s32 CharaSelectLocoState_21e190(Chr *);
void CharaResetToBaseMode_21e830(Chr *);
void ActCfgTableGetWalkMotionName_21f550(s32, char *, s32);
void ActCfgTableGetRunMotionName_21f570(s32, char *, s32);
void ActCfgTableGetStandMotionName_21f590(s32, char *, s32);
u64 ActCfgTableEvalNormalPrmtFlags_221600(s32, s32, s32, f32);
u64 ActCfgTableEvalNormalPendingPrmtFlags_2217a0(s32, s32, s32, f32);
void ActCfgTableRunNormalEvntsById_2224d0(s32, s32, s32);
Mot *ActCfgTableFindMoveById_223080(s32, s32);
Anm *CharaGetGroundTri_238410(Chr *, s32);
s32 CharaIsCurMotion_238540(Chr *, char *);
s32 CharaGetCurMotionName_238560(Chr *);
f32 CharaGetMotionFrame_238570(Chr *);
void CharaGetRot_2388b0(Chr *, Vec *);
u32 IsInBattle_288420(void);
char *strcpy(char *, const char *);

extern char D_0045CEA0[];
extern char D_0045CEB8[];
extern char D_0045CEC0[];
extern char D_0045CF30[];
extern char D_0045CF40[];
extern char D_0045CF48[];
extern char D_0045CF50[];
extern char D_0045CF58[];
extern char D_0045CF60[];
extern char D_0045CF68[];
extern char D_0045CF70[];
extern char D_0045CF78[];
extern char D_0045CF80[];
extern char D_0045CF88[];
extern char D_0045CF90[];
extern char D_0045CF98[];
extern char D_0045CFA0[];
extern char D_0045CFA8[];
extern char D_0045CFB8[];
extern char D_0045CFC0[];
extern f32 D_0047D5D0;
extern f32 D_0047D800;
extern f32 D_0047DB20;
extern f32 D_0047DB50;
extern f32 D_0047DB58;
}

extern "C" void CharaActLoco_21cc10(Chr *c, Step *st);

static inline bool Low(s32 s) {
    return s == 0 || s == 1;
}

static inline void Wait(Chr *c, s32 r, char *buf, const char *s2, const char *s3, const char *base) {
    if (c->fA34 != r) {
        if (c->fA2E == 2) {
            if (c->fA2C <= 0) {
                strcpy(buf, s2);
            } else {
                Sprintf_1343b8(buf, D_0045CEA0, c->fA2C + 0x60, base);
            }
        } else if (c->fA2E == 3) {
            if (c->fA2C <= 0) {
                strcpy(buf, s3);
            } else {
                Sprintf_1343b8(buf, D_0045CEB8, c->fA2C + 0x60, base);
            }
        } else {
            if (c->fA2C <= 0) {
                strcpy(buf, base);
            } else {
                Sprintf_1343b8(buf, D_0045CEC0, c->fA2C + 0x60, base);
            }
            strcpy(buf, base);
        }
        CharaPlayMotion_212590(c, c->f3F4, buf, 0, 0.25f);
        c->fA34 = r;
        c->fAD0 = 0.0f;
        c->fAD4 = 0.0f;
    }
    c->f3D0 |= 0x10000000;
    c->f3D0 |= 0x20000000;
}

void CharaActLoco_21cc10(Chr *c, Step *st) {
    s32 prev;
    u64 mask;
    u64 m2;
    s32 r;
    s32 s;
    bool b;
    s32 t;
    u32 fl;
    Mot *mo;
    Ctx *ctx;
    Wld *wl;
    s32 id;
    f32 f;
    f32 f20;

    prev = c->fA34;
    c->f42C = 0;
    mask = ActCfgTableEvalNormalPendingPrmtFlags_2217a0(c->f428, c->fA32, CharaGetCurMotionName_238560(c), CharaGetMotionFrame_238570(c));
    m2 = ActCfgTableEvalNormalPrmtFlags_221600(c->f428, c->fA32, CharaGetCurMotionName_238560(c), CharaGetMotionFrame_238570(c)) | 0xFF97CFFDE0990FFFULL;
    switch (c->fA34) {
    case 0:
    case 2:
    case 1:
        m2 |= 0x2380000020000000ULL;
        break;
    }
    c->f570 = c->f568 & m2;
    r = CharaSelectLocoState_21e190(c);
    if (r == 1 && c->fA2E != 0 && c->fA2E != 1) r = 2;
    if (r == 0 && c->fA34 == 2 && ((t = c->fA32) == 0 || t == 1) && !(c->fAD0 < 15.0f)) {
        if (GetGameMode_1f59c0() == 6 || (GetGameMode_1f59c0() == 7 && IsInBattle_288420() == 0)) {
            if (c->f3D8 & 4) {
                if (ModelHasMotion_20a5b0(c->f3F4, D_0045CF30) != 0) {
                    mo = ActCfgTableFindMoveById_223080(c->f428, 0x66);
                    if (mo != 0) {
                        f = mo->fC;
                        f20 = D_0047D800 * f;
                        if (!(VecLengthSqXZ_1cb450(&c->f80) <= f20 * f20)) r = 0x14;
                    }
                }
            }
        }
    }
    fl = c->fA44 & 0x1000000;
    if (fl && c->fAD0 <= 15.0f) {
        switch (r) {
        case 0:
        case 2:
        case 1:
            switch (c->fA34) {
            case 2:
            case 1:
                r = c->fA34;
                break;
            }
            break;
        }
    }
    if (!fl) {
        switch (r) {
        case 0:
            switch (c->fA34) {
            case 2:
            case 1:
                c->fAD4 += st->f4;
                if (c->fAD4 < 3.0f || c->fAD0 < 3.0f) r = c->fA34;
                break;
            default:
                c->fAD4 = 0.0f;
                break;
            }
            break;
        case 2:
            switch (c->fA34) {
            case 0:
                c->fAD4 += st->f4;
                if (c->fAD4 < 3.0f || c->fAD0 < 3.0f) r = c->fA34;
                break;
            case 1:
                c->fAD4 = 0.0f;
                break;
            default:
                c->fAD4 = 0.0f;
                break;
            }
            break;
        case 1:
            switch (c->fA34) {
            case 0:
            case 2:
                c->fAD4 += st->f4;
                if (c->fAD4 < 3.0f || c->fAD0 < 3.0f) r = c->fA34;
                break;
            default:
                c->fAD4 = 0.0f;
                break;
            }
            break;
        }
    }
    switch (r) {
    case 0:
    case 1:
    case 2:
    case 0x1E:
    case 0x1F:
    case 0x14:
    case 0x15:
    case 0x16:
    case 0xA:
    case 0xB:
    case 0xC:
    case 0xD:
    case 0xE:
        if (CharaIsLandedOrLockedMaybe_2109c0(c) == 0 || CharaTryStartAction_216700(c, st) == 0) {
            mask |= 0x0040000000000000ULL;
        } else {
            return;
        }
        break;
    }
    c->f570 |= 0x800;
    switch (r) {
    case 0: {
        char buf[0x20];
        Vec v;

        if (c->fA34 == r) break;
        ActCfgTableGetStandMotionName_21f590(c->f428, buf, c->fA2E);
        if (c->fA34 != -1 && CharaIsCurMotion_238540(c, buf) != 0) break;
        f = 1.0f;
        if (c->fA40 != 0) {
            f = c->fA10;
            switch (c->fA3C) {
            case 11:
                f = D_0047DB20;
                break;
            }
        } else {
            switch (c->fA3A) {
            case 0:
            case 1:
                f = D_0047DB20;
                break;
            case 2:
                f = D_0047DB50;
                break;
            case 3:
                f = D_0047DB50;
                break;
            case 6:
                f = D_0047DB20;
                break;
            case 7:
                break;
            case 15:
                if (c->f424 >= 0x80 && c->f424 < 0x9C) {
                    f = f;
                }
                break;
            }
        }
        CharaPlayMotion_212590(c, c->f3F4, buf, 0, f);
        c->fA34 = r;
        c->fAD0 = 0.0f;
        c->fAD4 = 0.0f;
        c->fAD8 = 150.0f + 150.0f * RandFloat_13c010();
        CharaClearFlags_2124a0(c);
        CharaGetRot_2388b0(c, &v);
        f20 = Sinf_128fd0(v.y);
        CharaSetMoveDirXYZMaybe_213a90(c, f20, 0.0f, Cosf_128d30(v.y));
        break;
    }
    case 2: {
        char buf[0x20];

        if (c->fA34 != r) {
            if (!(c->fA44 & 0x1000000)) {
                ActCfgTableGetRunMotionName_21f570(c->f428, buf, c->fA2E);
                f = 1.0f;
                if (c->fA40 == 0) {
                    switch (c->fA3A) {
                    case 0:
                    case 1:
                        f = 0.5f;
                        break;
                    case 2:
                        f = 0.5f;
                        break;
                    case 3:
                        f = 0.5f;
                        break;
                    }
                }
                CharaPlayMotion_212590(c, c->f3F4, buf, 0, f);
            }
            c->fA34 = r;
            c->fAD0 = 0.0f;
            c->fAD4 = 0.0f;
        }
        if (c->f570 & 3) CharaSetMoveDirMaybe_213b00(c, c->f440);
        break;
    }
    case 1: {
        char buf[0x20];

        if (c->fA34 != r) {
            if (!(c->fA44 & 0x1000000)) {
                ActCfgTableGetWalkMotionName_21f550(c->f428, buf, c->fA2E);
                f = 1.0f;
                if (c->fA40 == 0) {
                    switch (c->fA3A) {
                    case 0:
                    case 1:
                        f = 0.5f;
                        break;
                    case 2:
                        f = 0.5f;
                        break;
                    case 3:
                        f = 0.5f;
                        break;
                    }
                }
                CharaPlayMotion_212590(c, c->f3F4, buf, 0, f);
            }
            c->fA34 = r;
            c->fAD0 = 0.0f;
            c->fAD4 = 0.0f;
        }
        if (c->f570 & 3) CharaSetMoveDirMaybe_213b00(c, c->f440);
        break;
    }
    case 0xA: {
        char buf[0x20];

        Wait(c, r, buf, D_0045CF40, D_0045CF50, D_0045CF48);
        break;
    }
    case 0xB: {
        char buf[0x20];

        Wait(c, r, buf, D_0045CF58, D_0045CF68, D_0045CF60);
        break;
    }
    case 0xC: {
        char buf[0x20];

        Wait(c, r, buf, D_0045CF70, D_0045CF80, D_0045CF78);
        break;
    }
    case 0xD: {
        char buf[0x20];

        Wait(c, r, buf, D_0045CF88, D_0045CF98, D_0045CF90);
        break;
    }
    case 0xE: {
        char bufC[0x20];
        char bufA[0x20];

        ActCfgTableGetStandMotionName_21f590(c->f428, bufC, c->fA2E);
        ActCfgTableGetRunMotionName_21f570(c->f428, bufA, c->fA2E);
        {
        f32 v[4] = {0};

        v[0] = Sinf_128fd0(c->f64);
        v[2] = Cosf_128d30(c->f64);
        if (!(VecDotXZ_1cba70(v, c->f450) < D_0047DB58)) {
            if (CharaIsCurMotion_238540(c, bufC) == 0) {
                CharaPlayMotion_212590(c, c->f3F4, bufC, 0, D_0047D5D0);
            }
        } else {
            if (CharaIsCurMotion_238540(c, bufA) == 0) {
                CharaPlayMotion_212590(c, c->f3F4, bufA, 0, D_0047DB50);
            }
        }
        }
        c->fA34 = r;
        c->fAD0 = 0.0f;
        c->fAD4 = 0.0f;
        break;
    }
    case 0x14:
        if (c->fA34 != r) {
            CharaPlayMotion_212590(c, c->f3F4, D_0045CF30, 2, 0.5f);
            c->fA34 = r;
            c->fAD0 = 0.0f;
            c->fAD4 = 0.0f;
            switch (CharaGetGroundTri_238410(c, 0)->f42) {
            case 14:
            case 17:
            case 16:
            case 7:
                GameSceneSoundSlot5PlaySeVol_1d05d0(GetCurrentScene_1f5be0(), 0x25, 1.0f);
                break;
            }
        }
        if (CharaPlayedMotionIsCurrent_2124c0(c) != 0 && !(CharaGetMotionFrame_238570(c) < 1.0f)) {
            CharaPlayMotion_212590(c, c->f3F4, D_0045CFA0, 4, 1.0f);
            c->fA34 = 0x15;
        }
        break;
    case 0x15:
        break;
    case 0x16:
        if (c->fA34 != r) {
            CharaPlayMotion_212590(c, c->f3F4, D_0045CFA8, 6, 1.0f);
            c->fA34 = r;
            c->fAD0 = 0.0f;
            c->fAD4 = 0.0f;
        }
        if (CharaPlayedMotionIsCurrent_2124c0(c) != 0 && !(CharaGetMotionFrame_238570(c) < 1.0f)) {
            CharaResetToBaseMode_21e830(c);
            CharaActLoco_21cc10(c, st);
            return;
        }
        break;
    case 0x1E:
    case 0x1F: {
        Vec v;

        if (c->fA34 != r) {
            if (r == 0x1E) {
                CharaPlayMotion_212590(c, c->f3F4, D_0045CFB8, 2, D_0047D5D0);
            } else {
                CharaPlayMotion_212590(c, c->f3F4, D_0045CFC0, 2, D_0047D5D0);
            }
            c->fA34 = r;
            c->fAD0 = 0.0f;
            c->fAD4 = 0.0f;
            CharaClearFlags_2124a0(c);
            CharaGetRot_2388b0(c, &v);
            f20 = Sinf_128fd0(v.y);
            CharaSetMoveDirXYZMaybe_213a90(c, f20, 0.0f, Cosf_128d30(v.y));
        }
        ctx = GetGameData_1fede0();
        wl = (Wld *)GetCurrentScene_1f5be0();
        id = ctx->f18->f18E;
        if ((CharaGetId_214a80(c) == id && wl->f4344 == 3) ||
            (CharaPlayedMotionIsCurrent_2124c0(c) != 0 && !(CharaGetMotionFrame_238570(c) < 1.0f))) {
            CharaResetToBaseMode_21e830(c);
            CharaActLoco_21cc10(c, st);
            return;
        }
        break;
    }
    case 0x32:
        break;
    case 0x33:
        break;
    case 0x28:
    case 0x29:
    case 0x2A:
    case 0x2B:
    case 0x2C:
    case 0x2D:
        CharaSetActionModeBattleInOut_21c190(c);
        c->fA34 = r;
        CharaActBattleInOut_21bbf0(c, st);
        return;
    case 0x64:
        CharaSetActionModeMoveMotion_21bbb0(c);
        c->fA34 = 200;
        CharaActMoveMotion_21b180(c, st);
        return;
    case 0x65:
        CharaSetActionModeMoveMotion_21bbb0(c);
        s = c->fA2E;
        b = true;
        if (c->fA2E != 0 && c->fA2E != 1) b = false;
        c->fA34 = b ? 0xC9 : 0xCB;
        CharaActMoveMotion_21b180(c, st);
        return;
    case 0x66:
        CharaSetActionModeLadder_21a850(c);
        c->fA34 = 200;
        CharaActLadder_2198e0(c, st);
        return;
    default:
        CharaResetToBaseMode_21e830(c);
        CharaActLoco_21cc10(c, st);
        return;
    }
    switch (c->fA34) {
    case 0:
        c->f42C = (s32)ActCfgTableFindMoveById_223080(c->f428, 0x65);
        break;
    case 1:
        c->f42C = (s32)ActCfgTableFindMoveById_223080(c->f428, 0x67);
        break;
    case 2:
    case 0x14:
    case 0x15:
    case 0x16:
        c->f42C = (s32)ActCfgTableFindMoveById_223080(c->f428, 0x66);
        break;
    case 0xE:
        c->f570 &= ~3ULL;
    case 0xA:
    case 0xB:
    case 0xC:
    case 0xD:
        c->f42C = (s32)ActCfgTableFindMoveById_223080(c->f428, 0x68);
        break;
    }
    switch (c->fA34) {
    case 0:
    case 1:
    case 2:
    case 0x15:
    case 0x16:
    case 0x1E:
    case 0x1F:
        switch (c->fA2E) {
        case 0:
        case 1:
            c->f570 |= 0x4000000;
            c->f570 |= 0x8000000;
            break;
        case 2:
            c->f570 |= 0x10000000;
            c->f570 |= 0x8000000;
            break;
        case 3:
            break;
        }
        break;
    }
    if (prev == -1) {
        CharaClearActionEffects_214ce0(c);
        ActCfgTableRunNormalEvntsById_2224d0(c->f428, c->f424, c->fA32);
    }
    c->f3D0 |= 0x0400000000000000ULL;
    c->f568 &= mask;
    c->fAD8 -= st->f4;
    if (c->fAD8 < 0.0f) c->fAD8 = -1.0f;
}
