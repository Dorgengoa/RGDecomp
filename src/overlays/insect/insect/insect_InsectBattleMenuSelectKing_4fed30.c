#include "types.h"
/* insect 0x004FED30 -- 776 bytes, 194 instructions, 29 calls, 7 conditional
 * branches, br/ins 0.036.  insect_InsectBattleGetStep_50d6a0(o, 2) state dispatch family;
 * header is insect_InsectBattleMenuTeamSelect_5004f0.c.  Compare chain 0x1D, 0x15, 0x12, 1 ->
 * source order 1, 0x12, 0x15, 0x1D (blocks 4FED90, 4FEEBC, 4FEF0C, 4FEF7C),
 * with 1 falling through into 0x12 and 0x12 into 0x15.
 *
 * Both centring expressions are signed DIVISIONS, not shifts: retail emits the
 * bgez / addiu 1 / sra pair for each, which `>> 1` does not produce.
 */

typedef struct Ins {
    u8    pad000[0x878];
    void *f878;                 /* +0x0878 */
    void *f87C;                 /* +0x087C */
    u8    pad880[0x4F90 - 0x880];
    u8    f4F90[0x2C];          /* +0x4F90 */
    u8    f4FBC;                /* +0x4FBC */
    u8    pad4FBD[0x5054 - 0x4FBD];
    u8    f5054[0x18];          /* +0x5054 */
    u8    f506C[0x4];           /* +0x506C */
    u8    pad5070[0x5DA0 - 0x5070];
    s32   f5DA0;                /* +0x5DA0 */
    s32   f5DA4;                /* +0x5DA4 */
} Ins;

extern const u8 D_00523F00[];

extern void insect_InsectBattleCursorUpdateDesc_4f4530(Ins *o, const u8 *t, s32 k);
extern s32  insect_InsectBattleGetStep_50d6a0(Ins *o, s32 k);
extern void insect_InsectBattleSetStep_50d7a0(Ins *o, s32 a, s32 b, s32 c);
extern void insect_InsectBattleSetState_50d8c0(Ins *o, s32 a, s32 b, s32 c);
extern void insect_InsectCursorSetPushPage_511cf0(void *a, s32 k, s32 v);
extern s32  insect_InsectMsgCenterX_512b10(void *a, s32 b, s32 c);
extern s32  insect_InsectMsgGet_512b70(void *a, s32 b);

extern void  func_28F510(void *h, s32 id, s32 a, s32 b);
extern void  func_28F5D0(void *h, s32 id, s32 a, s32 b, s32 c);
extern void  func_290010(void *h, s32 id, s32 a, s32 b);
extern void *func_290460(void *h, s32 id);
extern void  func_290690(void *h, s32 id, f32 a, f32 b, f32 c);
extern void  func_2907A0(void *h, s32 id, f32 v);
extern void  func_290A40(void *h, s32 id, s32 rgba, s32 i);
extern void  func_290F60(void *h, s32 id, s32 a, s32 b);
extern void  func_291110(void *h, s32 id, s32 a, s32 b);
extern void  func_392BB0(void *g, void *w, s32 a, s32 b, s32 c);
extern void  func_3938F0(void *g, void *w, f32 a, f32 b);

void insect_InsectBattleMenuSelectKing_4fed30(Ins *o)
{
    void *g;
    void *p19;
    s32 i;

    g = o->f5054;
    p19 = o->f506C;

    switch (insect_InsectBattleGetStep_50d6a0(o, 2)) {
    case 1:
        func_2907A0(o->f87C, 0xC38F, 0.0f);
        func_290690(o->f87C, 0xC38F, 1.0f, 0.125f, -1.0f);
        func_392BB0(g, func_290460(o->f87C, 0xC390), 0x140, 0x60, 0);
        func_3938F0(g, func_290460(o->f87C, 0xC391), 316.0f, 92.0f);
        func_28F510(o->f87C, 0xC390, insect_InsectMsgGet_512b70(p19, 9), 0);
        func_28F5D0(o->f87C, 0xC390, 0x30, 0x10, 0);
        func_28F510(o->f878, 0x753C, insect_InsectMsgGet_512b70(p19, 0xA), 0);
        func_28F5D0(o->f878, 0x753C,
                    insect_InsectMsgCenterX_512b10(p19, 0xA, o->f5DA0 + 0x40), 8, 0);
        func_291110(o->f878, 0x753D, 0, 1);
        insect_InsectBattleSetStep_50d7a0(o, 0x12, 2, -1);
        /* fallthrough */
    case 0x12:
        func_290F60(o->f87C, 0xC390, (o->f5DA0 - 0x140) / 2,
                    (o->f5DA4 - 0x60) / 2);
        insect_InsectBattleSetStep_50d7a0(o, 0x15, 2, -1);
        /* fallthrough */
    case 0x15:
        func_290010(o->f87C, 0xC38F, 1, -1);
        func_290010(o->f87C, 0xC392, 1, -1);
        insect_InsectCursorSetPushPage_511cf0(o->f4F90, 0, 1);
        o->f4FBC = o->f4FBC & 0xFD;
        insect_InsectBattleSetStep_50d7a0(o, 5, 0, -1);
        insect_InsectBattleSetStep_50d7a0(o, 0xA, 2, -1);
        break;
    case 0x1D:
        insect_InsectBattleCursorUpdateDesc_4f4530(o, D_00523F00, 1);
        func_290690(o->f87C, 0xC37E, 1.0f, 0.125f, -1.0f);
        func_290690(o->f87C, 0xC38F, 0.0f, 0.125f, -1.0f);
        i = 0;
        do {
            func_290A40(o->f878, 0x7545, 0xFF7F7F7F, i);
            i++;
        } while (i < 5);
        insect_InsectBattleSetState_50d8c0(o, 0xE, 0, -1);
        insect_InsectCursorSetPushPage_511cf0(o->f4F90, 8, 1);
        break;
    }
}
