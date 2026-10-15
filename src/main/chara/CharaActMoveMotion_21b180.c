#include "types.h"

typedef struct {
    s32 v[3];
} Key_0021b180;

typedef struct {
    f32 x, y, z, w;
} V4_0021b180;

typedef struct {
    u8 pad0[0xC];
    f32 xC;
} Rate_0021b180;

typedef struct {
    u8 pad0[0x30];
    u8 x30[0x44 - 0x30];
    s16 x44;
} Tgt_0021b180;

typedef struct Obj {
    u8 pad0[0x64];
    f32 x64;                            /* 0x64 */
    u8 pad68[0x70 - 0x68];
    f32 x70;                            /* 0x70 */
    f32 x74;
    f32 x78;
    u8 pad7C[0x80 - 0x7C];
    f32 x80;                            /* 0x80 */
    f32 x84;
    f32 x88;
    u8 pad8C[0x3D8 - 0x8C];
    s32 x3D8;                           /* 0x3D8 */
    u8 pad3DC[0x3F4 - 0x3DC];
    s32 m3F4;                           /* 0x3F4 */
    u8 pad3F8[0x428 - 0x3F8];
    s32 m428;                           /* 0x428 */
    s32 m42C;                           /* 0x42C */
    u8 pad430[0x440 - 0x430];
    f32 x440;                           /* 0x440 */
    f32 x444;
    f32 x448;
    u8 pad44C[0x450 - 0x44C];
    f32 x450;                           /* 0x450 */
    f32 x454;
    f32 x458;
    u8 pad45C[0x470 - 0x45C];
    f32 x470;                           /* 0x470 */
    f32 x474;
    f32 x478;
    u8 pad47C[0x490 - 0x47C];
    u8 x490[0x568 - 0x490];             /* 0x490 */
    u64 m568;                           /* 0x568 */
    u64 m570;                           /* 0x570 */
    u8 pad578[0xA2C - 0x578];
    s16 mA2C;                           /* 0xA2C */
    s16 mA2E;                           /* 0xA2E */
    u8 padA30[0xA32 - 0xA30];
    s16 mA32;                           /* 0xA32 */
    s16 mA34;                           /* 0xA34 */
    s16 mA36;                           /* 0xA36 */
    u8 padA38[0xA3A - 0xA38];
    s16 mA3A;                           /* 0xA3A */
    u8 padA3C[0xA3E - 0xA3C];
    s16 mA3E;                           /* 0xA3E */
    u8 padA40[0xAD0 - 0xA40];
    s32 mAD0;                           /* 0xAD0 */
    s32 mAD4;                           /* 0xAD4 */
} Obj;

extern void CharaPlayMotion_212590(Obj *, s32, char *, s32, f32);
extern s32 CharaPlayedMotionIsCurrent_2124c0(Obj *);
extern void CharaSetActionModeHang_21ae30(Obj *);
extern void CharaActHang_21a890(Obj *, s32);
extern void CharaActLoco_21cc10(Obj *, s32);
extern void CharaResetToBaseMode_21e830(Obj *);
extern s32 CharaInputInterruptMaybe_21e8f0(Obj *, s32);
extern u64 ActCfgTableEvalNormalPrmtFlags_221600(s32, s32, s32, f32);
extern u64 ActCfgTableEvalNormalPendingPrmtFlags_2217a0(s32, s32, s32, f32);
extern s32 CharaGetCurMotionName_238560(Obj *);
extern f32 CharaGetMotionFrame_238570(Obj *);
extern s32 CharaActMoveMotionNextStateMaybe_21ba40(Obj *);
extern s32 CharaTryStartAction_216700(Obj *, s32);
extern Rate_0021b180 *ActCfgTableFindMoveById_223080(s32, s32);
extern void CharaSetMoveDirXYZMaybe_213a90(Obj *, f32, f32, f32);
extern void CharaSetMoveDirMaybe_213b00(Obj *, f32 *);
extern void ModeInfoKeySet_215550(Key_0021b180 *, s32, s32, char *);
extern void ModeInfoKeyClear_215590(Key_0021b180 *);
extern char *ActCfgTableGetInfoNameByModeList_2154c0(s32, Key_0021b180 *, s32, char *);
extern char *strcpy(char *, const char *);
extern s32 Sprintf_1343b8(char *, const char *, ...);
extern void CharaSetVelocity_238770(Obj *, f32, f32, f32);
extern f32 VecDot3_1cba90(f32 *, f32 *);
extern f32 Atan2f_1291a8(f32, f32);
extern f32 AngleWrap_1cbf30(f32);
extern f32 Sinf_128fd0(f32);
extern f32 Cosf_128d30(f32);
extern void CharaSetFallPeakPosMaybe_213ad0(Obj *, f32 *);
extern void CharaGetPlatformVelMaybe_2384e0(Obj *, V4_0021b180 *);
extern s32 ModelHasMotion_20a5b0(s32, char *);
extern Tgt_0021b180 *CharaGetGroundTri_238410(Obj *, s32);
extern void VecScaleToLength_1cb510(void *, void *, f32);
extern f32 D_0047DB64;
extern const f32 D_0047D1FC __attribute__((section(".sdata")));
extern f32 D_0047DA74;
extern char D_0045CE90[];
extern char D_0045CE98[];
extern char D_0045CEA0[];
extern char D_0045CEA8[];
extern char D_0045CEB0[];
extern char D_0045CEB8[];
extern char D_0045CEC0[];
extern char D_0045CEC8[];
extern char D_0045CED0[];

