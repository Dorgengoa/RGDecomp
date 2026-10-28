/* rgp:protos */
#define RGP_SELF_insect_InsectBattleHelpStep_50a9f0 1
#include "port/game_protos.h"
#line 1
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
 *     (insect_jtbl_00524F60, ten entries, sltiu 0xA with NO bias) so the case set
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

extern u8   insect_D_00523D00[];
extern char insect_D_00524CD8[];
extern char insect_D_00524F38[];
extern char insect_D_00524F40[];
extern char insect_D_00524F50[];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

extern void  memcpy(void *d, void *s, s32 n);
extern void  Sprintf_1343b8();
extern void  strcpy(void *a, const char *t);
extern u32   strlen(const char *t);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectBattleHelpStep_50a9f0(Ins *o)
{
    s32 xBC;
    s32 xB8;
    s32 xB4;
    s32 xB0;
    s32 xAC;
    s32 xA8;
    u8 buf[0x28] __attribute__((aligned(16)));
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
            MemStackHeapReinit_14de90(p);
            MemStackHeapAlloc_14db10(p, 2, 0, 0x40);
            v = MemStackNew_14e230(0x58, p);
            if (v != 0) {
                v = MemStackCtor_14e030(v);
            }
            MemStackReturnToOwnerMaybe_14dad0(p);
            MemStackHeapAlloc_14db10(p, 2, 0, 0x40);
            MemStackClear_14dff0(v);
            MemStackInit_14d810(v, MemStackAllocQw_14d950(p, 0x280), 0x280);
            if (strlen(insect_D_00524F38) < 0x10) {
                strcpy(v, insect_D_00524F38);
            }
            MemStackReset_14d830(v);
            MemStackReturnToOwnerMaybe_14dad0(p);
            o->f5074 = v;
            insect_InsectFileSlotRequest_512140(o->f5000, insect_D_00524CD8, 0);
            b = 6;
            break;
        case 6:
            if (insect_InsectFileSlotIsLoaded_512010(o->f5000) != 0) {
                ({ __typeof__(((s32)ArchiveGetFileByPath_1c2800(insect_InsectFileSlotGetData_511fa0(o->f5000, &xBC),
                                                insect_D_00524F40, &xBC))) rgp_ao0 = ((s32)ArchiveGetFileByPath_1c2800(insect_InsectFileSlotGetData_511fa0(o->f5000, &xBC),
                                                insect_D_00524F40, &xBC)); insect_InsectHelpParseScript_510b30(o->f5070,rgp_ao0,
                                    xBC); });
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
        k = ((Card *)insect_InsectCursorSetGetCurPage_511e20(o->f4F90))->fB;
        switch (insect_InsectBattleGetStep_50d6a0(o, 4)) {
        case 1:
            o->f4FBC = o->f4FBC & 0xFD;
            insect_InsectBattleSetFlag_50dad0(o, 0x2C);
            func_3930D0(g, UiFindWidget_290460(o->f880, 0x75FC), 0x120, 0x106, 0);
            UiQuadSetByModeRelated_3934d0(g, UiFindWidget_290460(o->f880, 0x75F9), 0x11C, 0x102, 1, o->f5EF1);
            UiSpriteListFillColumnMaybe_3939e0(g, UiFindWidget_290460(o->f880, 0x75FB), 8, 0, 284.0f, 28.0f);
            UiQuadSetByModeRelated_3934d0(g, UiFindWidget_290460(o->f880, 0x75FA), 0x11C, 0x1C, 5, o->f5EF1);
            w = UiFindWidget_290460(o->f880, 0x75FE);
            o->f5D9C = UiScrollBarSpritesLayoutMaybe_392e60(g, w, 0xE2, 8,
                                   insect_InsectHelpGetCount_510cb0(o->f5070));
            UiSetWidgetVisible_290010(o->f880, 0x75F8, 1, -1);
            UiSetWidgetAlpha_2907a0(o->f880, 0x75F8, 0.0f);
            UiFadeWidgetAlpha_290690(o->f880, 0x75F8, 1.0f, 0.125f, -1.0f);
            UiSetWidgetPos_290f60(o->f880, 0x75FC, (o->f5DA0 - 0x120) >> 1,
                        (o->f5DA4 - 0x106) >> 1);
            UiSetWidgetPos_290f60(o->f880, 0x75F9, 4, 4);
            UiSetWidgetPos_290f60(o->f880, 0x75FA, 4, 4);
            UiSetWidgetPos_290f60(o->f880, 0x75FB, 4, 0x1E);
            UiSetWidgetPos_290f60(o->f880, 0x75FD, 0x114, 0x20);
            UiSetWidgetPos_290f60(o->f880, 0x7600, (o->f5DA0 - 0x100) / 2,
                        o->f5DA4 / 2 + 0x9A);
            insect_InsectBattleCursorUpdateDesc_4f4530(o, insect_D_00523D00, 1);
            UiFadeWidgetAlpha_290690(o->f87C, 0xC37E, 1.0f, 0.125f, -1.0f);
            UiSetWidgetAlpha_2907a0(o->f880, 0x75FF, 0.0f);
            insect_InsectBattleSetFlag_50dad0(o, 0x19);
            i = 0;
            do {
                UiSetTextString_28f510(o->f880, 0x75FB,
                            insect_InsectHelpGetEntryTitle_510ba0(o->f5070, i + k), i);
                UiSetTextPos_28f5d0(o->f880, 0x75FB, 6, i * 0x1C + 8, i);
                i++;
            } while (i < 8);
            UiSetTextString_28f510(o->f880, 0x75FC, ((s32)insect_InsectMsgGet_512b70(p19, 0xE)), 0);
            UiSetTextPos_28f5d0(o->f880, 0x75FC,
                        insect_InsectMsgCenterX_512b10(p19, 0xE, 0x120), 0xA, 0);
            b = 0xA;
            break;
        case 0xA:
            insect_InsectBattleCursorUpdateDesc_4f4530(o, insect_D_00523D00, 0);
            UiMoveWidgetUniform_290f50(o->f880, 0x75FE, 0, (s32)((f32)k * o->f5D9C), 0.5f, 0);
            i = 0;
            do {
                UiSetTextString_28f510(o->f880, 0x75FB,
                            insect_InsectHelpGetEntryTitle_510ba0(o->f5070, i + k), i);
                UiSetTextPos_28f5d0(o->f880, 0x75FB, 6, i * 0x1C + 8, i);
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
            r = ((Rec *)insect_InsectHelpGetEntry_510c00(o->f5070, xB4));
            if (r != 0) {
                Sprintf_1343b8(buf, r->f08, D_00484F98);
                insect_InsectFileSlotRequest_512140(o->f5000, buf, 5);
                b = 0xA;
            }
            break;
        case 0xA:
            if (insect_InsectFileSlotIsLoaded_512010(o->f5000) != 0) {
                v2 = insect_InsectFileSlotGetData_511fa0(o->f5000, &xB0);
                p2 = o->f138;
                D_00484F9C = ((s32)MemStackHeapAlloc_14db10(p2, 2, 0, 0x40));
                q = MemStackAllocQw_14d950(p2, xB0 >> 4);
                memcpy(q, v2, xB0);
                MemStackReturnToOwnerMaybe_14dad0(p2);
                NameTableRegisterImArchive_1594d0(GetDrawCtxNameTable_15de40(), q, 0x29D, p2, 0);
                insect_InsectFileSlotRelease_512020(o->f5000);
                b = 0x12;
            }
            break;
        case 0x12:
            w = UiFindWidget_290460(o->f880, 0x75FF);
            r = ((Rec *)insect_InsectHelpGetEntry_510c00(o->f5070, xB4));
            if (r != 0) {
                s = o->f5F02;
                Sprintf_1343b8(s, r->f0C, D_00484F98);
                if (w != 0) {
                    Sprintf_1343b8((u8 *)w + 4, insect_D_00524F50, s);
                }
                UiSetWidgetPos_290f60(o->f880, 0x75FF, o->f5DA0, 0);
                UiMoveWidgetUniform_290f50(o->f880, 0x75FF, 0, 0, 0.5f, 0);
                UiSetWidgetAlpha_2907a0(o->f880, 0x75FF, 0.0f);
                UiFadeWidgetAlpha_290690(o->f880, 0x75FF, 1.0f, 0.125f, -1.0f);
                UiFadeWidgetAlpha_290690(o->f880, 0x75FC, 0.0f, 0.125f, -1.0f);
                UiFadeWidgetAlpha_290690(o->f87C, 0xC37E, 0.0f, 0.125f, -1.0f);
                c = 0xB;
            }
            /* fallthrough */
        case 0x15:
            UiSetWidgetVisible_290010(o->f880, 0x75FF, 1, -1);
            UiSetWidgetAlpha_2907a0(o->f880, 0x7600, 1.0f);
            b = 9;
            o->f4FBC = o->f4FBC & 0xFD;
            /* fallthrough */
        case 9:
            if (UiWidgetIsMoving_290d30(o->f880, 0x75FF) == 0) {
                b = 0x1C;
            }
            break;
        case 0x1C:
            t = UiGetWidgetAlpha_290770(o->f880, 0x7600);
            if (t <= 0.0f) {
                UiFadeWidgetAlpha_290690(o->f880, 0x7600, 1.0f, 0.0625f, -1.0f);
            } else if (t >= 1.0f) {
                UiFadeWidgetAlpha_290690(o->f880, 0x7600, 0.0f, 0.0625f, -1.0f);
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
            UiMoveWidgetUniform_290f50(o->f880, 0x75FF, o->f5DA0, 0, 0.5f, 0);
            b = 9;
            /* fallthrough */
        case 9:
            if (UiWidgetIsMoving_290d30(o->f880, 0x75FF) == 0) {
                b = 6;
            }
            break;
        case 6:
            p = o->f138;
            s = o->f5F02;
            r = ((Rec *)insect_InsectHelpGetEntry_510c00(o->f5070, xA8));
            if (r != 0) {
                Sprintf_1343b8(s, insect_D_00524F50, r->f08, D_00484F98);
                h = GetDrawCtxNameTable_15de40();
                NameTableRemoveByName_158c40(h, s, 0x29D);
                NameTableFreeGroup_158ac0(h, 0x29D);
                MemStackHeapFree_14dcb0(p, D_00484F9C);
                D_00484F9C = 0;
                D_00484F98 = D_00484F98 + 1;
                r = ((Rec *)insect_InsectHelpGetEntry_510c00(o->f5070, xA8));
                if (r != 0) {
                    n = r->f04;
                    if (insect_InsectBattleTestFlag_50da40(o, 0x13) != 0) {
                        n = -1;
                    }
                    insect_InsectBattleClearFlag_50da90(o, 0x13);
                    if (D_00484F98 >= n) {
                        a = 2;
                        b = 0xA;
                        UiFadeWidgetAlpha_290690(o->f87C, 0xC37E, 1.0f, 0.125f, -1.0f);
                        UiFadeWidgetAlpha_290690(o->f880, 0x75FC, 1.0f, 0.125f, -1.0f);
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
        UiFadeWidgetAlpha_290690(o->f880, 0x75F8, 0.0f, 0.125f, -1.0f);
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
