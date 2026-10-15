#include "types.h"
/* insect 0x004F88A0 -- 1,452 bytes.  One `jalr $25` at 004F8D9C:
 * `lw $25,0x1B0($17) / lw $25,0x44($25)` = C++ virtual #15 (slot 0x44 =
 * 8 + 4*15) on a class whose vptr sits at +0x1B0.  Same class as the merged
 * insect_InsectBattleDrawMarkerModels_4f4a30 / insect_InsectBattleSpawnBombModel_50ee60.  [[jalr-is-cpp-virtual]]
 *
 * Inner switch: the compare chain tests 0x3B, 0xB, 0x3D, 0xA, 0x3A, 0x39, 1,
 * so SOURCE order is the reverse -- 1, 0x39, 0x3A, 0xA, 0x3D, 0xB, 0x3B -- and
 * the arm addresses (4F89AC, 4F89C0, 4F8A70, 4F8AE4, 4F8B94, 4F8BF8, 4F8C58)
 * run forwards in exactly that order.
 *
 * insect's _gp is 0x00485170, so `lb -0x4248($28)` is D_00480F28.
 */

class VE {
public:
    u8 pad000[0x1B0];
    virtual void s00(); virtual void s01(); virtual void s02();
    virtual void s03(); virtual void s04(); virtual void s05();
    virtual void s06(); virtual void s07(); virtual void s08();
    virtual void s09(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(f32 t);            /* slot 0x44 */
};

struct Ent {
    u8  pad000[0x39];
    s8  f039;                   /* +0x39 */
    u8  pad03A[0x6C - 0x3A];
    s16 f06C;                   /* +0x6C */
    u8  pad06E[0x73 - 0x6E];
    s8  f073;                   /* +0x73 */
    s8  f074;                   /* +0x74 */
    u8  pad075[0xDC - 0x75];
    s16 f0DC;                   /* +0xDC */
};

struct EL2 { u8 pad000[0x994]; };

struct Sub {
    u8  pad000[0x14];
    s16 f014;                   /* +0x14 */
    s16 f016;                   /* +0x16 */
    u8  pad018[0x20 - 0x18];
};

struct Ins {
    u8   pad000[0x35F8];
    EL2  arr[2];                    /* +0x35F8, stride 0x994 */
    Sub  arr2[2];                   /* +0x4920, stride 0x20 */
    u8   f4960[0x4B4C - 0x4960];    /* +0x4960 */
    u8   f4B4C[0x5000 - 0x4B4C];    /* +0x4B4C */
    u8   f5000[0x58];               /* +0x5000 */
    u8   f5058[0x506C - 0x5058];    /* +0x5058 */
    u8   f506C[0x5DA8 - 0x506C];    /* +0x506C */
    s32  f5DA8;                     /* +0x5DA8 */
    u8   pad5DAC[0x5EFC - 0x5DAC];
    s16  f5EFC;                     /* +0x5EFC */
    s16  f5EFE;                     /* +0x5EFE */
    u8   pad5F00[0x5FC8 - 0x5F00];
    f32  f5FC8;                     /* +0x5FC8 */
};

extern s8 D_00480F28;
extern const char D_00524C88[];

extern "C" void  func_1343B8(char *d, const char *f, s32 a);

extern "C" void  insect_InsectBoardPieceWorldPos_4edad0(void *t, Ent *p, f32 *x, f32 *y, f32 *z);
extern "C" void  insect_InsectBoardPlacePiece_4ef830(void *t, Ent *p, s16 x, s16 y);
extern "C" s32   insect_InsectFormationGetRow_4efdc0(void *p, s32 n);
extern "C" void  insect_InsectFormationDecodeCell_4effa0(s32 r, s32 i, s32 *a, s32 *b, s32 c);
extern "C" s32   insect_InsectBattleGetStep_50d6a0(Ins *o, s32 k);
extern "C" void  insect_InsectBattleSetStep_50d7a0(Ins *o, s32 a, s32 b, s32 c);
extern "C" void  insect_InsectBattleSetState_50d8c0(Ins *o, s32 a, s32 b, s32 c);
extern "C" void  insect_InsectBattleSetFlag_50dad0(Ins *o, s32 k);
extern "C" VE   *insect_InsectBattleGetPieceModel_50df60(Ins *o, Ent *p);
extern "C" s32   insect_InsectBattleSpawnBombModel_50ee60(Ent *p);
extern "C" s32   insect_InsectBattleRequestBombModel_50f100(Ent *p);
extern "C" void  insect_InsectBattlePieceApplyColor_50fa30(VE *q, Ent *p);
extern "C" void  insect_InsectBattlePieceSetDesignVisible_50fa80(VE *q, Ent *p, s32 k);
extern "C" s32   insect_InsectFileSlotGetData_511fa0(void *p, s32 *out);
extern "C" s32   insect_InsectFileSlotIsLoaded_512010(void *p);
extern "C" void  insect_InsectFileSlotRelease_512020(void *p);
extern "C" void  insect_InsectFileSlotRequest_512140(void *p, char *s, s32 k);
extern "C" s16   insect_InsectModelMemCreatePiece_5125f0(void *b, s32 a, s32 c);
extern "C" const char *insect_InsectMsgGet_512b70(void *m, s32 k);
extern "C" s32   insect_InsectTeamGetFormation_5138c0(EL2 *e);
extern "C" Ent  *insect_InsectTeamGetPiece_5138d0(EL2 *e, s32 i);
extern "C" void  insect_InsectTeamBuild_513920(EL2 *e, Sub *w, s32 g, s32 v);
extern "C" void  insect_InsectTeamSetSide_513cf0(EL2 *e, s32 g);
extern "C" void  insect_InsectTeamReset_513d00(EL2 *e, f32 t);
extern "C" void  insect_InsectTeamSlotSetName_5140f0(Sub *w, const char *s);
extern "C" void  insect_InsectTeamSlotAddMember_514190(Sub *w, s32 i);
extern "C" void  insect_InsectTeamSlotInit_514240(Sub *w, s32 k);
extern "C" void  insect_InsectPieceSetBaseMotion_5153e0(Ent *p, s32 a, s32 b, s32 c, s32 d);
extern "C" void  insect_InsectPieceSetPos_5159b0(Ent *p, f32 x, f32 y, f32 z);

extern "C" void insect_InsectBattleLoadTeams_4f88a0(Ins *o)
{
    s32   nn;
    s32   a;
    s32   b;
    f32   fx;
    f32   fy;
    f32   fz;
    char  buf[0x18];
    s32   v;
    s32   i;
    EL2  *e;
    s32   j;
    s32   k;
    s32   r;
    s32   d;
    s32   gg;
    void *t;
    void *m;
    void *bb;
    VE   *q;
    Sub  *w;
    Ent  *p;

    switch (o->f5DA8) {
    case 3:
    case 6:
        insect_InsectBattleSetState_50d8c0(o, 0, 1, -1);
        return;
    case 0:
        break;
    default:
        o->f5EFE = -1;
        o->f5EFC = -1;
        break;
    }
    m = o->f506C;
    p = 0;
    bb = o->f4B4C;
    t = o->f4960;
    w = &o->arr2[D_00480F28];
    e = &o->arr[D_00480F28];
    switch (insect_InsectBattleGetStep_50d6a0(o, 1)) {
    case 1:
        D_00480F28 = 1;
        insect_InsectBattleSetStep_50d7a0(o, 0x39, 1, -1);
        break;
    case 0x39:
        insect_InsectTeamSlotInit_514240(w, 0x39);
        w->f014 = o->f5EFC;
        w->f016 = o->f5EFE;
        v = o->f5DA8;
        if (v != 0 && v != 3) {
            for (i = 0; i < 5; i++) {
                insect_InsectTeamSlotAddMember_514190(w, i);
            }
            insect_InsectTeamSlotSetName_5140f0(w, insect_InsectMsgGet_512b70(m, D_00480F28 + 0xC));
        }
        insect_InsectTeamReset_513d00(e, o->f5FC8);
        insect_InsectTeamSetSide_513cf0(e, D_00480F28);
        insect_InsectTeamBuild_513920(e, w, D_00480F28, o->f5DA8);
        insect_InsectBattleSetStep_50d7a0(o, 0x3A, 1, -1);
        break;
    case 0x3A:
        i = 0;
        while (i < 5) {
            p = insect_InsectTeamGetPiece_5138d0(e, i);
            if (p != 0 && p->f06C == -1) {
                break;
            }
            i++;
        }
        func_1343B8(buf, D_00524C88, p->f0DC);
        insect_InsectFileSlotRequest_512140(o->f5000, buf, 2);
        insect_InsectBattleSetStep_50d7a0(o, 0xA, 1, -1);
        break;
    case 0xA:
        if (insect_InsectFileSlotIsLoaded_512010(o->f5000) != 0) {
            nn = 0;
            d = insect_InsectFileSlotGetData_511fa0(o->f5000, &nn);
            i = 0;
            while (i < 5) {
                p = insect_InsectTeamGetPiece_5138d0(e, i);
                if (p != 0 && p->f06C == -1) {
                    break;
                }
                i++;
            }
            p->f06C = insect_InsectModelMemCreatePiece_5125f0(bb, d, nn);
            insect_InsectFileSlotRelease_512020(o->f5000);
            k = 0xB;
            if (insect_InsectBattleRequestBombModel_50f100(p) != 0) {
                k = 0x3D;
            }
            insect_InsectBattleSetStep_50d7a0(o, k, 1, -1);
        }
        break;
    case 0x3D:
        i = 4;
        while (i >= 0) {
            p = insect_InsectTeamGetPiece_5138d0(e, i);
            if (p != 0 && p->f06C != -1) {
                break;
            }
            i--;
        }
        if (p != 0 && insect_InsectBattleSpawnBombModel_50ee60(p) != 0) {
            insect_InsectBattleSetStep_50d7a0(o, 0xB, 1, -1);
        }
        break;
    case 0xB:
        p = insect_InsectTeamGetPiece_5138d0(e, 4);
        if (p != 0) {
            if (p->f06C != -1) {
                insect_InsectBattleSetStep_50d7a0(o, 0x3B, 1, -1);
                insect_InsectBattleSetStep_50d7a0(o, 0xB, 0, -1);
            } else {
                insect_InsectBattleSetStep_50d7a0(o, 0x3A, 1, -1);
            }
        }
        break;
    case 0x3B:
        bb = o->f5058;
        r = insect_InsectFormationGetRow_4efdc0(bb, insect_InsectTeamGetFormation_5138c0(e));
        for (j = 0; j < 5; j++) {
            p = insect_InsectTeamGetPiece_5138d0(e, j);
            if (p != 0) {
                insect_InsectFormationDecodeCell_4effa0(r, j, &a, &b, 1);
                v = o->f5DA8;
                if (v != 0 && v != 3) {
                    a = p->f073;
                    gg = D_00480F28;
                    if (gg == 1) {
                        a = 4 - p->f073;
                        p->f074 = ~p->f074 & 1;
                    }
                    b = p->f074 + (1 - gg) * 5;
                }
                insect_InsectBoardPlacePiece_4ef830(t, p, a, b);
                insect_InsectBoardPieceWorldPos_4edad0(t, p, &fx, &fy, &fz);
                insect_InsectPieceSetPos_5159b0(p, fx, fy, fz);
                q = insect_InsectBattleGetPieceModel_50df60(o, p);
                if (q != 0) {
                    insect_InsectBattlePieceSetDesignVisible_50fa80(q, p, 0);
                    insect_InsectPieceSetBaseMotion_5153e0(p, 0, 4, p->f039, 0);
                    q->s15(1.0f);
                    insect_InsectBattlePieceApplyColor_50fa30(q, p);
                }
            }
        }
        insect_InsectBattleSetFlag_50dad0(o, 0xA);
        v = o->f5DA8;
        if (v != 0 && v == 5 && D_00480F28 == 1) {
            D_00480F28 = 0;
            insect_InsectBattleSetStep_50d7a0(o, 0x39, 1, -1);
        } else {
            insect_InsectBattleSetState_50d8c0(o, 0, 1, -1);
        }
        break;
    }
}