void CharaActMoveMotion_21b180(Obj *p, s32 arg)
{
    u64 keep;
    u64 m;
    s32 st;
    s16 t;
    Rate_0021b180 *r;
    f32 ang;
    s32 id;
    f32 f;

    p->m42C = 0;
    keep = ActCfgTableEvalNormalPendingPrmtFlags_2217a0(p->m428, p->mA32, CharaGetCurMotionName_238560(p), CharaGetMotionFrame_238570(p));
    m = ActCfgTableEvalNormalPrmtFlags_221600(p->m428, p->mA32, CharaGetCurMotionName_238560(p), CharaGetMotionFrame_238570(p)) | 0xFF97CFFDE0000000ULL;
    if (p->mA34 != 4) {
        m |= 0x7FF;
    }
    p->m570 = p->m568 & m;
    st = CharaActMoveMotionNextStateMaybe_21ba40(p);
    switch (st) {
    case 0:
    case 1:
    case 4:
        t = p->mA2E;
        if (t != 0 && t != 1) {
            if (CharaTryStartAction_216700(p, arg) != 0) {
                return;
            }
        }
        keep |= (u64)0x400000 << 32;
        break;
    }
    p->m570 |= 0x800;
    p->m42C = (s32)ActCfgTableFindMoveById_223080(p->m428, 4);
    if (p->m570 & 0x40000000) {
        CharaSetMoveDirXYZMaybe_213a90(p, p->x470 - p->x70, 0.0f, p->x478 - p->x78);
    } else if (p->m570 & 3) {
        CharaSetMoveDirMaybe_213b00(p, &p->x440);
    }
    switch (st) {
    case 0:
        if (p->mA34 != st) {
            Key_0021b180 k[3];
            char name[0x20];
            V4_0021b180 d;

            ModeInfoKeySet_215550(&k[0], 3, 0x85, D_0045CE90);
            ModeInfoKeySet_215550(&k[1], 2, 0x7B, D_0045CE90);
            ModeInfoKeyClear_215590(&k[2]);
            strcpy(name, ActCfgTableGetInfoNameByModeList_2154c0(p->m428, k, p->mA2E, D_0045CE90));
            CharaSetVelocity_238770(p, 0.0f, 0.0f, 0.0f);
            if (p->m570 & 3) {
                if ((p->m570 & 0x80000000) && (p->m570 & 0x400)) {
                    r = ActCfgTableFindMoveById_223080(p->m428, 0x66);
                    if (r != 0) {
                        if (VecDot3_1cba90(&p->x450, &p->x440) < D_0047DB64) {
                            p->x64 = Atan2f_1291a8(p->x450, p->x458);
                            ang = AngleWrap_1cbf30(D_0047D1FC + p->x64);
                            t = p->mA2E;
                            if (t == 2) {
                                if (p->mA2C <= 0) {
                                    strcpy(name, D_0045CE98);
                                } else {
                                    Sprintf_1343b8(name, D_0045CEA0, p->mA2C + 0x60, D_0045CEA8);
                                }
                            } else if (t == 3) {
                                if (p->mA2C <= 0) {
                                    strcpy(name, D_0045CEB0);
                                } else {
                                    Sprintf_1343b8(name, D_0045CEB8, p->mA2C + 0x60, D_0045CEA8);
                                }
                            } else {
                                if (p->mA2C <= 0) {
                                    strcpy(name, D_0045CEA8);
                                } else {
                                    Sprintf_1343b8(name, D_0045CEC0, p->mA2C + 0x60, D_0045CEA8);
                                }
                                strcpy(name, D_0045CEA8);
                            }
                        } else {
                            ang = Atan2f_1291a8(p->x440, p->x448);
                        }
                        p->x80 = r->xC * Sinf_128fd0(ang);
                        p->x88 = r->xC * Cosf_128d30(ang);
                    }
                } else {
                    id = -1;
                    switch (p->mA3E) {
                    case 0xA:
                    case 0xB:
                    case 0xC:
                    case 0xD:
                    case 2:
                        id = 0x66;
                        break;
                    case 1:
                        id = 0x67;
                        break;
                    }
                    r = ActCfgTableFindMoveById_223080(p->m428, id);
                    CharaSetMoveDirMaybe_213b00(p, &p->x440);
                    if (r != 0) {
                        p->x80 = r->xC * p->x450;
                        p->x88 = r->xC * p->x458;
                    }
                }
            }
            CharaPlayMotion_212590(p, p->m3F4, name, 6, 1.0f);
            p->mA34 = st;
            p->mAD0 = 0;
            p->mAD4 = 0;
            p->mA36 = 2;
            CharaSetFallPeakPosMaybe_213ad0(p, &p->x70);
            CharaGetPlatformVelMaybe_2384e0(p, &d);
            p->x80 += d.x;
            p->x88 += d.z;
        }
        if (CharaPlayedMotionIsCurrent_2124c0(p) != 0) {
            if (!(CharaGetMotionFrame_238570(p) < 1.0f)) {
                Key_0021b180 k[3];
                char name[0x20];

                ModeInfoKeySet_215550(&k[0], 3, 0x86, D_0045CEC8);
                ModeInfoKeySet_215550(&k[1], 2, 0x7C, D_0045CEC8);
                ModeInfoKeyClear_215590(&k[2]);
                strcpy(name, ActCfgTableGetInfoNameByModeList_2154c0(p->m428, k, p->mA2E, D_0045CEC8));
                if (p->mA34 == 0xC9) {
                    f = 0.25f;
                } else {
                    f = D_0047DA74;
                }
                CharaPlayMotion_212590(p, p->m3F4, name, 0, f);
                p->mA34 = 1;
                p->mAD0 = 0;
                p->mAD4 = 0;
                p->mA36 = 2;
            } else {
                keep |= 3;
            }
        }
        break;
    case 1:
    case 2:
    case 6:
        if (p->mA34 != st) {
            Key_0021b180 k[3];
            char name[0x20];

            ModeInfoKeySet_215550(&k[0], 3, 0x86, D_0045CEC8);
            ModeInfoKeySet_215550(&k[1], 2, 0x7C, D_0045CEC8);
            ModeInfoKeyClear_215590(&k[2]);
            strcpy(name, ActCfgTableGetInfoNameByModeList_2154c0(p->m428, k, p->mA2E, D_0045CEC8));
            if (p->mA34 == 5) {
                f = 0.25f;
            } else {
                f = D_0047DA74;
            }
            CharaPlayMotion_212590(p, p->m3F4, name, 2, f);
            p->mA34 = st;
            *(f32 *)&p->mAD0 = (p->mA3A == 6) ? -10.0f : 0.0f;
            p->mAD4 = 0;
            CharaSetFallPeakPosMaybe_213ad0(p, &p->x70);
        }
        break;
    case 4:
        p->mA36 = 1;
        if (p->mA34 != st) {
            Key_0021b180 k[3];
            char name[0x20];

            ModeInfoKeySet_215550(&k[0], 3, 0x87, D_0045CED0);
            ModeInfoKeySet_215550(&k[1], 2, 0x7D, D_0045CED0);
            ModeInfoKeyClear_215590(&k[2]);
            strcpy(name, ActCfgTableGetInfoNameByModeList_2154c0(p->m428, k, p->mA2E, D_0045CED0));
            if (ModelHasMotion_20a5b0(p->m3F4, name) == 0) {
                CharaResetToBaseMode_21e830(p);
                CharaActLoco_21cc10(p, arg);
                return;
            }
            CharaPlayMotion_212590(p, p->m3F4, name, 6, 1.0f);
            p->mA34 = st;
            p->mAD0 = 0;
            p->mAD4 = 0;
            if (p->x3D8 & 4) {
                if (CharaGetGroundTri_238410(p, 0)->x44 == 8) {
                    p->mA34 = 5;
                    VecScaleToLength_1cb510(p->x490, CharaGetGroundTri_238410(p, 0)->x30, 6.0f);
                }
            }
        } else {
            if (CharaInputInterruptMaybe_21e8f0(p, arg) != 0) {
                return;
            }
            if (CharaPlayedMotionIsCurrent_2124c0(p) != 0 && !(CharaGetMotionFrame_238570(p) < 1.0f)) {
                CharaResetToBaseMode_21e830(p);
                CharaActLoco_21cc10(p, arg);
                return;
            }
        }
        break;
    case 5:
        break;
    case 0x64:
        CharaSetActionModeHang_21ae30(p);
        p->mA34 = 0xC8;
        CharaActHang_21a890(p, arg);
        return;
    default:
        CharaResetToBaseMode_21e830(p);
        CharaActLoco_21cc10(p, arg);
        return;
    }
    p->m568 &= keep;
}
