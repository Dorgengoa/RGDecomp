#include "types.h"
/* insect 0x0050A9F0 -- 3,048 bytes, 762 instructions, 123 calls, 41 conditional
 * branches, br/ins 0.054.  A member of the insect_InsectBattleGetStep_50d6a0(o, k) state
 * dispatch family whose header is insect_InsectBattleMenuTeamSelect_5004f0.c -- read that prototype
 * block first, most of this API comes from it.  Found by x_band.py (THRESHOLD,
 * then size); the divide-trap screen is clean here.
 *
 * TWO dispatch levels and they are spelled differently:
 *
 *   - the OUTER switch on insect_InsectBattleGetState_50d6f0(o, 4) is a real jump table
 *     (jtbl_00524F60, ten entries, sltiu 0xA with NO bias) so the case set
 *     spans 0..9 and cases 0, 5, 6, 7 and 9 are EMPTY CASES pointing at the
 *     shared exit.  Their presence is what makes the set dense enough for a
 *     table at all, and the block layout is ASCENDING case order = source order.
 *   - each INNER switch is a compare CHAIN, so its cases test in REVERSED
 *     source order.  Read off the reference: 0x1B/6/1 -> source 1, 6, 0x1B;
 *     0xB/0xA/1 -> 1, 0xA, 0xB; 0xB/0x1C/9/0x15/0x12/0xA/1 -> 1, 0xA, 0x12,
 *     0x15, 9, 0x1C, 0xB; 6/9/1 -> 1, 9, 6.  In every one the block ADDRESSES
 *     run in that same reversed order forwards, which is the cross-check.
 *
 * Three fall-throughs are real: 0x12 -> 0x15 -> 9 in the case-3 chain and
 * 1 -> 9 in the case-4 chain.  Case 0x12 guards only its own body -- the
 * r == 0 path still falls into 0x15.
 *
 * "case 0xB: break;" is in the source twice and carries a PLAIN beq + nop
 * rather than the branch-likely the other guards get, because the merge block
 * first instruction is the argument copy the exit needs either way.
 *
 * The -1 that case 6 of the case-4 chain hands to n, and the one func_290010
 * takes as its last argument, are both the initialiser still live in $20; an
 * argument with no instruction of its own is not a missing instruction.
 *
 * D_00484F98 / D_00484F9C are MAIN-image small data (the gp window is
 * 0x47D170..0x48D170) and must stay non-const to keep %gp_rel.  The overlay
 * own D_005..... data must be const to get %hi/%lo.
 */

typedef struct Ins {
    u8    pad000[0x138];
    u8    f138[0x87C - 0x138];  /* +0x0138 */
    void *f87C;                 /* +0x087C */
    void *f880;                 /* +0x0880 */
    u8    pad884[0x4F90 - 0x884];
    u8    f4F90[0x2C];          /* +0x4F90 */
    u8    f4FBC;                /* +0x4FBC */
    u8    pad4FBD[0x5000 - 0x4FBD];
    u8    f5000[0x54];          /* +0x5000 */
    u8    f5054[0x18];          /* +0x5054 */
    u8    f506C[0x4];           /* +0x506C */
    u8    f5070[0x4];           /* +0x5070 */
    void *f5074;                /* +0x5074 */
    u8    pad5078[0x5D9C - 0x5078];
    f32   f5D9C;                /* +0x5D9C */
    s32   f5DA0;                /* +0x5DA0 */
    s32   f5DA4;                /* +0x5DA4 */
    u8    pad5DA8[0x5EF1 - 0x5DA8];
    u8    f5EF1;                /* +0x5EF1 */
    u8    pad5EF2[0x5F02 - 0x5EF2];
    u8    f5F02[1];             /* +0x5F02 */
} Ins;

typedef struct Rec {
    u8    pad00[0x4];
    s16   f04;                  /* +0x04 */
    u8    pad06[0x2];
    void *f08;                  /* +0x08 */
    void *f0C;                  /* +0x0C */
} Rec;

typedef struct Card { u8 pad00[0xB]; s8 fB; } Card;

extern s32 D_00484F98;
extern s32 D_00484F9C;

