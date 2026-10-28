/* rgp:protos */
#line 1
/* BYTE-IDENTICAL -- insect session 29 (ix29).
 * Closed by DECLARATION ORDER == FIRST-DEFINITION (STATEMENT) ORDER.  The 21
 * bad words were a pure $s0<->$s2 swap in case 0x1B's second loop: retail
 * q=$s2 and the scratch web {aa,h,h2,h3,k}=$s0, ours the reverse, because our
 * declaration order put `k` (5th) ahead of `q` (8th) while retail's order is
 * the order the values are first defined.  ONLY the full permutation matches:
 * every targeted single relocation of `k` was WORSE (37 and 40 bad).
 */
#include "types.h"
/* insect 0x00502F00 -- 1,968 bytes.  The insect_InsectBattleGetStep_50d6a0(o, 0) state
 * dispatch family (header: insect_InsectBattleMenuPieceCmd_501810.c) crossed with the C++ virtual
 * class whose vptr sits at +0x00.  13 `jalr $25` sites, slots
 * 0x140/0x154/0x170/0x17C/0x188/0x1A4/0x1BC/0x1C0 = virtuals
 * #78/#83/#90/#93/#96/#103/#109/#110 (slot = 8 + 4*N).
 *
 * Compare chain tests 0xA, 0x1C, 0x1B, 1 so SOURCE order is the reverse:
 * 1, 0x1B, 0x1C, 0xA -- and the block addresses (502F74, 50300C, 5032F4,
 * 503648) run forwards in that same order.  Case 0x1B FALLS THROUGH into
 * case 0x1C.
 */

class VE {
public:
    VC_VPTR_MEMBER;  
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
    s32 v078() { return VCM0(s32, 0x140); }                 /* slot 0x140 */
      
    
    s32 v083() { return VCM0(s32, 0x154); }                 /* slot 0x154 */
      
      
    s32 v090() { return VCM0(s32, 0x170); }                 /* slot 0x170 */
     
    s32 v093() { return VCM0(s32, 0x17C); }                 /* slot 0x17C */
     
    s32 v096(s32 i) { return VCM(s32, (void *, s32), 0x188, i); }            /* slot 0x188 */
      
      
    s32 v103() { return VCM0(s32, 0x1A4); }                 /* slot 0x1A4 */
      
     
    void v109(s32 a, s32 b, s32 c) { VCM(void, (void *, s32, s32, s32), 0x1BC, a, b, c); } /* slot 0x1BC */
    s32 v110() { return VCM0(s32, 0x1C0); }                 /* slot 0x1C0 */
};

struct Ent {
    u8   pad000[0x10];
    VE  *f010;                  /* +0x10 */
    u8   pad014[0x1E - 0x14];
    s16  f01E;                  /* +0x1E */
    u8   pad020[0x26 - 0x20];
    u8   f026;                  /* +0x26 */
    u8   pad027[0x28 - 0x27];
    u8   f028;                  /* +0x28 */
    u8   pad029[0x43 - 0x29];
    s8   f043;                  /* +0x43 */
    s8   f044;                  /* +0x44 */
    s8   f045;                  /* +0x45 */
    s8   f046[6];               /* +0x46 */
    u8   pad04C[0x50 - 0x4C];
    s16  f050;                  /* +0x50 */
    u8   pad052[0x5C - 0x52];
    s32  f05C;                  /* +0x5C */
};

struct EL2 { u8 pad000[0x994]; };

struct Dlg {
    u8   pad000[0x1C];
    s16  f01C;                  /* +0x1C */
    u8   pad01E[0x24 - 0x1E];
    s8   f024;                  /* +0x24 */
};

struct Ins {
    u8   pad000[0x35F8];
    EL2  arr[2];                    /* +0x35F8, stride 0x994 */
    u8   pad4920[0x4F90 - 0x4920];
    u8   f4F90[0x2C];               /* +0x4F90 */
    u8   f4FBC;                     /* +0x4FBC */
    u8   pad4FBD[0x506C - 0x4FBD];
    u8   f506C[0x5080 - 0x506C];    /* +0x506C */
    u8   f5080[8];                  /* +0x5080 */
    s16  f5088;                     /* +0x5088 */
    s16  f508A;                     /* +0x508A */
    u8   pad508C[0x5098 - 0x508C];
    s16  f5098;                     /* +0x5098 */
    s16  f509A;                     /* +0x509A */
    s16  f509C;                     /* +0x509C */
    u8   pad509E[0x50A2 - 0x509E];
    s16  f50A2;                     /* +0x50A2 */
    s8   f50A4;                     /* +0x50A4 */
    u8   pad50A5[0x5EEC - 0x50A5];
    s8   f5EEC;                     /* +0x5EEC */
    u8   pad5EED[0x5F82 - 0x5EED];
    char f5F82[2];                  /* +0x5F82 */
};

extern "C" void  Sprintf_1343b8(char *d, const char *f, ...);
extern "C" void  InsectRollStatGain_3d11e0(VE *e, s32 a, s32 b);

