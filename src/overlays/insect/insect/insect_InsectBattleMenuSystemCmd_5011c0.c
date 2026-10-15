#include "types.h"
/* insect 0x005011C0 -- 780 bytes, 195 instructions, 30 calls, 7 conditional
 * branches, br/ins 0.036.  Third member of the insect_InsectBattleMenuPieceCmd_501810 /
 * insect_FUN_005014D0 triple: same family, same 004efc80/004efc10 list build,
 * same five-case chain 0xB, 0x20, 0x1C, 0x1D, 1 -> source order
 * 1, 0x1D, 0x1C, 0x20, 0xB (blocks 501230, 501340, 5013AC, 5013C4, 50147C).
 *
 * The leading insect_InsectCursorSetFindPage_511e60(o->f4F90, 2) has its RESULT DISCARDED --
 * there is no NULL guard and no use of $2 -- so it is a statement, not the
 * initialiser of a local.  The other two members of the triple do guard on it.
 *
 * o->f502C and o->f4F90 are array members (insect-array-member-blocks-cse).
 */

typedef struct Ins {
    u8    pad000[0x878];
    void *f878;                 /* +0x0878 */
    void *f87C;                 /* +0x087C */
    u8    pad880[0x4F90 - 0x880];
    u8    f4F90[0x2C];          /* +0x4F90 */
    u8    f4FBC;                /* +0x4FBC */
    u8    pad4FBD[0x502C - 0x4FBD];
    u8    f502C[4];             /* +0x502C */
} Ins;

extern const u8 D_00523DE0[];

extern s32   insect_InsectCmdMenuCount_4efc10(void *a);
extern void  insect_InsectCmdMenuAdd_4efc80(void *a, s32 k);
extern void  insect_InsectCmdMenuClear_4efd40(void *a);
extern void  insect_InsectCmdMenuEntryRefresh_4f0060(Ins *o, s32 i, void *p);
extern void  insect_InsectBattleCursorUpdateDesc_4f4530(Ins *o, const u8 *t, s32 k);
extern void  insect_InsectCmdMenuLayout_4fab80(Ins *o, s32 a, s32 b, s32 c);
extern s32   insect_InsectBattleGetStep_50d6a0(Ins *o, s32 k);
extern void  insect_InsectBattleSetStep_50d7a0(Ins *o, s32 a, s32 b, s32 c);
extern void  insect_InsectBattleSetState_50d8c0(Ins *o, s32 a, s32 b, s32 c);
extern void  insect_InsectCursorSetSetSize_511bd0(void *a, s32 k, s32 v);
extern void  insect_InsectCursorSetPushPage_511cf0(void *a, s32 k, s32 v);
extern void *insect_InsectCursorSetFindPage_511e60(void *a, s32 k);

extern void func_290010(void *h, s32 id, s32 a, s32 b);
extern void func_290690(void *h, s32 id, f32 a, f32 b, f32 c);
extern f32  func_290770(void *h, s32 id);

void insect_InsectBattleMenuSystemCmd_5011c0(Ins *o)
{
    s32 n;
    s32 i;

    insect_InsectCursorSetFindPage_511e60(o->f4F90, 2);
    switch (insect_InsectBattleGetStep_50d6a0(o, 2)) {
    case 1:
        insect_InsectCmdMenuClear_4efd40(o->f502C);
        insect_InsectCmdMenuAdd_4efc80(o->f502C, 5);
        insect_InsectCmdMenuAdd_4efc80(o->f502C, 3);
        insect_InsectCmdMenuAdd_4efc80(o->f502C, 7);
        n = insect_InsectCmdMenuCount_4efc10(o->f502C);
        insect_InsectCursorSetPushPage_511cf0(o->f4F90, 4, 0);
        insect_InsectCursorSetSetSize_511bd0(o->f4F90, 1, n);
        o->f4FBC = o->f4FBC & 0xFD;
        insect_InsectCmdMenuLayout_4fab80(o, 0, 0, 0);
        insect_InsectBattleSetStep_50d7a0(o, 5, 0, -1);
        i = 0;
        while (i < insect_InsectCmdMenuCount_4efc10(o->f502C)) {
            insect_InsectCmdMenuEntryRefresh_4f0060(o, i, 0);
            i++;
        }
        func_290010(o->f878, 0x7564, 0, -1);
        func_290010(o->f878, 0x7560, 1, -1);
        insect_InsectBattleSetStep_50d7a0(o, 0x1C, 2, -1);
        insect_InsectBattleCursorUpdateDesc_4f4530(o, D_00523DE0, 1);
        break;
    case 0x1D:
        func_290690(o->f878, 0x755F, 0.0f, 0.125f, -1.0f);
        func_290690(o->f87C, 0xC37E, 0.0f, 0.125f, -1.0f);
        insect_InsectBattleSetState_50d8c0(o, 0x10, 0, -1);
        insect_InsectBattleSetStep_50d7a0(o, 0xB, 2, -1);
        break;
    case 0x1C:
        insect_InsectBattleCursorUpdateDesc_4f4530(o, D_00523DE0, 0);
        break;
    case 0x20:
        func_290690(o->f878, 0x7565, 0.0f, 0.125f, -1.0f);
        func_290690(o->f878, 0x755F, 0.0f, 0.125f, -1.0f);
        func_290690(o->f878, 0x7530, 0.0f, 0.125f, -1.0f);
        func_290690(o->f87C, 0xC37E, 0.0f, 0.125f, -1.0f);
        if (func_290770(o->f878, 0x7530) <= 0.0f) {
            insect_InsectBattleSetStep_50d7a0(o, 0xB, 2, -1);
        }
        break;
    case 0xB:
        func_290690(o->f878, 0x755F, 0.0f, 0.125f, -1.0f);
        func_290690(o->f87C, 0xC37E, 0.0f, 0.125f, -1.0f);
        break;
    }
}