extern const u8   D_00523D00[];
extern const char D_00524CD8[];
extern const char D_00524F38[];
extern const char D_00524F40[];
extern const char D_00524F50[];

extern s32   insect_InsectBattleGetStep_50d6a0(Ins *o, s32 k);
extern s32   insect_InsectBattleGetState_50d6f0(Ins *o, s32 k);
extern void  insect_InsectBattleSetStep_50d7a0(Ins *o, s32 a, s32 b, s32 c);
extern void  insect_InsectBattleSetState_50d8c0(Ins *o, s32 a, s32 b, s32 c);
extern s32   insect_InsectBattleTestFlag_50da40(Ins *o, s32 k);
extern void  insect_InsectBattleClearFlag_50da90(Ins *o, s32 k);
extern void  insect_InsectBattleSetFlag_50dad0(Ins *o, s32 k);
extern void  insect_InsectBattleCursorUpdateDesc_4f4530(Ins *o, const u8 *t, s32 k);
extern void  insect_InsectBattlePlaySe_4f45b0(Ins *o, s32 k);
extern void  insect_InsectHelpParseScript_510b30(void *a, s32 b, s32 c);
extern s32   insect_InsectHelpGetEntryTitle_510ba0(void *a, s32 i);
extern Rec  *insect_InsectHelpGetEntry_510c00(void *a, s32 i);
extern s32   insect_InsectHelpGetCount_510cb0(void *a);
extern void  insect_InsectHelpInit_510da0(void *a);
extern s64   insect_InsectCursorSetGetEvents_5119f0(void *a, s32 mask);
extern void  insect_InsectCursorSetGetCell_511a40(void *a, s32 k, s32 *x, s32 *y);
extern void  insect_InsectCursorSetSetScrollMax_511b30(void *a, s32 k, s32 v);
extern void  insect_InsectCursorSetSetSize_511bd0(void *a, s32 k, s32 v);
extern void  insect_InsectCursorSetPopPage_511ca0(void *a);
extern void  insect_InsectCursorSetPushPage_511cf0(void *a, s32 k, s32 v);
extern Card *insect_InsectCursorSetGetCurPage_511e20(void *a);
extern void *insect_InsectFileSlotGetData_511fa0(void *a, s32 *n);
extern s32   insect_InsectFileSlotIsLoaded_512010(void *a);
extern void  insect_InsectFileSlotRelease_512020(void *a);
extern void  insect_InsectFileSlotRequest_512140(void *a, const void *t, s32 k);
extern s32   insect_InsectMsgCenterX_512b10(void *a, s32 b, s32 c);
extern s32   insect_InsectMsgGet_512b70(void *a, s32 b);

extern void  func_1319A8(void *d, void *s, s32 n);
extern void  func_1343B8();
extern void  func_134A98(void *a, const char *t);
extern u32   func_134BB0(const char *t);
extern void  func_14D810(void *a, void *b, s32 n);
extern void  func_14D830(void *a);
extern void *func_14D950(void *a, s32 n);
extern void  func_14DAD0(void *a);
extern s32   func_14DB10(void *a, s32 b, s32 c, s32 d);
extern void  func_14DCB0(void *a, s32 b);
extern void  func_14DE90(void *a);
extern void  func_14DFF0(void *a);
extern void *func_14E030(void *a);
extern void *func_14E230(s32 n, void *a);
extern void  func_158AC0(s32 h, s32 id);
extern void  func_158C40(s32 h, const void *s, s32 id);
extern void  func_1594D0(s32 h, void *a, s32 id, void *b, s32 c);
extern s32   func_15DE40(void);
extern s32   func_1C2800(void *a, const char *t, s32 *n);
extern void  func_28F510(void *h, s32 id, s32 a, s32 b);
extern void  func_28F5D0(void *h, s32 id, s32 a, s32 b, s32 c);
extern void  func_290010(void *h, s32 id, s32 a, s32 b);
extern void *func_290460(void *h, s32 id);
extern void  func_290690(void *h, s32 id, f32 a, f32 b, f32 c);
extern f32   func_290770(void *h, s32 id);
extern void  func_2907A0(void *h, s32 id, f32 v);
extern s32   func_290D30(void *h, s32 id);
extern void  func_290F50(void *h, s32 id, s32 a, s32 b, s32 c, f32 t);
extern void  func_290F60(void *h, s32 id, s32 a, s32 b);
extern f32   func_392E60(void *g, void *w, s32 a, s32 b, s32 c);
extern void  func_3930D0(void *g, void *w, s32 a, s32 b, s32 c);
extern void  func_3934D0(void *g, void *w, s32 a, s32 b, s32 c, s32 d);
extern void  func_3939E0(void *g, void *w, s32 a, s32 b, f32 c, f32 d);