extern "C" s32   insect_InsectBattleGetStep_50d6a0(Ins *o, s32 k);
extern "C" void  insect_InsectBattleSetStep_50d7a0(Ins *o, s32 a, s32 b, s32 c);
extern "C" void  insect_InsectBattleSetState_50d8c0(Ins *o, s32 a, s32 b, s32 c);
extern "C" s32   insect_InsectBattleTestFlag_50da40(Ins *o, s32 k);
extern "C" s32   insect_InsectStoryCheckMatchBeatenMaybe_510660(s32 a);
extern "C" s32   insect_InsectStoryIsRankCleared_510710(void);
extern "C" void  insect_InsectCursorSetPushPage_511cf0(void *p, s32 a, s32 b);
extern "C" const char *insect_InsectMsgGet_512b70(void *t, s32 k);
extern "C" s32   insect_InsectPieceGetStat_512e20(Ent *q, s32 i, s32 a);
extern "C" s32   insect_InsectPieceTestStatus_513280(Ent *q, s32 k);
extern "C" void  insect_InsectPieceSetStatus_5132d0(Ent *q, s32 k);
extern "C" Ent  *insect_InsectTeamGetPiece_5138d0(EL2 *a, s32 i);
extern "C" s32   insect_InsectPieceIsInPlay_5149e0(Ent *q);
extern "C" s32   insect_InsectBattleLogIsEmpty_51b8b0(void *d);
extern "C" void  insect_InsectBattleLogResetWait_51c0e0(void *d);
extern "C" s32   insect_InsectBattleLogHasUnread_51c0f0(void *d);
extern "C" void  insect_InsectBattleLogSetRect_51c210(void *d, s32 a, s32 b, s32 c, s32 e);
extern "C" void  insect_InsectBattleLogClear_51c2b0(void *d);
extern "C" void  insect_InsectBattleLogPush_51c2f0(void *d, char *s, s32 a, s32 b, s32 c);

