#include "types.h"
/* insect 0x004FB1A0 -- 880 bytes, 220 instructions, 35 calls, 7 conditional
 * branches, br/ins 0.032.  Five-arm state dispatch, chain 5,4,3,2,1 and blocks
 * laid out 1,2,3,4,5, i.e. the reversed-case-order rule with source order
 * ascending.  No fall-throughs; the default is the `b` whose delay slot already
 * carries the epilogue's `ld $31`.
 *
 * The case-1 compare takes `$6` rather than `$3` because the constant 1 is
 * reused as func_290010's third ARGUMENT inside that arm -- the dispatch's own
 * constant CSE'd into the case body, the same shape as insect_FUN_005004F0's
 * case 0xA.
 */

typedef struct Ins {
    u8    pad000[0x878];
    void *f878;                 /* +0x0878 */
    void *f87C;                 /* +0x087C */
    u8    pad880[0x4F90 - 0x880];
    u8    f4F90[0x2C];          /* +0x4F90 */
    u8    f4FBC;                /* +0x4FBC */
    u8    pad4FBD[0x506C - 0x4FBD];
    u8    f506C[0x5DA0 - 0x506C];
    s32   f5DA0;                /* +0x5DA0 */
} Ins;

extern const u8 D_005240E0[];

extern s32  insect_InsectBattleGetStep_50d6a0(Ins *o, s32 k);
extern void insect_InsectBattleSetStep_50d7a0(Ins *o, s32 a, s32 b, s32 c);
extern void insect_InsectBattleCursorUpdateDesc_4f4530(Ins *o, const u8 *t, s32 k);
extern void insect_InsectCursorSetSetSize_511bd0(void *a, s32 b, s32 c);
extern void insect_InsectCursorSetSetCell_511c50(void *a, s32 b, s32 c);
extern void insect_InsectCursorSetPushPage_511cf0(void *a, s32 b, s32 c);
extern s32  insect_InsectMsgCenterX_512b10(void *a, s32 b, s32 c);
extern s32  insect_InsectMsgGet_512b70(void *a, s32 b);

extern void func_28F510(void *h, s32 id, s32 a, s32 b);
extern void func_28F5D0(void *h, s32 id, s32 a, s32 b, s32 c);
extern void func_290010(void *h, s32 id, s32 a, s32 b);
extern void func_290690(void *h, s32 id, f32 a, f32 b, f32 c);
extern f32  func_290770(void *h, s32 id);
extern void func_2907A0(void *h, s32 id, f32 v);

void insect_InsectBattleMenuFirstTurnSelect_4fb1a0(Ins *o)
{
    switch (insect_InsectBattleGetStep_50d6a0(o, 2)) {
    case 1:
        func_290010(o->f878, 0x765C, 1, -1);
        func_2907A0(o->f878, 0x753B, 0.0f);
        func_2907A0(o->f878, 0x753E, 0.0f);
        func_2907A0(o->f878, 0x765C, 0.0f);
        func_290690(o->f878, 0x7530, 1.0f, 0.125f, -1.0f);
        func_290690(o->f878, 0x765C, 1.0f, 0.125f, -1.0f);
        func_28F510(o->f878, 0x765D, insect_InsectMsgGet_512b70(o->f506C, 0x7D7), 0);
        func_28F5D0(o->f878, 0x765D,
                    insect_InsectMsgCenterX_512b10(o->f506C, 0x7D7, o->f5DA0 + 0x40),
                    0xA, 0);
        func_28F510(o->f878, 0x765E, insect_InsectMsgGet_512b70(o->f506C, 0xC), 0);
        func_28F510(o->f878, 0x765E, insect_InsectMsgGet_512b70(o->f506C, 0xD), 1);
        func_290010(o->f87C, 0xC37E, 1, -1);
        func_2907A0(o->f87C, 0xC37E, 0.0f);
        func_290690(o->f87C, 0xC37E, 1.0f, 0.125f, -1.0f);
        insect_InsectBattleSetStep_50d7a0(o, 2, 2, -1);
        insect_InsectCursorSetPushPage_511cf0(o->f4F90, 7, 1);
        insect_InsectCursorSetSetCell_511c50(o->f4F90, 0, 0);
        insect_InsectCursorSetSetSize_511bd0(o->f4F90, 1, 2);
        break;
    case 2:
        insect_InsectBattleCursorUpdateDesc_4f4530(o, D_005240E0, 1);
        if (func_290770(o->f878, 0x765C) >= 1.0f) {
            insect_InsectBattleSetStep_50d7a0(o, 3, 2, -1);
            insect_InsectBattleSetStep_50d7a0(o, 3, 0, -1);
            o->f4FBC = o->f4FBC & 0xFD;
        }
        break;
    case 3:
        insect_InsectBattleCursorUpdateDesc_4f4530(o, D_005240E0, 0);
        break;
    case 4:
        func_290690(o->f878, 0x753E, 0.0f, 0.125f, -1.0f);
        func_290690(o->f878, 0x765C, 0.0f, 0.125f, -1.0f);
        func_290690(o->f878, 0x7530, 0.0f, 0.125f, -1.0f);
        func_290690(o->f87C, 0xC37E, 0.0f, 0.125f, -1.0f);
        insect_InsectBattleSetStep_50d7a0(o, 5, 2, -1);
        break;
    case 5:
        if (func_290770(o->f878, 0x7530) <= 0.0f) {
            insect_InsectBattleSetStep_50d7a0(o, 6, 2, -1);
            insect_InsectBattleSetStep_50d7a0(o, 5, 0, -1);
        }
        break;
    }
}