void insect_InsectBattleHelpStep_50a9f0(Ins *o)
{
    s32 xBC;
    s32 xB8;
    s32 xB4;
    s32 xB0;
    s32 xAC;
    s32 xA8;
    u8 buf[0x28];
    void *g;
    void *p19;
    void *v2;
    void *p2;
    void *p;
    void *q;
    void *v;
    void *w;
    Rec *r;
    u8 *s;
    s32 h;
    s32 i;
    s32 n;
    s32 k;
    s32 a;
    s32 b;
    s32 c;
    f32 t;

    c = b = a = -1;
    g = o->f5054;
    p19 = o->f506C;

    switch (insect_InsectBattleGetState_50d6f0(o, 4)) {
    case 0:
        break;
    case 1:
        switch (insect_InsectBattleGetStep_50d6a0(o, 4)) {
        case 1:
            D_00484F9C = 0;
            insect_InsectHelpInit_510da0(o->f5070);
            p = o->f138;
            func_14DE90(p);
            func_14DB10(p, 2, 0, 0x40);
            v = func_14E230(0x58, p);
            if (v != 0) {
                v = func_14E030(v);
            }
            func_14DAD0(p);
            func_14DB10(p, 2, 0, 0x40);
            func_14DFF0(v);
            func_14D810(v, func_14D950(p, 0x280), 0x280);
            if (func_134BB0(D_00524F38) < 0x10) {
                func_134A98(v, D_00524F38);
            }
            func_14D830(v);
            func_14DAD0(p);
            o->f5074 = v;
            insect_InsectFileSlotRequest_512140(o->f5000, D_00524CD8, 0);
            b = 6;
            break;
        case 6:
            if (insect_InsectFileSlotIsLoaded_512010(o->f5000) != 0) {
                insect_InsectHelpParseScript_510b30(o->f5070,
                                    func_1C2800(insect_InsectFileSlotGetData_511fa0(o->f5000, &xBC),
                                                D_00524F40, &xBC),
                                    xBC);
                insect_InsectFileSlotRelease_512020(o->f5000);
                b = 0x1B;
            }
            break;
        case 0x1B:
            n = insect_InsectHelpGetCount_510cb0(o->f5070) - 8;
            if (n <= 0) {
                n = 0;
            }
            insect_InsectCursorSetPushPage_511cf0(o->f4F90, 0xE, 1);
            insect_InsectCursorSetSetSize_511bd0(o->f4F90, 1, 8);
            insect_InsectCursorSetSetScrollMax_511b30(o->f4F90, 0, n);
            a = 2;
            break;
        }
        break;
    case 2:
        k = insect_InsectCursorSetGetCurPage_511e20(o->f4F90)->fB;
        switch (insect_InsectBattleGetStep_50d6a0(o, 4)) {
        case 1:
            o->f4FBC = o->f4FBC & 0xFD;
            insect_InsectBattleSetFlag_50dad0(o, 0x2C);
            func_3930D0(g, func_290460(o->f880, 0x75FC), 0x120, 0x106, 0);
            func_3934D0(g, func_290460(o->f880, 0x75F9), 0x11C, 0x102, 1, o->f5EF1);
            func_3939E0(g, func_290460(o->f880, 0x75FB), 8, 0, 284.0f, 28.0f);
            func_3934D0(g, func_290460(o->f880, 0x75FA), 0x11C, 0x1C, 5, o->f5EF1);
            w = func_290460(o->f880, 0x75FE);
            o->f5D9C = func_392E60(g, w, 0xE2, 8,
                                   insect_InsectHelpGetCount_510cb0(o->f5070));
            func_290010(o->f880, 0x75F8, 1, -1);
            func_2907A0(o->f880, 0x75F8, 0.0f);
            func_290690(o->f880, 0x75F8, 1.0f, 0.125f, -1.0f);
            func_290F60(o->f880, 0x75FC, (o->f5DA0 - 0x120) >> 1,
                        (o->f5DA4 - 0x106) >> 1);
            func_290F60(o->f880, 0x75F9, 4, 4);
            func_290F60(o->f880, 0x75FA, 4, 4);
            func_290F60(o->f880, 0x75FB, 4, 0x1E);
            func_290F60(o->f880, 0x75FD, 0x114, 0x20);
            func_290F60(o->f880, 0x7600, (o->f5DA0 - 0x100) / 2,
                        o->f5DA4 / 2 + 0x9A);
            insect_InsectBattleCursorUpdateDesc_4f4530(o, D_00523D00, 1);
            func_290690(o->f87C, 0xC37E, 1.0f, 0.125f, -1.0f);
            func_2907A0(o->f880, 0x75FF, 0.0f);
            insect_InsectBattleSetFlag_50dad0(o, 0x19);
            i = 0;
            do {
                func_28F510(o->f880, 0x75FB,
                            insect_InsectHelpGetEntryTitle_510ba0(o->f5070, i + k), i);
                func_28F5D0(o->f880, 0x75FB, 6, i * 0x1C + 8, i);
                i++;
            } while (i < 8);
            func_28F510(o->f880, 0x75FC, insect_InsectMsgGet_512b70(p19, 0xE), 0);
            func_28F5D0(o->f880, 0x75FC,
                        insect_InsectMsgCenterX_512b10(p19, 0xE, 0x120), 0xA, 0);
            b = 0xA;
            break;
        case 0xA:
            insect_InsectBattleCursorUpdateDesc_4f4530(o, D_00523D00, 0);
            func_290F50(o->f880, 0x75FE, 0, (s32)((f32)k * o->f5D9C), 0, 0.5f);
            i = 0;
            do {
                func_28F510(o->f880, 0x75FB,
                            insect_InsectHelpGetEntryTitle_510ba0(o->f5070, i + k), i);
                func_28F5D0(o->f880, 0x75FB, 6, i * 0x1C + 8, i);
                i++;
            } while (i < 8);
            n = insect_InsectCursorSetGetEvents_5119f0(o->f4F90, -1);
            if (n & 0x20) {
                insect_InsectCursorSetPopPage_511ca0(o->f4F90);
                a = 8;
                c = 6;
            } else if (n & 0x80) {
                D_00484F98 = 0;
                insect_InsectCursorSetPushPage_511cf0(o->f4F90, 0, 0);
                a = 3;
                c = 5;
            }
            break;
        case 0xB:
            break;
        }
        break;
    case 3:
        insect_InsectCursorSetGetCell_511a40(o->f4F90, 0xE, &xB8, &xB4);
        switch (insect_InsectBattleGetStep_50d6a0(o, 4)) {
        case 1:
            r = insect_InsectHelpGetEntry_510c00(o->f5070, xB4);
            if (r != 0) {
                func_1343B8(buf, r->f08, D_00484F98);
                insect_InsectFileSlotRequest_512140(o->f5000, buf, 5);
                b = 0xA;
            }
            break;
        case 0xA:
            if (insect_InsectFileSlotIsLoaded_512010(o->f5000) != 0) {
                v2 = insect_InsectFileSlotGetData_511fa0(o->f5000, &xB0);
                p2 = o->f138;
                D_00484F9C = func_14DB10(p2, 2, 0, 0x40);
                q = func_14D950(p2, xB0 >> 4);
                func_1319A8(q, v2, xB0);
                func_14DAD0(p2);
                func_1594D0(func_15DE40(), q, 0x29D, p2, 0);
                insect_InsectFileSlotRelease_512020(o->f5000);
                b = 0x12;
            }
            break;
        case 0x12:
            w = func_290460(o->f880, 0x75FF);
            r = insect_InsectHelpGetEntry_510c00(o->f5070, xB4);
            if (r != 0) {
                s = o->f5F02;
                func_1343B8(s, r->f0C, D_00484F98);
                if (w != 0) {
                    func_1343B8((u8 *)w + 4, D_00524F50, s);
                }
                func_290F60(o->f880, 0x75FF, o->f5DA0, 0);
                func_290F50(o->f880, 0x75FF, 0, 0, 0, 0.5f);
                func_2907A0(o->f880, 0x75FF, 0.0f);
                func_290690(o->f880, 0x75FF, 1.0f, 0.125f, -1.0f);
                func_290690(o->f880, 0x75FC, 0.0f, 0.125f, -1.0f);
                func_290690(o->f87C, 0xC37E, 0.0f, 0.125f, -1.0f);
                c = 0xB;
            }
            /* fallthrough */
        case 0x15:
            func_290010(o->f880, 0x75FF, 1, -1);
            func_2907A0(o->f880, 0x7600, 1.0f);
            b = 9;
            o->f4FBC = o->f4FBC & 0xFD;
            /* fallthrough */
        case 9:
            if (func_290D30(o->f880, 0x75FF) == 0) {
                b = 0x1C;
            }
            break;
        case 0x1C:
            t = func_290770(o->f880, 0x7600);
            if (t <= 0.0f) {
                func_290690(o->f880, 0x7600, 1.0f, 0.0625f, -1.0f);
            } else if (t >= 1.0f) {
                func_290690(o->f880, 0x7600, 0.0f, 0.0625f, -1.0f);
            }
            if (insect_InsectCursorSetGetEvents_5119f0(o->f4F90, 0x80) != 0) {
                a = 4;
                c = 5;
            } else if (insect_InsectCursorSetGetEvents_5119f0(o->f4F90, 0x20) != 0) {
                insect_InsectBattleSetFlag_50dad0(o, 0x13);
                a = 4;
                c = 6;
            }
            break;
        case 0xB:
            break;
        }
        break;
    case 4:
        insect_InsectCursorSetGetCell_511a40(o->f4F90, 0xE, &xAC, &xA8);
        switch (insect_InsectBattleGetStep_50d6a0(o, 4)) {
        case 1:
            func_290F50(o->f880, 0x75FF, o->f5DA0, 0, 0, 0.5f);
            b = 9;
            /* fallthrough */
        case 9:
            if (func_290D30(o->f880, 0x75FF) == 0) {
                b = 6;
            }
            break;
        case 6:
            p = o->f138;
            s = o->f5F02;
            r = insect_InsectHelpGetEntry_510c00(o->f5070, xA8);
            if (r != 0) {
                func_1343B8(s, D_00524F50, r->f08, D_00484F98);
                h = func_15DE40();
                func_158C40(h, s, 0x29D);
                func_158AC0(h, 0x29D);
                func_14DCB0(p, D_00484F9C);
                D_00484F9C = 0;
                D_00484F98 = D_00484F98 + 1;
                r = insect_InsectHelpGetEntry_510c00(o->f5070, xA8);
                if (r != 0) {
                    n = r->f04;
                    if (insect_InsectBattleTestFlag_50da40(o, 0x13) != 0) {
                        n = -1;
                    }
                    insect_InsectBattleClearFlag_50da90(o, 0x13);
                    if (D_00484F98 >= n) {
                        a = 2;
                        b = 0xA;
                        func_290690(o->f87C, 0xC37E, 1.0f, 0.125f, -1.0f);
                        func_290690(o->f880, 0x75FC, 1.0f, 0.125f, -1.0f);
                        insect_InsectCursorSetPopPage_511ca0(o->f4F90);
                    } else {
                        a = 3;
                    }
                }
            }
            break;
        }
        break;
    case 5:
    case 6:
    case 7:
        break;
    case 8:
        func_290690(o->f880, 0x75F8, 0.0f, 0.125f, -1.0f);
        insect_InsectBattleClearFlag_50da90(o, 0x2B);
        insect_InsectBattleClearFlag_50da90(o, 0x2C);
        a = 0;
        break;
    case 9:
        break;
    }
    insect_InsectBattleSetState_50d8c0(o, a, 4, -1);
    insect_InsectBattleSetStep_50d7a0(o, b, 4, -1);
    insect_InsectBattlePlaySe_4f45b0(o, c);
}