extern "C" void insect_InsectBattleFlowExpReward_502f00(Ins *o)
{
    void *t;
    s32   n;
    s32   j;
    EL2  *g;
    s32   i;
    Ent  *p;
    s32   m;
    s32   r;
    EL2  *a;
    Ent  *q;
    VE   *e;
    s32   aa;
    s32   bb;
    s32   h;
    s32   h2;
    s32   h3;
    s32   k;
    Dlg  *d;
    char *bp;
    Dlg  *d2;
    s32   j2;
    Ent  *q2;
    s32   n5;
    char *bpA;
    s32   v;

    t = o->f506C;
    switch (insect_InsectBattleGetStep_50d6a0(o, 0)) {
    case 1:
        insect_InsectBattleLogClear_51c2b0(o->f5080);
        o->f5098 = 9;
        o->f50A2 = 0;
        o->f50A4 = 0;
        o->f509A = 4;
        insect_InsectBattleLogSetRect_51c210(o->f5080, 0, 0, -1, -1);
        o->f5088 = 0x30;
        o->f508A = 0x84;
        o->f509C = 0x1E;
        insect_InsectBattleLogResetWait_51c0e0(o->f5080);
        insect_InsectCursorSetPushPage_511cf0(o->f4F90, 0, 1);
        insect_InsectBattleSetStep_50d7a0(o, 0xA, 0, -1);
        insect_InsectBattleSetState_50d8c0(o, 0x1B, 2, -1);
        break;
    case 0x1B:
        o->f4FBC = o->f4FBC & 0xFD;
        n = 0;
        for (j = 0; j < 2; j++) {
            g = &o->arr[j];
            for (i = 0; i < 5; i++) {
                p = insect_InsectTeamGetPiece_5138d0(g, i);
                if (p != 0 && insect_InsectPieceIsInPlay_5149e0(p) == 0) {
                    n += p->f050;
                }
            }
        }
        m = insect_InsectBattleTestFlag_50da40(o, 0x3F);
        if (insect_InsectStoryIsRankCleared_510710() != 0) {
            n = n >> 1;
        }
        if (m == 0) {
            n = n >> 1;
        }
        r = insect_InsectStoryCheckMatchBeatenMaybe_510660(m);
        a = o->arr;
        for (i = 0; i < 5; i++) {
            q = insect_InsectTeamGetPiece_5138d0(a, i);
            e = q->f010;
            if (e != 0) {
                aa = e->v103();
                bb = e->v110() & 0xFF;
                if (e->v078() == 0) {
                    if (insect_InsectBattleTestFlag_50da40(o, 0x3F) != 0) {
                        InsectRollStatGain_3d11e0(e, n, r);
                    } else {
                        e->v109(n, 0, 0);
                    }
                    if (aa < e->v103()) {
                        insect_InsectPieceSetStatus_5132d0(q, 0x13);
                    }
                    if (bb == 0 && e->v110() != 0) {
                        insect_InsectPieceSetStatus_5132d0(q, 0x14);
                    }
                    h = q->f01E;
                    q->f043 = e->v083() - h;
                    h2 = q->f026;
                    q->f044 = e->v090() - h2;
                    h3 = q->f028;
                    q->f045 = e->v093() - h3;
                    for (k = 0; k < 6; k++) {
                        q->f046[k] = e->v096(k) - insect_InsectPieceGetStat_512e20(q, k, 0);
                    }
                }
            }
        }
        d = (Dlg *)o->f5080;
        if (d != 0) {
            bp = o->f5F82;
            if (n > 0) {
                Sprintf_1343b8(bp, insect_InsectMsgGet_512b70(t, 0x14), n);
            } else {
                Sprintf_1343b8(bp, insect_InsectMsgGet_512b70(t, 0x15));
            }
            insect_InsectBattleLogPush_51c2f0(d, bp, 0, -1, 1);
            d->f024 = 1;
        }
        insect_InsectBattleSetStep_50d7a0(o, 0x1C, 0, -1);
        o->f5EEC = 1;
        /* fallthrough */
    case 0x1C:
        d2 = (Dlg *)o->f5080;
        if (o->f5EEC > 0 && insect_InsectBattleLogHasUnread_51c0f0(d2) == 0) {
            o->f5EEC = 0;
        }
        if (o->f5EEC <= 0) {
            o->f5EEC = 0;
            if (d2 != 0) {
                d2->f024 = 0;
                d2->f01C = 0;
                insect_InsectBattleLogResetWait_51c0e0(d2);
                a = o->arr;
                for (j2 = 0; j2 < 5; j2++) {
                    q2 = insect_InsectTeamGetPiece_5138d0(a, j2);
                    if (q2 != 0) {
                        e = q2->f010;
                        if (e != 0) {
                            if (e->v078() != 0) {
                                bp = o->f5F82;
                                Sprintf_1343b8(bp, insect_InsectMsgGet_512b70(t, 0x50), q2->f05C);
                                insect_InsectBattleLogPush_51c2f0(d2, bp, 5, -1, 1);
                            } else {
                                if (insect_InsectPieceTestStatus_513280(q2, 0x13) != 0) {
                                    n5 = q2->f05C;
                                    bp = o->f5F82;
                                    Sprintf_1343b8(bp, insect_InsectMsgGet_512b70(t, 0x1C), n5, e->v103());
                                    insect_InsectBattleLogPush_51c2f0(d2, bp, 5, 0xB, 1);
                                }
                                if (insect_InsectBattleTestFlag_50da40(o, 0x3F) != 0 && insect_InsectPieceTestStatus_513280(q2, 0x13) == 0) {
                                    bp = o->f5F82;
                                    Sprintf_1343b8(bp, insect_InsectMsgGet_512b70(t, 0x1D), q2->f05C);
                                    insect_InsectBattleLogPush_51c2f0(d2, bp, 5, 0xB, 1);
                                }
                                if (e->v110() != 0 && insect_InsectPieceTestStatus_513280(q2, 0x14) != 0) {
                                    bp = o->f5F82;
                                    Sprintf_1343b8(bp, insect_InsectMsgGet_512b70(t, 0x51), q2->f05C);
                                    insect_InsectBattleLogPush_51c2f0(d2, bp, 5, 0xB, 1);
                                }
                                v = (s8)q2->f043;
                                if (v != 0) {
                                    bpA = o->f5F82;
                                    Sprintf_1343b8(bpA, insect_InsectMsgGet_512b70(t, 0x1E), q2->f05C, v);
                                    insect_InsectBattleLogPush_51c2f0(d2, bpA, 5, -1, 1);
                                }
                                v = (s8)q2->f044;
                                if (v > 0) {
                                    bp = o->f5F82;
                                    Sprintf_1343b8(bp, insect_InsectMsgGet_512b70(t, 0x1F), q2->f05C, v);
                                    insect_InsectBattleLogPush_51c2f0(d2, bp, 5, -1, 1);
                                }
                                v = (s8)q2->f045;
                                if (v > 0) {
                                    bp = o->f5F82;
                                    Sprintf_1343b8(bp, insect_InsectMsgGet_512b70(t, 0x20), q2->f05C, v);
                                    insect_InsectBattleLogPush_51c2f0(d2, bp, 5, -1, 1);
                                }
                                for (i = 0; i < 6; i++) {
                                    v = (s8)q2->f046[i];
                                    if (v > 0) {
                                        bp = o->f5F82;
                                        Sprintf_1343b8(bp, insect_InsectMsgGet_512b70(t, i + 0x21), q2->f05C, v);
                                        insect_InsectBattleLogPush_51c2f0(d2, bp, 5, -1, 1);
                                    }
                                }
                            }
                        }
                    }
                }
            }
            insect_InsectBattleSetStep_50d7a0(o, 0xA, 0, -1);
        }
        break;
    case 0xA:
        if (((unsigned char)insect_InsectBattleLogIsEmpty_51b8b0(o->f5080)) != 0) {
            insect_InsectBattleSetStep_50d7a0(o, 0xB, 0, -1);
            insect_InsectBattleSetStep_50d7a0(o, 0x1D, 2, -1);
        }
        break;
    }
}
